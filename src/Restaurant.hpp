#ifndef Restaurant_hpp
#define Restaurant_hpp

#include "Dish.hpp"
#include <map>

namespace dishReviewService {

class Restaurant {
private:
    std::string displayName;
    std::vector<std::string, std::shared_ptr<Dish>> restaurantMenu;
public:
    Restaurant(std::string newDisplayName);
    ~Restaurant();

    void addDish(const std::shared_ptr<Dish>& newDish, const std::string& newDishKey);
    void removeDish(const std::string& keyToRemove);

}



}

#endif /* Restaurant_hpp */