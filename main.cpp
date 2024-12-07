#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cmath>
#include <limits>
#include "Read.cpp"
#include "Problem.h"
#include "Validator.cpp"

// A helper function to extract only the specified features from an instance
std::vector<double> extractFeatures(const std::vector<double>& full_features, const std::vector<int>& feature_subset) {
    std::vector<double> reduced;
    reduced.reserve(feature_subset.size());
    for (int f : feature_subset) {
        reduced.push_back(full_features[f - 1]); // f is 1-based, convert to 0-based
    }
    return reduced;
}

void printVector(std::vector<int> v){
    std::cout << "{";
    int i = 0;

    for (const int &num : v) {
        std::cout << num;
        if(i < (v.size() - 1)) {
            std::cout << ", ";
        } 
        i++;
    }
    std::cout << "} ";
}

void test_classifier(std::string filename, std::vector<int> feature_subset) {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Testing Classifier"<<std::endl;
    std::cout << "Input file name: "<< filename << std::endl;
    std::cout << "Feature subset: ";
    printVector(feature_subset);
    
    
    // Load dataset
    // std::string filename = "large-test-dataset.txt"; // or prompt user if needed
    std::vector<std::vector<double>> data;
    std::vector<int> labels;
    ReadDataset(filename, data, labels);

    // For demonstration: using {3, 5, 7} as feature subset
    // std::vector<int> feature_subset = {1, 15, 27};

    // Start timing the leave-one-out validation
    auto start = std::chrono::high_resolution_clock::now();

    int correct_predictions = 0;
    int total = static_cast<int>(data.size());

    Classifier classifier;

    // Leave-One-Out Cross Validation
    for (int i = 0; i < total; ++i) {
        // Prepare training data excluding instance i
        std::vector<std::vector<double>> training_data;
        std::vector<int> training_labels;

        for (int j = 0; j < total; ++j) {
            if (j == i) continue;
            // Extract relevant features from data[jtd::cout << "Testing Classifies" << std::endl;]
            std::vector<double> reduced_instance = extractFeatures(data[j], feature_subset);
            training_data.push_back(reduced_instance);
            training_labels.push_back(labels[j]);
        }
        //std::cout << "Traning Classifier" << std::endl;
        //auto start_T = std::chrono::high_resolution_clock::now();
        // Train the classifier on the training set
        classifier.Train(training_data, training_labels);
        // End timing
        //auto end_T = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<double> elapsed_T = end_T - start_T;
        //std::cout << "Time spent Traning: " << elapsed_T.count() << " seconds\n";

        // Test on the left-out instance i
        std::vector<double> test_instance_reduced = extractFeatures(data[i], feature_subset);
        //std::cout << "Prediting Label using classifier" << std::endl;
        auto start_P = std::chrono::high_resolution_clock::now();
        
        int predicted_label = classifier.Test(test_instance_reduced);
        //auto end_P = std::chrono::high_resolution_clock::now();
        //std::chrono::duration<double> elapsed_P = end_P - start_P;
        //std::cout << "Time spent Predicting: " << elapsed_P.count() << " seconds\n";

        int actual_label = labels[i];

        // Display predicted and actual values
        /*
        std::cout << "Test instance " << i << ": Predicted = " << predicted_label
                  << ", Actual = " << actual_label;*/

        if (predicted_label == actual_label) {
            //std::cout << " [CORRECT]" << std::endl;
            correct_predictions++;
        } else {
            //std::cout << " [INCORRECT]" << std::endl;
        }
    }

    double accuracy = static_cast<double>(correct_predictions) / total;

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Display final results
    std::cout << "\nTotal instances: " << total << std::endl;
    std::cout << "Number of correct predictions: " << correct_predictions << std::endl;
    std::cout << "Accuracy: with feature ";
    printVector(feature_subset);
    std::cout<< (accuracy * 100.0) << "%" << std::endl;
    std::cout << "Time spent on classifier: " << elapsed.count() << " seconds\n";
}

void test_validator() {
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Testing Validator" << std::endl;
    //SMALL DATASET
    std::vector<std::vector<double>> data;
    std::vector<int> labels;

    // Load small dataset
    ReadDataset("small-test-dataset.txt", data, labels);
    
    auto start1 = std::chrono::high_resolution_clock::now();
    // Test Validator with {3, 5, 7}
    Validator validator;
    std::vector<int> feature_subset_small = {3, 5, 7};
    double accuracy_small = validator.Validate(data, labels, feature_subset_small);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;
    std::cout << "Accuracy with features {3, 5, 7}: " << accuracy_small * 100 << "%\n";
    std::cout << "Time spent on validation: " << elapsed1.count() << " seconds\n";
    std::cout << std::endl;
    std::cout << std::endl;
    
    //LARGE DATASET
    std::vector<std::vector<double>> data2;
    std::vector<int> labels2;
    ReadDataset("large-test-dataset.txt", data2, labels2);
    auto start2 = std::chrono::high_resolution_clock::now();
    // Test Validator with {1, 15, 27}
    Validator validator2;
    std::vector<int> feature_subset_large = {1, 15, 27};
    double accuracy_large = validator2.Validate(data2, labels2, feature_subset_large);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end2 - start2;
    std::cout << "Accuracy with features {1, 15, 27}: " << accuracy_large * 100 << "%\n";
    std::cout << "Time spent on validation: " << elapsed.count() << " seconds\n";

}

void test_search() {
    //START OF NORMAL FEATURE SELECTION
    std::cout << "Welcome to Pranay Thakur's Feature Selection Algorithm.\n";
    std::cout << "Type in the name of the file to test: ";
    std::string fileName;
    std::cin >> fileName;
    Problem problem(fileName);
    std::cout << std::endl;
    std::cout << "Type the number of the algorithm you want to run.\n";
    std::cout << std::endl;
    std::cout << "1. Forward Selection\n";
    std::cout << "2. Backward Elimination\n";
    std::cout << "3. Bi-Directional Search (Custom Algorithm)\n";
    std::cout << std::endl;
    std::cout << std::endl;
   

    //selects the algorithm
    int choice;
    std::cin >> choice;

    std::cout << "This dataset has "<< problem.features();
    std::cout  <<" features. (not including the class attribute), with ";
    std::cout << problem.instances() << " instances." << std::endl;

    //5 = f1, f2, f3, f4, f5
    //1 = f1
    int total_features = problem.features();
    
    std::cout << "Please wait while I normalize the data...";
    problem.normalize();
    std::cout << "Done!" << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Running nearest neighbor with no features (default rate), using “leaving-one-out” evaluation," << std::endl;
    std::cout << "I get an accuracy of " << problem.default_rate()*100<< "%"<<std::endl;
    
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
}
/*
Small Dataset Results
    Forward: Feature Subset: {5,3}, Acc: 0.92%
    Backward: Feature Subset: {2,3,4,5}, Acc: 0.83%
Large Dataset Results
    Forward: Feature Subset: {27,1}, Acc: 0.955%
    Backward: Feature Subset: {1,2,3,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40}, Acc: 0.711%
Titanic Dataset Results
    Forward: Feature Subset: {2}, Acc:0.78%
    Backward: Feature Subset: {2}, Acc:0.78%
*/

int main() {

    //test_classifier("small-test-dataset.txt", {3, 5, 7});
    //test_classifier("large-test-dataset.txt", {1, 15, 27});
    //test_classifier("output.txt", {1,2,3, 4, 5, 6});
    //test_validator();
    test_search();
    return 0;
}
