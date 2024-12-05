#include <vector>
#include <cmath>
#include <limits>

class Classifier {
public:
    // data
    std::vector<std::vector<double>> training_data;
    std::vector<int> training_labels;

    // train stores the data
    void Train(const std::vector<std::vector<double>>& data, const std::vector<int>& labels) {
        training_data = data;
        training_labels = labels;
    }

    // test finds nearest neighbor, returns predicted class label
    int Test(const std::vector<double>& test_instance) {
        double min_distance = std::numeric_limits<double>::max();
        int predicted_label = -1;

        // nearest neighbor
        for (size_t i = 0; i < training_data.size(); ++i) {
            double distance = 0.0;
            for (size_t j = 0; j < test_instance.size(); ++j) {
                distance += std::pow(test_instance[j] - training_data[i][j], 2);
                // distance += (test_instance - training_data) * (test_instance - training_data)
            }
            distance = std::sqrt(distance);
            // distance = distance/distance;

            if (distance < min_distance) {
                min_distance = distance;
                predicted_label = training_labels[i];
            }
        }
        return predicted_label;
    }
};

