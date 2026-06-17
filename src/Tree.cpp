#include "Tree.h"
#include <algorithm>

using namespace std;

std::unique_ptr<Tree> CreateNode(std::unique_ptr<Vehicle> item) {
    auto temp = std::make_unique<Tree>();
    temp->repaired_vehicle = std::move(item);
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

void Insert(std::unique_ptr<Tree>& node, std::unique_ptr<Vehicle> key) {
    Tree* temp = node.get();
    while (temp != nullptr) {
        if (key->model >= temp->repaired_vehicle->model) {
            if (temp->right == nullptr) {
                temp->right = CreateNode(std::move(key));
                return;
            } else {
                temp = temp->right.get();
            }
        } else {
            if (temp->left == nullptr) {
                temp->left = CreateNode(std::move(key));
                return;
            } else {
                temp = temp->left.get();
            }
        }
    }
}

void addTree(std::unique_ptr<Tree>& root, std::unique_ptr<Vehicle> key) {
    if (root == nullptr) {
        root = CreateNode(std::move(key));
    } else {
        Insert(root, std::move(key));
    }
}

int numberOfLevels(Tree* root) {
    int h = 0;
    if (root != nullptr) {
        int alturaesq = numberOfLevels(root->left.get());
        int alturadir = numberOfLevels(root->right.get());
        int alturamax = max(alturaesq, alturadir);
        h = alturamax + 1;
    }
    return h;
}

void printTree(Tree* no, int nivel) {
    if (no == nullptr) {
        cout << endl;
        return;
    }
    printTree(no->right.get(), nivel + 1);
    for (int i = 1; i < nivel; i++) {
        cout << "\t";
    }
    cout << no->repaired_vehicle->model << " (" << no->repaired_vehicle->ID << ")" << endl;
    printTree(no->left.get(), nivel + 1);
}

void backbone(std::unique_ptr<Tree>& root) {
    if (root == nullptr) {
        return;
    }
    if (root->left != nullptr) {
        backbone(root->left);
        auto temp = std::move(root->right);
        root->right = std::move(root->left);
        Tree* t = root->right.get();
        while (t->right != nullptr) {
            t = t->right.get();
        }
        t->right = std::move(temp);
    }
    backbone(root->right);
}

void sortTree(std::unique_ptr<Tree>& root) {
    if (!root) return;
    bool swapped = true;
    while (swapped) {
        swapped = false;
        std::unique_ptr<Tree>* ptr_to_current = &root;

        while ((*ptr_to_current)->right) {
            if ((*ptr_to_current)->repaired_vehicle->model > (*ptr_to_current)->right->repaired_vehicle->model) {
                auto temp = std::move((*ptr_to_current)->right);
                (*ptr_to_current)->right = std::move(temp->right);
                temp->right = std::move(*ptr_to_current);
                *ptr_to_current = std::move(temp);
                swapped = true;
            }
            ptr_to_current = &((*ptr_to_current)->right);
        }
    }
}

void printArray(Tree* raiz) {
    Tree* temp = raiz;
    if (temp != nullptr) {
        cout << temp->repaired_vehicle->model << " (" << temp->repaired_vehicle->ID << ")" << endl;
        while (temp->right != nullptr) {
            cout << temp->right->repaired_vehicle->model << " (" << temp->right->repaired_vehicle->ID << ")" << endl;
            temp = temp->right.get();
        }
        cout << endl;
    }
}