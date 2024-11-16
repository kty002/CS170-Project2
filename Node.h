#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

class Node {
public:
    std::vector<int> features;  // features f1 f2 f3
    double score;               // score/accuracy

    Node(const std::vector<int>& feature_set = {}, double evaluation_score = 0.0)
        : features(feature_set), score(evaluation_score) {}

    std::string to_string() const; // set -> string
};

#endif // NODE_H
