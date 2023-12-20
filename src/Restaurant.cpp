#include "Restaurant.hpp"

using std::string;
using std::shared_ptr;
using std::map;
using std::ostream;
using std::to_string;

namespace dishReviewService{

Restaurant::Restaurant(const string& newDisplayName, const Address& newRestaurantAddress) :
displayName(newDisplayName),
restaurantAddress(newRestaurantAddress) {}

Restaurant::~Restaurant() {}

void Restaurant::setAddress(const Address& newRestaurantAddress) {
    restaurantAddress = newRestaurantAddress;
}

void Restaurant::addDish(const std::shared_ptr<Dish>& newDish, const string& newDishKey) {
    restaurantMenu[newDishKey] = newDish;
}

void Restaurant::removeDish(const string& keyToRemove) {
    restaurantMenu.erase(keyToRemove);
}

}
