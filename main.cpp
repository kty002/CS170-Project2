#include "Problem.h"
#include <iostream>

int main() {
    std::cout << "Welcome to Bertie Woosters (change this to your name) Feature Selection Algorithm.\n";
    std::cout << "Please enter total number of features: ";
    
    //5 = f1, f2, f3, f4, f5
    //1 = f1
    int total_features;
    std::cin >> total_features;

    std::cout << "Type the number of the algorithm you want to run.\n";
    std::cout << "1. Forward Selection\n";
    std::cout << "2. Backward Elimination\n";
    std::cout << "3. Bertie's Special Algorithm\n";

    //selects the algorithm
    int choice;
    std::cin >> choice;

    Problem problem;

    if (choice == 1) {
        problem.forward_selection(total_features);
    } 
    else if (choice == 2) {
        problem.backward_elimination(total_features);
    }
    else if (choice == 3) {
        problem.custom_algorithm(total_features);
    }
    else {
        std::cout << "I have no idea what algorithm to run\n";
    }

    return 0;
}