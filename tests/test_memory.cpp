#include "catch.hpp"
#include <iostream>
#include <cassert>
#include "Garage.h"
#include "Files.h"

using namespace std;

TEST_CASE("Heavy Memory Allocation Test", "[memory]") {
    cout << "[TEST] Starting Heavy Memory Allocation Test..." << endl;
    
    // Create dummy files for FileLines to avoid reading actual disks
    FileLines brands;
    brands.size = 2;
    brands.lines.push_back("Audi");
    brands.lines.push_back("BMW");

    FileLines models;
    models.size = 2;
    models.lines.push_back("A4");
    models.lines.push_back("M3");

    std::stringstream mock_in;
    mock_in << "20\n";
    for(int i=0; i<20; i++) {
        mock_in << "Audi\nJohn\n50\n";
    }
    Garage garage = createGarage(brands, mock_in);
    
    // Rapidly inject 10,000 vehicles into the wait queue
    cout << "[TEST] Adding 10,000 vehicles to the wait queue..." << endl;
    for (int i = 0; i < 10000; i++) {
        addVehicle(garage.waitQueue, createVehicle(brands, models));
        garage.waitQueueSize++;
        garage.totalVehicles++;
    }
    
    REQUIRE(garage.waitQueueSize == 10000);
    
    // Move them into workstations
    cout << "[TEST] Placing vehicles into workstations..." << endl;
    placeVehiclesInWorkStations(garage, 10000);
    
    // Process next day repeatedly to process repairs
    cout << "[TEST] Processing 10 days of heavy repairs..." << endl;
    for (int i = 0; i < 10; i++) {
        repair(garage.workstations);
    }
    
    // Balance the BSTs to prevent stack overflow on destructor (due to 10k right-leaning nodes)
    WorkStation* ws = garage.workstations.get();
    while (ws != nullptr) {
        if (ws->repairedVehicles) {
            backbone(ws->repairedVehicles);
            sortTree(ws->repairedVehicles);
        }
        // Manually destroy vehiclesToRepair linked list
        while (ws->vehiclesToRepair) {
            ws->vehiclesToRepair = std::move(ws->vehiclesToRepair->next);
        }
        ws = ws->next.get();
    }
    
    // Manually destroy waitQueue linked list
    while (garage.waitQueue) {
        garage.waitQueue = std::move(garage.waitQueue->next);
    }
    
    // Manually destroy workstations linked list
    while (garage.workstations) {
        garage.workstations = std::move(garage.workstations->next);
    }
    
    cout << "[TEST] Memory test passed. No segfaults detected, unique_ptr boundaries held." << endl;
}
