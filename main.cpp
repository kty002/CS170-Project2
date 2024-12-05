#include "Problem.h"
#include <fstream>
#include <sstream>
// #include "Classifier.cpp"
#include "Validator.cpp"
#include <iostream>

// https://stackoverflow.com/questions/8365013/reading-line-from-text-file-and-putting-the-strings-into-a-vector
// CODE BORROWED AND USED AS REFERENCE TO READ DATASET
// readdataset opens a file and normalizes it into data
void ReadDataset(const std::string& filename, std::vector<std::vector<double>>& data, std::vector<int>& labels) {
    std::string line;
    std::ifstream file(filename);
    // std::ifstream myfile("OHenry.txt");

    if(!file) //Always test the file open.
    {
        std::cout<<"Error opening output file"<< std::endl;
        system("pause");
        return;
    }
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::vector<double> instance;
        double value;
        stream >> value;
        labels.push_back(static_cast<int>(value)); //normalize values

        while (stream >> value) {
            instance.push_back(value);
        }
        data.push_back(instance);
    }
}

// STARTS WITH THE SMALL THEN LARGE DATASET, TRANSITIONS TO SELECTION ALGORITHM
// NEEDS TO INCLUDE STEPS (display predicted and actual values, if predicted = actual then correct, if not then incorrect)
// NEEDS TO INCLUDE TIME SPENT ON STEPS
// DISPLAY BOTH WHEN DONE
int main() {
    //SMALL DATASET
     std::vector<std::vector<double>> data;
    std::vector<int> labels;

    // Load small dataset
    ReadDataset("small-test-dataset.txt", data, labels);

    // Test Validator with {3, 5, 7}
    Validator validator;
    std::vector<int> feature_subset_small = {3, 5, 7};
    double accuracy_small = validator.Validate(data, labels, feature_subset_small);

    std::cout << "Accuracy with features {3, 5, 7}: " << accuracy_small * 100 << "%\n";

    //LARGE DATASET
    std::vector<std::vector<double>> data2;
    std::vector<int> labels2;
    ReadDataset("large-test-dataset.txt", data2, labels2);

    // Test Validator with {1, 15, 27}
    Validator validator2;
    std::vector<int> feature_subset_large = {1, 15, 27};
    double accuracy_large = validator2.Validate(data2, labels2, feature_subset_large);

    std::cout << "Accuracy with features {1, 15, 27}: " << accuracy_large * 100 << "%\n";



    // uncomment return to end after running datasets
    // return 1;

    //START OF NORMAL FEATURE SELECTION
    std::cout << "Welcome to Pranay Thakur's Feature Selection Algorithm.\n";
    std::cout << "Please enter total number of features: ";
    
    //5 = f1, f2, f3, f4, f5
    //1 = f1
    int total_features;
    std::cin >> total_features;

    std::cout << "Type the number of the algorithm you want to run.\n";
    std::cout << "1. Forward Selection\n";
    std::cout << "2. Backward Elimination\n";
    std::cout << "3. Bi-Directional Search (Custom Algorithm)\n";


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
        std::cout << "I have no idea what algorithm to run, please restart the program and select a valid algorithm.\n";
    }

    return 0;
}
