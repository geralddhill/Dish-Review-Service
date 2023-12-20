#include "Restaurant.hpp"

using std::string;
using std::shared_ptr;
using std::map;
using std::ostream;
using std::to_string;

namespace dishReviewService{

Restaurant::Restaurant(const std::string& newDisplayName, const Address& newRestaurantAddress) :
displayName(newDisplayName),
restaurantAddress(newRestaurantAddress) {}

Restaurant::~Restaurant() {}

}
