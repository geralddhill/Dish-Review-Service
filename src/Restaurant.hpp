#ifndef Restaurant_hpp
#define Restaurant_hpp

#include "Dish.hpp"
#include <map>

namespace dishReviewService {

struct Address {
    std::string streetAddress;
    std::string city;
    std::string stateAbbreviated;
    int zipcode;
};

class Restaurant {
private:
    std::string displayName;
    Address restaurantAddress;
    std::map<std::string, std::shared_ptr<Dish>> restaurantMenu;
public:
    Restaurant(const std::string& newDisplayName, const Address& newRestaurantAddress);
    ~Restaurant();

    void setAddress(const Address& newRestaurantAddress);
    void addDish(const std::shared_ptr<Dish>& newDish, const std::string& newDishKey);
    void removeDish(const std::string& keyToRemove);

};



}

#endif /* Restaurant_hpp */
