#ifndef RestaurantInterface_hpp
#define RestaurantInterface_hpp

#include "Restaurant.hpp"
#include "Database.hpp"

namespace dishReviewService {

const std::string FILE_PREFIX = "../../../data/";
const std::string RESTAURANTS_FILE_LOCATION = FILE_PREFIX + "restaurants.txt";

class RestaurantInterface {
private:
    // Makes a string (like a display name) all lowercase with no spaces
    std::string convertToId(const std::string& input) const ;
    void addRestaurant() const;
    
public:
    RestaurantInterface();
    ~RestaurantInterface();

    void runRestaurantView() const;
};

}

#endif
