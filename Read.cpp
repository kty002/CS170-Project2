#ifndef READ_DATA_SET
#define READ_DATA_SET

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <cmath>
#include <limits>
#include <vector>

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

#endif 
