#include "Garage.h"

Garage createGarage(FileLines& brands, std::istream& in) {
	Garage new_garage;
	new_garage.numWorkstations = getNumberOfWorkStations(in);
	new_garage.workstations = createWorkStation(new_garage.numWorkstations, brands, in);

	new_garage.totalVehicles = 0;
	new_garage.cycles = 0;
	new_garage.waitQueueSize = 0;
	new_garage.waitQueue = nullptr;
	return new_garage;
}

void createVehiclesInWaitQueue(Garage& garage, FileLines& brands, FileLines& models, int num) {
    for (int i = 0; i < num; i++) {
        auto new_vehicle = createVehicle(brands, models);
        while (!isBrandPresent(garage.workstations.get(), new_vehicle->brand)) {
            new_vehicle = createVehicle(brands, models);
        }
        new_vehicle->ID = garage.totalVehicles + 1;
        garage.totalVehicles++;
        
        addVehicle(garage.waitQueue, std::move(new_vehicle));
    }
}

bool isBrandPresent(WorkStation* first_station, string brand) {
	bool present = false;
	WorkStation* current = first_station;
	while (current != nullptr) {
		present = (brand == current->mechanic.brand);
		if (present) {
			break;
		}
		current = current->next.get();
	}
	return present;
}

int getNumberOfWorkStations(std::istream& in) {
    string input_str;
    int num_workstations = 0;
    while (num_workstations < 1 || num_workstations > 20) {
        cout << "How many mechanics would you like to add? (1 - 20): " << endl;
        getline(in, input_str);
        if (in.eof()) exit(1);
        if (verifyNumber(input_str)) {
            num_workstations = stoi(input_str);
            if (num_workstations < 1 || num_workstations > 20) {
                cout << "Invalid input! Please enter an integer between 1 and 20." << endl;
            }
        } else {
            cout << "Invalid input! Please enter an integer between 1 and 20." << endl;
        }
    }
    return num_workstations;
}

void sortPriority(std::unique_ptr<Vehicle>& waitQueue) {
    if (!waitQueue) return;

    std::unique_ptr<Vehicle> priority_head = nullptr;
    std::unique_ptr<Vehicle> non_priority_head = nullptr;
    
    Vehicle* priority_tail = nullptr;
    Vehicle* non_priority_tail = nullptr;

    while (waitQueue) {
        auto current = std::move(waitQueue);
        waitQueue = std::move(current->next);
        current->next = nullptr;
        
        if (current->priority) {
            if (!priority_head) {
                priority_head = std::move(current);
                priority_tail = priority_head.get();
            } else {
                priority_tail->next = std::move(current);
                priority_tail = priority_tail->next.get();
            }
        } else {
            if (!non_priority_head) {
                non_priority_head = std::move(current);
                non_priority_tail = non_priority_head.get();
            } else {
                non_priority_tail->next = std::move(current);
                non_priority_tail = non_priority_tail->next.get();
            }
        }
    }
    
    if (priority_tail) {
        priority_tail->next = std::move(non_priority_head);
        waitQueue = std::move(priority_head);
    } else {
        waitQueue = std::move(non_priority_head);
    }
}

void placeVehiclesInWorkStations(Garage& garage, int num) {
    int placed = 0;
    
    std::unique_ptr<Vehicle>* current_wait = &garage.waitQueue;
    
    while (*current_wait != nullptr && placed < num) {
        bool placed_this_vehicle = false;
        WorkStation* current_station = garage.workstations.get();
        
        while (current_station != nullptr) {
            if (current_station->mechanic.brand == (*current_wait)->brand) {
                int count = 0;
                Vehicle* v = current_station->vehiclesToRepair.get();
                while(v) { count++; v = v->next.get(); }
                
                if (count < current_station->capacity) {
                    auto vehicle_to_move = std::move(*current_wait);
                    *current_wait = std::move(vehicle_to_move->next);
                    vehicle_to_move->next = nullptr;
                    
                    addVehicle(current_station->vehiclesToRepair, std::move(vehicle_to_move));
                    current_station->numVehiclesToRepair++;
                    placed++;
                    placed_this_vehicle = true;
                    break;
                }
            }
            current_station = current_station->next.get();
        }
        
        if (!placed_this_vehicle) {
            current_wait = &((*current_wait)->next);
        }
    }
}
