#include "Problem.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include "Validator.cpp"

double Problem::evaluate(const std::vector<int>& feature_set) {
    /*
    // returns random number
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(20.0, 80.0);

    double raw_score = dis(gen);
    // return dis(gen);

    //rounds to tenths place
    return std::round(raw_score * 10.0) / 10.0;
    */
    Validator validator;
    double accuracy = validator.Validate(data, labels, feature_set);
    return accuracy;

}

void Problem::forward_selection(int total_features) {
    std::cout << "Beginning Forward Selection...\n\n";

    std::vector<int> current_best_set;
    double current_best_score = 0.0;

    for (int level = 1; level <= total_features; ++level) {
        Node best_node({}, -std::numeric_limits<double>::infinity());

        // next group of sets
        // std::cout << "Level " << level << ":\n";

        for (int feature = 1; feature <= total_features; ++feature) {
            // check duplicates
            if (std::find(current_best_set.begin(), current_best_set.end(), feature) != current_best_set.end()) {
                continue;
            }

            // make new subset
            std::vector<int> new_set = current_best_set;
            new_set.push_back(feature);

            // check subset
            double score = evaluate(new_set);
            std::cout << "  Using feature(s) " << Node(new_set).to_string() << " accuracy is " << score*100 << "%\n";
            if (score > best_node.score) {
                best_node = Node(new_set, score);
            }
        }
        std::cout << "\n";

        if (best_node.score > current_best_score) {
            current_best_set = best_node.features;
            current_best_score = best_node.score;
            std::cout << "Feature set " << best_node.to_string() << " was best, accuracy is " << best_node.score << "%\n\n";
        } else {
            std::cout << "(Warning: Accuracy has decreased!)\n";
            break;
        }
    }

    std::cout << "Finished search!! The best feature subset is " << Node(current_best_set).to_string() << ", which has an accuracy of " << current_best_score << "%\n";
}


void Problem::backward_elimination(int total_features) {
    std::cout << "Beginning Backward Elimination...\n\n";

    // Start with the full set of features
    std::vector<int> current_best_set;
    for (int feature = 1; feature <= total_features; ++feature) {
        current_best_set.push_back(feature);
    }

    // Evaluate the full feature set
    double current_best_score = evaluate(current_best_set);
    std::cout << "  Using feature(s) " << Node(current_best_set).to_string()
              << " accuracy is " << current_best_score << "%\n\n";

    // Begin the backward elimination process
    for (int level = total_features; level > 1; --level) {
        Node best_node({}, -std::numeric_limits<double>::infinity());

        // Try removing each feature and evaluate the new set
        for (int feature : current_best_set) {
            // Create a new set without the current feature
            std::vector<int> new_set = current_best_set;
            new_set.erase(std::remove(new_set.begin(), new_set.end(), feature), new_set.end());

            // Evaluate the new feature set
            double score = evaluate(new_set);
            std::cout << "  Using feature(s) " << Node(new_set).to_string()
                      << " accuracy is " << score << "%\n";

            // Update the best node if the new score is better
            if (score > best_node.score) {
                best_node = Node(new_set, score);
            }
        }
        std::cout << "\n";

        // Decide whether to update the current best set
        if (best_node.score > current_best_score) {
            current_best_set = best_node.features;
            current_best_score = best_node.score;
            std::cout << "Feature set " << best_node.to_string()
                      << " was best, accuracy is " << best_node.score << "%\n\n";
        } else {
            std::cout << "(Warning: Accuracy has decreased!)\n";
            break;
        }
    }

    // Final output
    std::cout << "Finished search!! The best feature subset is " << Node(current_best_set).to_string()
              << ", which has an accuracy of " << current_best_score << "%\n";
}

//ad custom algorithm
void Problem::custom_algorithm(int total_features) {
    std::cout << "Beginning Custom Algorithm (Bi-Directional Search)...\n\n";

    // Initialize forward and backward sets
    std::vector<int> forward_set;
    std::vector<int> backward_set;
    for (int feature = 1; feature <= total_features; ++feature) {
        backward_set.push_back(feature);
    }

    double forward_score = 0.0;
    double backward_score = evaluate(backward_set);

    std::cout << "Initial backward set " << Node(backward_set).to_string()
              << " accuracy is " << backward_score << "%\n\n";

    // Bi-directional search
    while (true) {
        // Add the best feature to forward_set
        Node best_forward({}, -std::numeric_limits<double>::infinity());
        for (int feature = 1; feature <= total_features; ++feature) {
            if (std::find(forward_set.begin(), forward_set.end(), feature) != forward_set.end()) {
                continue; // Skip features that are already in the forward set
            }

            std::vector<int> new_set = forward_set;
            new_set.push_back(feature);
            double score = evaluate(new_set);

            std::cout << "  Forward step: Using feature(s) " << Node(new_set).to_string()
                      << " accuracy is " << score << "%\n";

            if (score > best_forward.score) {
                best_forward = Node(new_set, score);
            }
        }

        if (best_forward.score > forward_score) {
            forward_set = best_forward.features;
            forward_score = best_forward.score;
            std::cout << "  Forward: Feature set " << best_forward.to_string()
                      << " was best, accuracy is " << best_forward.score << "%\n\n";
        }

        // Remove the least important feature from backward_set
        Node best_backward({}, -std::numeric_limits<double>::infinity());
        for (int feature : backward_set) {
            std::vector<int> new_set = backward_set;
            new_set.erase(std::remove(new_set.begin(), new_set.end(), feature), new_set.end());
            double score = evaluate(new_set);

            std::cout << "  Backward step: Using feature(s) " << Node(new_set).to_string()
                      << " accuracy is " << score << "%\n";

            if (score > best_backward.score) {
                best_backward = Node(new_set, score);
            }
        }

        if (best_backward.score > backward_score) {
            backward_set = best_backward.features;
            backward_score = best_backward.score;
            std::cout << "  Backward: Feature set " << best_backward.to_string()
                      << " was best, accuracy is " << best_backward.score << "%\n\n";
        }

        // Checking the convergence
        if (forward_set == backward_set) {
            std::cout << "Forward and Backward searches have converged!\n";
            break;
        }

        // Stopping if there is no improvement in either direction
        if (best_forward.score <= forward_score && best_backward.score <= backward_score) {
            std::cout << "(Warning: No improvement in both directions!)\n";
            break;
        }
    }

    // Displaying final output
    std::cout << "Finished Bi-Directional Search!! The best feature subset is " << Node(forward_set).to_string()
              << ", which has an accuracy of " << forward_score << "%\n";
}

void Problem::normalize() {
    if (data.empty() || data[0].empty()) {
        // No data to normalize
        return;
    }

    int num_instances = static_cast<int>(data.size());
    int num_features = static_cast<int>(data[0].size());

    for (int j = 0; j < num_features; ++j) {
        // Find min and max for feature j
        double min_val = data[0][j];
        double max_val = data[0][j];

        for (int i = 1; i < num_instances; ++i) {
            if (data[i][j] < min_val) {
                min_val = data[i][j];
            }
            if (data[i][j] > max_val) {
                max_val = data[i][j];
            }
        }

        double range = max_val - min_val;
        if (range == 0.0) {
            // All values are the same, no normalization needed
            continue;
        }

        // Normalize feature j using min-max scaling
        for (int i = 0; i < num_instances; ++i) {
            data[i][j] = (data[i][j] - min_val) / range;
        }
    }
}
