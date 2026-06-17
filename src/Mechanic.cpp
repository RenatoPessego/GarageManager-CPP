#include "Mechanic.h"

Mechanic createMechanic(FileLines& brands, std::istream& in) {
	Mechanic new_mechanic = Mechanic();
	string input_str;
	double price_temp = 0;
	int price = 0;
	string brand;
	bool exit_loop = false;

	while (!exit_loop) {
		cout << "Enter a valid mechanic brand: " << endl;
		getline(in, brand);
  if (in.eof()) exit(1);
		for (int i = 0; i < brands.size; i++) {
			if (removeSpaces(toUpperCase(brand)) == removeSpaces(toUpperCase(brands.lines[i]))) {
				new_mechanic.brand = brands.lines[i];
				exit_loop = true;
				break;
			}
		}
	}
	cout << "Enter the mechanic's name: " << endl;
	in >> ws;
	getline(in, new_mechanic.name);
 if (in.eof()) exit(1);
	while ((price_temp > 100) || (price_temp <= 0)) {
		cout << "Enter a valid price per day for the mechanic (integer between 0 and 100): " << endl;
		getline(in, input_str);
  if (in.eof()) exit(1);
		while (!verifyNumber(input_str)) {
			cout << "Invalid input!" << endl << "Enter the price per day for the mechanic (integer between 0 and 100): " << endl;
			getline(in, input_str);
   if (in.eof()) exit(1);
		}
		price_temp = stod(input_str);
	}
	price = (int)price_temp;
	new_mechanic.pricePerDay = price;
	return new_mechanic;
}

bool verifyNumber(string n) {
	if (n.length() == 0) {
		return false;
	}
	for (int i = 0; i < n.length(); i++) {
		if (isdigit(n[i]) == false) {
			return false;
		}
	}
	return true;
}