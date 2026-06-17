#pragma once
#include "Garage.h"

void menuInfo(Garage& garage, std::istream& in = std::cin);
void nextDay(Garage& garage, FileLines& brands, FileLines& models, std::istream& in = std::cin);
void management(Garage& garage, FileLines& brands, FileLines& models, std::istream& in = std::cin);
void menu(Garage& garage, FileLines& brands, FileLines& models, std::istream& in = std::cin);
void updateRepairTime(Garage& garage, std::istream& in = std::cin);
void addPriority(Garage& garage, std::istream& in = std::cin);
void addWorkStation(Garage& garage, FileLines& brands, FileLines& models, std::istream& in = std::cin);
void removeMechanic(Garage& garage, FileLines& brands, std::istream& in = std::cin);
void printGarageByRepresentation(Garage& garage, std::istream& in = std::cin);
void saveGarage(const Garage& garage);
bool loadGarage(Garage& garage, const string& path);
void printAlphabetically(Garage& garage, std::istream& in = std::cin);