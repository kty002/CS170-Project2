#ifndef VALIDATOR_CPP
#define VALIDATOR_CPP
#include "Classifier.cpp"
#include <vector>
// #include <chrono> 
// https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
// this might be helpful for tracking time

class Validator {
public:
    // do leave-one-out validation
    // data, labels, feature_subset
    double Validate(const std::vector<std::vector<double>>& data, const std::vector<int>& labels, const std::vector<int>& feature_subset) {
        int correct_predictions = 0;

        for (size_t i = 0; i < data.size(); ++i) {
            // leave out current instance
            std::vector<std::vector<double>> train_data;
            std::vector<int> train_labels;
            for (size_t j = 0; j < data.size(); ++j) {
                // if (i == j) {
                if (i != j) {
                    train_data.push_back(FilterFeatures(data[j], feature_subset));
                    train_labels.push_back(labels[j]);
                }
            }

            // train and test classifier
            Classifier classifier;
            classifier.Train(train_data, train_labels);
            std::vector<double> test_instance = FilterFeatures(data[i], feature_subset);
            int predicted_label = classifier.Test(test_instance);

            if (predicted_label == labels[i]) {
                ++correct_predictions;
        }
        // cout << "Step " << i + 1 << "/" << total_instances;
        // cout << "Predicted = " << predicted_label;
        // cout << "Actual = " << labels[i];
        //  if (predicted_label == labels[i]) {
                // cout << "Correct = True";
        // }
        // else {
        //     cout << "Correct = False";
        // }
        // cout << "Time spent on step: " << TimeSpentOnStep;
        }

        return static_cast<double>(correct_predictions) / data.size();
    }

private:
    // filter features based on subset
    std::vector<double> FilterFeatures(const std::vector<double>& instance, const std::vector<int>& feature_subset) {
        std::vector<double> filtered;
        for (int index : feature_subset) {
            filtered.push_back(instance[index - 1]); // Adjust for 1-based index
        }
        return filtered;
    }
};


#endif // VALIDATOR_CPP