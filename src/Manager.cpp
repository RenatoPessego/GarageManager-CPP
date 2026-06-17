#include "Manager.h"

void menuInfo(Garage& garage, std::istream& in) {
	cout << "Day: " << garage.cycles << endl;
	WorkStation* current_ws = garage.workstations.get();
	while (current_ws != nullptr) {
		cout << "WS: " << current_ws->ID << " | " << "Mechanic: " << current_ws->mechanic.name
			<< " | " << "Capacity: " << current_ws->capacity << " | " << "Vehicles: " << current_ws->numVehiclesToRepair << " | " <<
			"Brand: " << current_ws->mechanic.brand << " | " << "Total Revenue: " << current_ws->revenue << endl;
		if (garage.cycles >= 1) {
			cout << "Vehicles to be repaired: " << endl;
		}
		Vehicle* current_vehicle = current_ws->vehiclesToRepair.get();
		if (current_ws->numVehiclesToRepair > 0) {
			for (int i = 0; i < current_ws->capacity; i++) {
				if (current_vehicle != nullptr && garage.cycles >= 1) {
					cout << "ID: " << current_vehicle->ID << " | " << "Vehicle: " << current_vehicle->brand << "-"
						<< current_vehicle->model << " | " << "Priority: ";
					if (current_vehicle->priority) {
						cout << "Yes";
					}
					else {
						cout << "No";
					}
					cout << " | " << "Repair Time: " << current_vehicle->daysInRepair << " | " << "Max Repair Time: ";
					cout << current_vehicle->maxRepairTime << endl;
				}
                if (current_vehicle) current_vehicle = current_vehicle->next.get();
			}
		}
		cout << endl;
		current_ws = current_ws->next.get();

	}
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << "Wait Queue: " << endl;
	Vehicle* current_wait = garage.waitQueue.get();
	while (current_wait != nullptr) {
		cout << "ID: " << current_wait->ID << " | " << "Model: " << current_wait->model << " | " << "Brand: " << current_wait->brand << " | "
			<< "Priority: ";
		if (current_wait->priority) {
			cout << "Yes";
		}
		else {
			cout << "No";
		}
		cout << " | " << "Max Repair Time: " << current_wait->maxRepairTime << endl;
		current_wait = current_wait->next.get();
	}
	cout << endl;
}

void nextDay(Garage& garage, FileLines& brands, FileLines& models, std::istream& in) {
	system("CLS");
	garage.cycles++;
	createVehiclesInWaitQueue(garage, brands, models, 10);
	sortPriority(garage.waitQueue);
	if (garage.cycles > 1) {
		repair(garage.workstations);
	}
	placeVehiclesInWorkStations(garage, 8);
	menuInfo(garage, in);
}

void menu(Garage& garage, FileLines& brands, FileLines& models, std::istream& in) {
	string choice;
	bool exit_menu = false;
	do {
		cout << "Next Day (s) *********** management (g)" << endl << "Exit Program (T)" << endl;
		cout << "Select your option : " << endl;
		getline(in, choice);
  if (in.eof()) exit(1);
		while (choice.length() != 1) {
			cout << "Invalid choice! Type only one of the highlighted letters below." << endl;
			cout << "Next Day (s) *********** management (g)" << endl << "Exit Program (T)" << endl;
			cout << "Select your option : " << endl;
			getline(in, choice);
   if (in.eof()) exit(1);
			cout << endl;
		}

		switch (choice[0]) {
		case 's':
		case 'S':
			nextDay(garage, brands, models, in);
			break;
		case 'g':
		case 'G':
			management(garage, brands, models, in);
			break;
		case 't':
		case 'T':
			exit_menu = true;
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}
	} while (!exit_menu);
}

void management(Garage& garage, FileLines& brands, FileLines& models, std::istream& in) {
	int option;
	string choice1temp;
	double choice1temporary = 0;
	int choice = 0;
	string choice2temp;
	double choice2temporary = 0;
	int choice2 = 0;
	string path = "data/garage.txt";
	bool exit_management = false;
	do {
		cout << " ***** Welcome Manager *****" << endl;
		cout << "(1). Update Repair Time" << endl;
		cout << "(2). Add Priority" << endl;
		cout << "(3). Remove Mechanic" << endl;
		cout << "(4). Save Garage" << endl;
		cout << "(5). Load Garage" << endl;
		cout << "(6). Add Mechanic (Workstation)" << endl;
		cout << "(7). Print Repaired Vehicles" << endl;
		cout << "(8). Exit management" << endl;
		cout << "Select your option : ";
		
		string option_str;
		getline(in, option_str);
  if (in.eof()) exit(1);
		while (!verifyNumber(option_str) || option_str.empty()) {
			cout << "Invalid option! Type a valid number: ";
			getline(in, option_str);
   if (in.eof()) exit(1);
		}
		option = stoi(option_str);

		switch (option) {
		case 1:
			updateRepairTime(garage, in);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 2:
			addPriority(garage, in);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 3:
			removeMechanic(garage, brands, in);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 4:
			saveGarage(garage);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 5:
			while ((choice2temporary > 2) || (choice2temporary <= 0)) {
				cout << "Type: " << endl << "(1) Choose path manually" << endl << "(2) Use default path (data/garage.txt)" << endl;
				in >> ws;
				getline(in, choice2temp);
    if (in.eof()) exit(1);
				while (!verifyNumber(choice2temp)) {
					cout << "Invalid Option! Try again" << endl;;
					cout << "Type: " << endl << "(1) Choose path manually" << endl << "(2) Use default path (data/garage.txt)" << endl;
					getline(in, choice2temp);
     if (in.eof()) exit(1);
				}
				choice2temporary = stod(choice2temp);
				if ((choice2temporary > 2) || (choice2temporary <= 0)) {
					choice2temporary = 0;
				}
				else {
					choice2 = (int)choice2temporary;
				}
			}
			switch (choice2) {
			case 1:
				cout << "Type the path (include .txt at the end of the file name): " << endl;
				getline(in, path);
    if (in.eof()) exit(1);
				while(path.empty()) {
					getline(in, path);
     if (in.eof()) exit(1);
				}
				break;
			case 2:
				break;
			default:
				cout << "Invalid option" << endl << "Printing using default path..." << endl;
				break;
			}
			loadGarage(garage, path);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 6:
			addWorkStation(garage, brands, models, in);
			system("CLS");
			menuInfo(garage, in);
			break;
		case 7:
			while ((choice1temporary > 2) || (choice1temporary <= 0)) {
				cout << "Type: " << endl << "(1) Print Alphabetically" << endl << "(2) Print By Representation" << endl;
				in >> ws;
				getline(in, choice1temp);
    if (in.eof()) exit(1);
				while (!verifyNumber(choice1temp)) {
					cout << "Invalid Option! Try again" << endl;;
					cout << "Type: " << endl << "(1) Print Alphabetically" << endl << "(2) Print By Representation" << endl;
					getline(in, choice1temp);
     if (in.eof()) exit(1);
				}
				choice1temporary = stod(choice1temp);
			}
			choice = (int)choice1temporary;
			switch (choice) {
			case 1:
				printAlphabetically(garage, in);
				break;
			case 2:
				printGarageByRepresentation(garage, in);
				break;
			}
			system("CLS");
			menuInfo(garage, in);
			break;
		case 8:
			exit_management = true;
			break;
		default:
			cout << "Invalid option" << endl;
			break;
		}
	} while (!exit_management);
}

void updateRepairTime(Garage& garage, std::istream& in) {
	string brand;
	string model;
	string input;
	double timetemp = 0;
	int time;
	cout << "Indicate the brand to update the repair time: " << endl;
	in >> ws;
	getline(in, brand);
 if (in.eof()) exit(1);
	cout << "Indicate the model to update the repair time: " << endl;
	in >> ws;
	getline(in, model);
 if (in.eof()) exit(1);
	cout << "Enter the respective time: \n ";
	getline(in, input);	
 if (in.eof()) exit(1);
	while ((timetemp > INT_MAX) || (timetemp <= 0)) {
		while (!verifyNumber(input)) {
			cout << "Invalid time!" << endl << "Enter a valid repair time (integer between 0 and 2147483647): " << endl;
			getline(in, input);
   if (in.eof()) exit(1);
		}
		timetemp = stod(input);
		if ((timetemp <= INT_MAX) && (timetemp > 0)) {
			time = (int)timetemp;
		}
		else {
			cout << "Invalid time!" << endl << "Enter a valid repair time (integer between 0 and 2147483647): " << endl;
			getline(in, input);
   if (in.eof()) exit(1);
			timetemp = 0;
		}
	}
	Vehicle* current = garage.waitQueue.get();
	while (current != nullptr) {
		if (removeSpaces(toUpperCase(current->brand)) == removeSpaces(toUpperCase(brand)) && (removeSpaces(toUpperCase(current->model)) == removeSpaces(toUpperCase(model)))) {
			current->maxRepairTime = time;
		}
		current = current->next.get();
	}
}

void addPriority(Garage& garage, std::istream& in) {
	string input;
	double Idtemp = 0;
	int Id;
	cout << "Indicate the ID of the vehicle to set as Priority: " << endl;
	in >> ws;
	getline(in, input);
 if (in.eof()) exit(1);
	while ((Idtemp > INT_MAX) || (Idtemp <= 0)) {
		while (!verifyNumber(input)) {
			cout << "Invalid ID!" << endl << "Indicate a valid ID to set as priority (integer): " << endl;
			getline(in, input);
   if (in.eof()) exit(1);
		}
		Idtemp = stod(input);
		if ((Idtemp <= INT_MAX) && (Idtemp > 0)) {
			Id = (int)Idtemp;
		}
		else {
			cout << "Invalid ID!" << endl << "Indicate a valid ID to set as priority (integer between 0 and 2147483647): " << endl;
			getline(in, input);
   if (in.eof()) exit(1);
			Idtemp = 0;
		}
	}
	Vehicle* current = garage.waitQueue.get();
	while (current != nullptr) {
		if ((current->ID == Id) && (!current->priority)) {
			current->priority = true;
		}
		current = current->next.get();
	}
	sortPriority(garage.waitQueue);
}

void removeMechanic(Garage& garage, FileLines& brands, std::istream& in) {
	string mechanicRem;
	cout << "Indicate the name of the mechanic you want to remove: " << endl;
	in >> ws;
	getline(in, mechanicRem);
 if (in.eof()) exit(1);
    
    std::unique_ptr<WorkStation>* current_ptr = &garage.workstations;
    while (*current_ptr != nullptr) {
        if (removeSpaces(toUpperCase((*current_ptr)->mechanic.name)) == removeSpaces(toUpperCase(mechanicRem))) {
            break;
        }
        current_ptr = &((*current_ptr)->next);
    }
    
    if (*current_ptr == nullptr) {
        cout << "There is no WS with that mechanic!" << endl;
        return;
    }
    
    WorkStation* current_station = current_ptr->get();
    
	// Repair all vehicles
    std::unique_ptr<Vehicle>* current_vehicle_ptr = &current_station->vehiclesToRepair;
    while (*current_vehicle_ptr != nullptr) {
        Vehicle* v = current_vehicle_ptr->get();
        v->repairCost = v->daysInRepair * current_station->mechanic.pricePerDay;
        current_station->numVehiclesToRepair--;
        current_station->revenue += v->repairCost;
        current_station->numRepairedVehicles++;
        
        auto repaired = std::move(*current_vehicle_ptr);
        *current_vehicle_ptr = std::move(repaired->next);
        repaired->next = nullptr;
        
        addTree(current_station->repairedVehicles, std::move(repaired));
    }

	cout << "The mechanic named " << mechanicRem << " was removed from the WS." << endl;
	cout << "WS: " << current_station->ID << " | " << "Mechanic: " << current_station->mechanic.name
		<< " | " << "Capacity: " << current_station->capacity << " | " <<
		"Brand: " << current_station->mechanic.brand << " | " << "Total Revenue: " << current_station->revenue << endl;
	cout << endl;

    // Delete Workstation node entirely
    *current_ptr = std::move((*current_ptr)->next);
    garage.numWorkstations--;
}

void printGarageByRepresentation(Garage& garage, std::istream& in) {
	string input_str;
	double IDtemp = 0;
	int ID = 0;
	while (IDtemp > garage.numWorkstations || IDtemp <= 0) {
		cout << "Enter a WS ID: " << endl;
		getline(in, input_str);
  if (in.eof()) exit(1);
		while (!verifyNumber(input_str) || input_str.empty()) {
			cout << "Invalid ID! Enter a valid WS ID: " << endl;
			getline(in, input_str);
   if (in.eof()) exit(1);
		}
		IDtemp = stod(input_str);
	}
	ID = int(IDtemp);
	WorkStation* current_station = garage.workstations.get();
	while (current_station != nullptr) {
		if (current_station->ID == ID) {
			system("CLS");
			cout << "Brand: " << current_station->mechanic.brand << endl;
			printTree(current_station->repairedVehicles.get(), 0);
			cout << "\nPress Enter to continue...";
			string dummy;
			getline(in, dummy);
			return;
		}
		current_station = current_station->next.get();
	}
	system("CLS");
	cout << "An error occurred. Try again!" << endl;
}

void addWorkStation(Garage& garage, FileLines& brands, FileLines& models, std::istream& in) {
    int max_id = 0;
	WorkStation* current_station = garage.workstations.get();
    if (!current_station) {
        garage.workstations = createWorkStation(1, brands, in);
        garage.workstations->ID = 1;
        garage.numWorkstations++;
        return;
    }
	while (current_station->next != nullptr) {
        if (current_station->ID > max_id) max_id = current_station->ID;
		current_station = current_station->next.get();
	}
    if (current_station->ID > max_id) max_id = current_station->ID;

	current_station->next = createWorkStation(1, brands, in);
	current_station = current_station->next.get();
	current_station->ID = max_id + 1;
	garage.numWorkstations++;
}

void serializeTree(Tree* root, ofstream& file) {
    if (root == nullptr) return;
    
    Vehicle* v = root->repaired_vehicle.get();
    file << v->daysInRepair << "|" << v->ID << "|" << v->brand << "|"
         << v->model << "|" << v->priority << "|" << v->maxRepairTime << "|" << v->repairCost << "\n";
         
    serializeTree(root->left.get(), file);
    serializeTree(root->right.get(), file);
}

void saveGarage(const Garage& garage) {
	string path = "data/garage.txt";
	ofstream file(path);

	if (file.is_open()) {
		file << garage.cycles << "|" << garage.totalVehicles << "|" << garage.numWorkstations << "\n";

		WorkStation* current_ws = garage.workstations.get();
		while (current_ws != nullptr) {
			file << current_ws->ID << "|" << current_ws->capacity << "|" << current_ws->revenue << "|"
				<< current_ws->numVehiclesToRepair << "|" << current_ws->numRepairedVehicles << "\n";

			Vehicle* current_vehicle = current_ws->vehiclesToRepair.get();
			while (current_vehicle != nullptr) {
				file << current_vehicle->daysInRepair << "|" << current_vehicle->ID << "|" << current_vehicle->brand << "|"
					<< current_vehicle->model << "|" << current_vehicle->priority << "|" << current_vehicle->maxRepairTime << "\n";
				current_vehicle = current_vehicle->next.get();
			}

			serializeTree(current_ws->repairedVehicles.get(), file);

			file << current_ws->mechanic.brand << "|" << current_ws->mechanic.name << "|" << current_ws->mechanic.pricePerDay << "\n";
			current_ws = current_ws->next.get();
		}

        int wait_size = 0;
        Vehicle* w = garage.waitQueue.get();
        while(w) { wait_size++; w = w->next.get(); }
        
		file << wait_size << "\n";
		Vehicle* current_wait = garage.waitQueue.get();
		while (current_wait != nullptr) {
			file << current_wait->ID << "|" << current_wait->daysInRepair << "|" << current_wait->brand << "|"
				<< current_wait->model << "|" << current_wait->priority << "|" << current_wait->maxRepairTime << "\n";
			current_wait = current_wait->next.get();
		}

		file.close();
		cout << "Garage saved successfully!" << endl;
	} else {
		cout << "Error opening file" << endl;
	}
}

bool loadGarage(Garage& garage, const string& path) {
	ifstream file(path);

	if (file.is_open()) {
		Garage new_garage;
		string line;

		getline(file, line);
		stringstream ss(line);
		getline(ss, line, '|'); new_garage.cycles = stoi(line);
		getline(ss, line, '|'); new_garage.totalVehicles = stoi(line);
		getline(ss, line); new_garage.numWorkstations = stoi(line);

		WorkStation* prev_ws = nullptr;
		for (int i = 0; i < new_garage.numWorkstations; i++) {
			auto ws = std::make_unique<WorkStation>();
			getline(file, line);
			stringstream ssWS(line);
			getline(ssWS, line, '|'); ws->ID = stoi(line);
			getline(ssWS, line, '|'); ws->capacity = stoi(line);
			getline(ssWS, line, '|'); ws->revenue = stoi(line);
			getline(ssWS, line, '|'); ws->numVehiclesToRepair = stoi(line);
			getline(ssWS, line); ws->numRepairedVehicles = stoi(line);

			Vehicle* prev_vehicle = nullptr;
			for (int j = 0; j < ws->numVehiclesToRepair; j++) {
				auto vehicle = std::make_unique<Vehicle>();
				getline(file, line);
				stringstream ssVehicle(line);
				getline(ssVehicle, line, '|'); vehicle->daysInRepair = stoi(line);
				getline(ssVehicle, line, '|'); vehicle->ID = stoi(line);
				getline(ssVehicle, line, '|'); vehicle->brand = line;
				getline(ssVehicle, line, '|'); vehicle->model = line;
				getline(ssVehicle, line, '|'); vehicle->priority = (line == "1");
				getline(ssVehicle, line); vehicle->maxRepairTime = stoi(line);

				if (prev_vehicle != nullptr) {
					prev_vehicle->next = std::move(vehicle);
					prev_vehicle = prev_vehicle->next.get();
				} else {
					ws->vehiclesToRepair = std::move(vehicle);
					prev_vehicle = ws->vehiclesToRepair.get();
				}
			}

			for (int k = 0; k < ws->numRepairedVehicles; k++) {
				auto repaired_vehicle = std::make_unique<Vehicle>();
				getline(file, line);
				stringstream ssRepaired(line);
				getline(ssRepaired, line, '|'); repaired_vehicle->daysInRepair = stoi(line);
				getline(ssRepaired, line, '|'); repaired_vehicle->ID = stoi(line);
				getline(ssRepaired, line, '|'); repaired_vehicle->brand = line;
				getline(ssRepaired, line, '|'); repaired_vehicle->model = line;
				getline(ssRepaired, line, '|'); repaired_vehicle->priority = (line == "1");
				getline(ssRepaired, line, '|'); repaired_vehicle->maxRepairTime = stoi(line);
				getline(ssRepaired, line); repaired_vehicle->repairCost = stoi(line);

				addTree(ws->repairedVehicles, std::move(repaired_vehicle));
			}

			getline(file, line);
			stringstream ssMechanic(line);
			getline(ssMechanic, line, '|'); ws->mechanic.brand = line;
			getline(ssMechanic, line, '|'); ws->mechanic.name = line;
			getline(ssMechanic, line); ws->mechanic.pricePerDay = stoi(line);

			if (prev_ws != nullptr) {
				prev_ws->next = std::move(ws);
				prev_ws = prev_ws->next.get();
			} else {
				new_garage.workstations = std::move(ws);
				prev_ws = new_garage.workstations.get();
			}
		}

		getline(file, line);
		new_garage.waitQueueSize = stoi(line);

		Vehicle* prev_wait = nullptr;
		for (int i = 0; i < new_garage.waitQueueSize; i++) {
			auto vehicle = std::make_unique<Vehicle>();
			getline(file, line);
			stringstream ssVehicle(line);
			getline(ssVehicle, line, '|'); vehicle->ID = stoi(line);
			getline(ssVehicle, line, '|'); vehicle->daysInRepair = stoi(line);
			getline(ssVehicle, line, '|'); vehicle->brand = line;
			getline(ssVehicle, line, '|'); vehicle->model = line;
			getline(ssVehicle, line, '|'); vehicle->priority = (line == "1");
			getline(ssVehicle, line); vehicle->maxRepairTime = stoi(line);

			if (prev_wait != nullptr) {
				prev_wait->next = std::move(vehicle);
				prev_wait = prev_wait->next.get();
			} else {
				new_garage.waitQueue = std::move(vehicle);
				prev_wait = new_garage.waitQueue.get();
			}
		}

		file.close();
		garage = std::move(new_garage);
		cout << "Garage loaded successfully!" << endl;
        return true;
	} else {
		cout << "Error opening file" << endl;
        return false;
	}
}

void printAlphabetically(Garage& garage, std::istream& in) {
	string input_str;
	double IDtemp = 0;
	int ID = 0;
	while (IDtemp > garage.numWorkstations || IDtemp <= 0) {
		cout << "Enter a WS ID: " << endl;
		getline(in, input_str);
  if (in.eof()) exit(1);
		while (!verifyNumber(input_str) || input_str.empty()) {
			cout << "Invalid ID! Enter a valid WS ID: " << endl;
			getline(in, input_str);
   if (in.eof()) exit(1);
		}
		IDtemp = stod(input_str);
	}
	ID = int(IDtemp);
	WorkStation* current_station = garage.workstations.get();

	while (current_station != nullptr) {
		if (current_station->ID == ID) {
			system("CLS");
			cout << "Brand: " << current_station->mechanic.brand << endl;
			backbone(current_station->repairedVehicles);
			sortTree(current_station->repairedVehicles);
			printArray(current_station->repairedVehicles.get());
			cout << "\nPress Enter to continue...";
			string dummy;
			getline(in, dummy);
			return;
		}
		current_station = current_station->next.get();
	}
	system("CLS");
	cout << "An error occurred. Try again!" << endl;
}
