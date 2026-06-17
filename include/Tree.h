#pragma once
#include "Vehicle.h"
#include "Mechanic.h"
#include <memory>
#include <string>

struct Tree {
    std::unique_ptr<Vehicle> repaired_vehicle;
    std::unique_ptr<Tree> left, right;
};

std::unique_ptr<Tree> CreateNode(std::unique_ptr<Vehicle> item);
void Insert(std::unique_ptr<Tree>& node, std::unique_ptr<Vehicle> key);
void addTree(std::unique_ptr<Tree>& root, std::unique_ptr<Vehicle> key);
int numberOfLevels(Tree* root);
void printTree(Tree* no, int nivel);
void backbone(std::unique_ptr<Tree>& root);
void sortTree(std::unique_ptr<Tree>& root);
void printArray(Tree* raiz);
