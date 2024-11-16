#include "Node.h"
#include <sstream>

std::string Node::to_string() const {
    std::ostringstream oss;
    oss << "{";
    for (size_t i = 0; i < features.size(); ++i) {
        oss << features[i];
        if (i < features.size() - 1) oss << ",";
    }
    oss << "}";
    return oss.str();
}
