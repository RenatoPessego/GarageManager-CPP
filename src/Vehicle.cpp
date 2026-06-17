#include "Vehicle.h"

bool GenerateProbabilities(double probability) {
	bool probability_final = rand() < (probability * (RAND_MAX + 1.0));
	return probability_final;
} 

std::unique_ptr<Vehicle> createVehicle(FileLines& brands, FileLines& models) {
	auto new_vehicle = std::make_unique<Vehicle>();
	new_vehicle->brand = brands.lines[rand() % brands.size];
	new_vehicle->model = models.lines[rand() % models.size];
	new_vehicle->ID = 0;
	new_vehicle->maxRepairTime = 2 + (rand() % 3);
	new_vehicle->daysInRepair = 0;
	new_vehicle->priority = GenerateProbabilities(0.05);
	new_vehicle->repairCost = 0;
	return new_vehicle;
}




void addVehicle(std::unique_ptr<Vehicle>& listHead, std::unique_ptr<Vehicle> car) {
	if (!listHead) {
		listHead = std::move(car);
	} else {
		Vehicle* current = listHead.get();
		while (current->next) {
			current = current->next.get();
		}
		current->next = std::move(car);
	}
}
