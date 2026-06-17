#include "WorkStation.h"

std::unique_ptr<WorkStation> createWorkStation(int num_stations, FileLines& brands, std::istream& in) {
	auto first_station = std::make_unique<WorkStation>();
	first_station->mechanic = createMechanic(brands, in);
	first_station->capacity = 2 + (rand() % 3);
	first_station->revenue = 0;
	first_station->ID = 1;
	first_station->numVehiclesToRepair = 0;
	first_station->numRepairedVehicles = 0;
	first_station->next = nullptr;
    
	WorkStation* current = first_station.get();
	for (int i = 1; i < num_stations; i++) {
		auto new_station = std::make_unique<WorkStation>();
		new_station->mechanic = createMechanic(brands, in);
		new_station->capacity = 2 + (rand() % 3);
		new_station->revenue = 0;
		new_station->ID = i + 1;
		new_station->numVehiclesToRepair = 0;
		new_station->numRepairedVehicles = 0;
		new_station->next = nullptr;
		
		current->next = std::move(new_station);
		current = current->next.get();
	}
	return first_station;
}

void repair(std::unique_ptr<WorkStation>& station_list) {
	bool repair_chance = false;
	WorkStation* current_station = station_list.get();
	
	while (current_station != nullptr) {
        int n = current_station->capacity;
        
        std::unique_ptr<Vehicle>* current_vehicle_ptr = &current_station->vehiclesToRepair;
        
        for (int i = 0; i < n; i++) {
            if (*current_vehicle_ptr == nullptr) break;
            
            Vehicle* current_vehicle = current_vehicle_ptr->get();
            repair_chance = GenerateProbabilities(0.15);
            
            if (current_vehicle->daysInRepair < current_vehicle->maxRepairTime) {
                if (repair_chance && current_vehicle->daysInRepair > 0) {
                    current_vehicle->repairCost = current_vehicle->daysInRepair * current_station->mechanic.pricePerDay;
                    current_station->revenue += current_vehicle->repairCost;
                    
                    auto repaired_vehicle = std::move(*current_vehicle_ptr);
                    *current_vehicle_ptr = std::move(repaired_vehicle->next);
                    repaired_vehicle->next = nullptr;
                    
                    addTree(current_station->repairedVehicles, std::move(repaired_vehicle));
                    
                    current_station->numVehiclesToRepair--;
                    current_station->numRepairedVehicles++;
                } else {
                    current_vehicle->daysInRepair++;
                    current_vehicle_ptr = &((*current_vehicle_ptr)->next);
                }
            } else if (current_vehicle->daysInRepair > 0 && current_vehicle->daysInRepair >= current_vehicle->maxRepairTime) {
                current_vehicle->repairCost = current_vehicle->daysInRepair * current_station->mechanic.pricePerDay;
                current_station->revenue += current_vehicle->repairCost;
                
                auto repaired_vehicle = std::move(*current_vehicle_ptr);
                *current_vehicle_ptr = std::move(repaired_vehicle->next);
                repaired_vehicle->next = nullptr;
                
                addTree(current_station->repairedVehicles, std::move(repaired_vehicle));
                
                current_station->numVehiclesToRepair--;
                current_station->numRepairedVehicles++;
            } else {
                current_vehicle_ptr = &((*current_vehicle_ptr)->next);
            }
        }
		
		current_station = current_station->next.get();
	}
}
