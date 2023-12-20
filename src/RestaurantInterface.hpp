#ifndef RestaurantInterface_hpp
#define RestaurantInterface_hpp

#include "Restaurant.hpp"
#include "Database.hpp"

namespace dishReviewService {

const std::string FILE_PREFIX = "../../../data/";
const std::string RESTAURANTS_FILE_LOCATION = FILE_PREFIX + "restaurants.txt";
const std::string INGREDIENTS_FILE_LOCATION = FILE_PREFIX + "ingredients.txt";

class RestaurantInterface {
private:
    // Various menu options as enums
    enum MainMenuOption {
        Exit,
        View_Restaurant,
        View_Database
    };
    
    enum DatabaseMenuOption {
        D_Back,
        Ingredients,
        Dishes,
        Restaurants
    };
    
    enum RestaurantMenuOption {
        R_Back,
        Set_Address,
        View_Dish,
        Add_Dish,
        Remove_Dish
    };
    
    // Runs options from the main menu
    void viewRestaurant() const;
    void viewDatabase() const;
    
    // Adds a restaurant to the file and database
    void addRestaurant() const;
    // Give options for restaurant
    void viewRestaurantMenu(std::string currentRestaurantId, std::shared_ptr<Restaurant> currentRestaurant) const;
    
    void editAddressFile(Address oldAddress, Address newAddress) const;
    void viewDish(std::shared_ptr<Restaurant> restaurant) const;
    void addDish(std::string restaurantId, std::shared_ptr<Restaurant> restaurant) const;
    void removeDish() const;
    
    // Makes a string (like a display name) all lowercase with no spaces
    std::string convertToId(const std::string& input) const;
    // Creates an address with user input
    Address createAddress() const;
    
public:
    RestaurantInterface();
    ~RestaurantInterface();

    // Starts the interface
    void run() const;
};

}

#endif
