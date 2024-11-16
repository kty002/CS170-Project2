#ifndef PROBLEM_H
#define PROBLEM_H

#include "Node.h"
#include <vector>
#include <string>
#include <random>

class Problem {
public:
    void forward_selection(int total_features);
    void backward_elimination(int total_features);
    void custom_algorithm(int total_features);

private:
    double evaluate(const std::vector<int>& feature_set);
};

#endif // PROBLEM_H
