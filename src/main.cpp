#include "Manager.h"

int main(int argc, char* argv[]) {
	srand((unsigned int)time(NULL));
	FileLines models = loadFileLines("data/models.txt");
	FileLines brands = loadFileLines("data/brands.txt");

	Garage garage;
	if (argc == 2) {
		string path = argv[1];
		loadGarage(garage, path);
	}
	else {
		system("CLS");
		cout << "Do you want to load a saved garage? (y/n): ";
		string choice;
		getline(cin, choice);
		if (choice == "y" || choice == "Y") {
			cout << "Enter path or leave empty for default (data/garage.txt): ";
			string path;
			getline(cin, path);
			if (path.empty()) path = "data/garage.txt";
			if (!loadGarage(garage, path)) {
				garage = createGarage(brands);
				createVehiclesInWaitQueue(garage, brands, models, 10);
				sortPriority(garage.waitQueue);
			}
		} else {
			garage = createGarage(brands);
			createVehiclesInWaitQueue(garage, brands, models, 10);
			sortPriority(garage.waitQueue);
		}
	}

	menuInfo(garage);
	menu(garage, brands, models);

	return 0;
}
