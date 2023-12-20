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
std::ostream& operator<<(std::ostream& output, const Address& outputAddress);

class Restaurant {
private:
    std::string displayName;
    Address restaurantAddress;
    std::map<std::string, std::shared_ptr<Dish>> appertizerMenu;
    std::map<std::string, std::shared_ptr<Dish>> entreeMenu;
    std::map<std::string, std::shared_ptr<Dish>> dessertMenu;
public:
    // Constructor/Destructor
    Restaurant(const std::string& newDisplayName, const Address& newRestaurantAddress);
    ~Restaurant();
    
    // Returns the address
    Address getAddress();
    // Returns the menus
    std::map<std::string, std::shared_ptr<Dish>> getAppetizers();
    std::map<std::string, std::shared_ptr<Dish>> getEntrees();
    std::map<std::string, std::shared_ptr<Dish>> getDesserts();
    
    // Sets the address of the restaurant
    void setAddress(const Address& newRestaurantAddress);
    // Adds a dish to the correct menu
    void addDish(const std::shared_ptr<Dish>& newDish, const std::string& newDishKey);
    // Removes a dish from the correct menu
    void removeDish(const std::string& keyToRemove);
    
    // Multiple ways to print the restaurant
    friend std::ostream& operator<<(std::ostream& output, const Restaurant& outputRestaurant);
    void printDetailed(std::ostream& output) const;
};



}

#endif /* Restaurant_hpp */
