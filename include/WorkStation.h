#pragma once
#include "Tree.h"
#include <memory>

struct WorkStation {
	Mechanic mechanic;
	int ID = 0;
	int capacity = 0;
	int revenue = 0;
	std::unique_ptr<Vehicle> vehiclesToRepair;
	int numVehiclesToRepair = 0;
	std::unique_ptr<Tree> repairedVehicles;
	int numRepairedVehicles = 0;
	std::unique_ptr<WorkStation> next;
};

std::unique_ptr<WorkStation> createWorkStation(int num_stations, FileLines& brands, std::istream& in = std::cin);
void repair(std::unique_ptr<WorkStation>& workstation);
