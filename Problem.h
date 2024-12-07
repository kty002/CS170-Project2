#ifndef PROBLEM_H
#define PROBLEM_H

#include "Node.h"
#include <vector>
#include <string>
#include <random>
extern void ReadDataset(const std::string& filename, std::vector<std::vector<double>>& data, std::vector<int>& labels);
class Problem {
public:
    Problem(std::string filename) {
        fname = filename; 
        ReadDataset(fname, data, labels);
    }
    void forward_selection(int total_features);
    void backward_elimination(int total_features);
    void custom_algorithm(int total_features);
    double default_rate() {
        return evaluate({});
    }
    int features(){
        return data[0].size();
    }
    int instances() {
        return data.size();
    }

    void normalize();

private:
    double evaluate(const std::vector<int>& feature_set);
    std::string fname;
    std::vector<std::vector<double>> data;
    std::vector<int> labels;
};

#endif // PROBLEM_H
