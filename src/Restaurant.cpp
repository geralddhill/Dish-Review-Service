#include "Restaurant.hpp"

using std::string;
using std::shared_ptr;
using std::map;
using std::ostream;
using std::to_string;
using std::cout;

namespace dishReviewService{

//
std::ostream& operator<<(std::ostream& output, const Address& outputAddress) {
    output << outputAddress.streetAddress << "\n";
    output << outputAddress.city << ", " << outputAddress.stateAbbreviated << "\n";
    output << outputAddress.zipcode << "\n";
    
    return output;
}

// Restaurant constructor
Restaurant::Restaurant(const string& newDisplayName, const Address& newRestaurantAddress) :
displayName(newDisplayName),
restaurantAddress(newRestaurantAddress) {}

Restaurant::~Restaurant() {}

// Simple accessor functions
Address Restaurant::getAddress() {
    return restaurantAddress;
}

std::map<std::string, std::shared_ptr<Dish>> Restaurant::getAppetizers() {
    return appertizerMenu;
}

std::map<std::string, std::shared_ptr<Dish>> Restaurant::getEntrees() {
    return entreeMenu;
}

std::map<std::string, std::shared_ptr<Dish>> Restaurant::getDesserts() {
    return dessertMenu;
}


void Restaurant::setAddress(const Address& newRestaurantAddress) {
    restaurantAddress = newRestaurantAddress;
}

void Restaurant::addDish(const std::shared_ptr<Dish>& newDish, const string& newDishKey) {
    // Adds to correct menu
    switch (newDish->getType()) {
        case Appetizer:
            appertizerMenu[newDishKey] = newDish;
            break;
        case Entree:
            entreeMenu[newDishKey] = newDish;
            break;
        case Dessert:
            dessertMenu[newDishKey] = newDish;
            break;
    }
}

void Restaurant::removeDish(const string& keyToRemove) {
    appertizerMenu.erase(keyToRemove);
    entreeMenu.erase(keyToRemove);
    dessertMenu.erase(keyToRemove);
}



std::ostream& operator<<(std::ostream& output, const Restaurant& outputRestaurant) {
    output << outputRestaurant.displayName;
    return output;
}

void Restaurant::printDetailed(ostream& output) const {
    // Prints name
    cout << displayName << "\n\n";
    // Prints address;
    cout << restaurantAddress << "\n";
    
    // Prints the menu;
    cout << "Appetizers:\n";
    for (auto const& item: appertizerMenu) {
        cout << *item.second << "\n";
    }
    cout << "\n";
    cout << "Entrees:\n";
    for (auto const& item: entreeMenu) {
        cout << *item.second << "\n";
    }
    cout << "\n";
    cout << "Desserts:\n";
    for (auto const& item: dessertMenu) {
        cout << *item.second << "\n";
    }
}

} /* Restaurant_cpp */


