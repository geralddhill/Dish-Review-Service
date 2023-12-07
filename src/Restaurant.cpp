#include "Restaurant.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::ostream;
using std::to_string;

Restaurant::Restaurant(string newDisplayName) : 
    displayName(newDisplayName) {}

Restaurant::~Restaurant() {}