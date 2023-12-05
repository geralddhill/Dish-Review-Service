#ifndef Restaurant_hpp
#define Restaurant_hpp

#include "Dish.hpp"
#include <iostream>
#include <string>

namespace dishReviewService {

class Restaurant {
private:
    std::string displayName;
    std::vector<std::shared_ptr<
public:
    Restaurant(std::string newDisplayName);
    ~Restaurant();

}



}

#endif /* Restaurant_hpp */