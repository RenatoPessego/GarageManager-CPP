#include "catch.hpp"
#include "Garage.h"
#include "Files.h"
#include "Tree.h"

int countNodes(Tree* node) {
    if (node == nullptr) return 0;
    return 1 + countNodes(node->left.get()) + countNodes(node->right.get());
}

TEST_CASE("BST Load Test", "[stress]") {
    FileLines brands;
    brands.size = 1;
    brands.lines.push_back("Ford");

    FileLines models;
    models.size = 1;
    models.lines.push_back("Mustang");

    std::stringstream mock_in;
    mock_in << "20\n";
    for(int i=0; i<20; i++) {
        mock_in << "Ford\nBob\n50\n";
    }
    Garage garage = createGarage(brands, mock_in);

    // Add vehicles
    for (int i = 0; i < 5000; i++) {
        addVehicle(garage.waitQueue, createVehicle(brands, models));
        garage.waitQueueSize++;
        garage.totalVehicles++;
    }

    placeVehiclesInWorkStations(garage, 5000);

    for (int i = 0; i < 50; i++) {
        repair(garage.workstations);
    }

    WorkStation* ws = garage.workstations.get();
    REQUIRE(ws != nullptr);
    
    int count = countNodes(ws->repairedVehicles.get());
    REQUIRE(count > 0);
    REQUIRE(ws->numRepairedVehicles == count);

    // Balance tree to prevent stack overflow on destructor
    backbone(ws->repairedVehicles);
    sortTree(ws->repairedVehicles);

    // Iteratively clear linked lists
    while (garage.waitQueue) {
        garage.waitQueue = std::move(garage.waitQueue->next);
    }
    WorkStation* current = garage.workstations.get();
    while (current) {
        while (current->vehiclesToRepair) {
            current->vehiclesToRepair = std::move(current->vehiclesToRepair->next);
        }
        current = current->next.get();
    }
    while (garage.workstations) {
        garage.workstations = std::move(garage.workstations->next);
    }
}
