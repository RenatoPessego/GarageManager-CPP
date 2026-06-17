#pragma once
#include "Files.h"

struct Mechanic {
    string name = "";
    string brand = "";
    int pricePerDay = 0;
};

Mechanic createMechanic(FileLines& brands, std::istream& in = std::cin);
bool verifyNumber(string n);