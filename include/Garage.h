#pragma once
#include "WorkStation.h"

struct Garage {
	std::unique_ptr<WorkStation> workstations;
	int numWorkstations = 0;
	std::unique_ptr<Vehicle> waitQueue;
	int waitQueueSize = 0;
	int totalVehicles = 0;
	int cycles = 0;
};

void createVehiclesInWaitQueue(Garage& garage, FileLines& brands, FileLines& models, int num);
Garage createGarage(FileLines& brands, std::istream& in = std::cin);
bool isBrandPresent(WorkStation* first_station, string brand);
int getNumberOfWorkStations(std::istream& in = std::cin);
void placeVehiclesInWorkStations(Garage& garage, int num);
void sortPriority(std::unique_ptr<Vehicle>& waitQueue);
