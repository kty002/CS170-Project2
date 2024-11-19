#include "Problem.h"
#include <iostream>
#include <algorithm>
#include <limits>

double Problem::evaluate(const std::vector<int>& feature_set) {
    // returns random number
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(20.0, 80.0);

    double raw_score = dis(gen);
    // return dis(gen);

    //rounds to tenths place
    return std::round(raw_score * 10.0) / 10.0;
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
            std::cout << "  Using feature(s) " << Node(new_set).to_string() << " accuracy is " << score << "%\n";
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
    std::cout << "Beginning Custom Algorithm...\n";
    return;
}