#include "Problem.h"
#include <iostream>

int main() {
    std::cout << "Welcome to Bertie Woosters (change this to your name) Feature Selection Algorithm.\n";
    std::cout << "Please enter total number of features: ";
    
    int total_features;
    std::cin >> total_features;

    std::cout << "Type the number of the algorithm you want to run.\n";
    std::cout << "1. Forward Selection\n";
    std::cout << "2. Backward Elimination\n";
    std::cout << "3. Bertie's Special Algorithm\n";

    int choice;
    std::cin >> choice;

    Problem problem;

    if (choice == 1) {
        problem.forward_selection(total_features);
    } else {
        std::cout << "Backward Elimination is not implemented yet.\n";
    }

    return 0;
}