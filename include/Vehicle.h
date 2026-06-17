#pragma once
#include "Files.h"
#include <memory>

struct Vehicle {
	string brand = "";
	string model = "";
	int daysInRepair = 0;
	int maxRepairTime = 0;
	int ID = 0;
	bool priority = false;
	int repairCost = 0;
	std::unique_ptr<Vehicle> next;
};

bool GenerateProbabilities(double probability);
std::unique_ptr<Vehicle> createVehicle(FileLines& brands, FileLines& models);
void addVehicle(std::unique_ptr<Vehicle>& listHead, std::unique_ptr<Vehicle> car);
