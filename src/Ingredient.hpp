#ifndef Ingredient_hpp
#define Ingredient_hpp

#include "Dish.hpp"
#include <string>
#include <vector>
#include <memory>

namespace dishReviewService {
class Dish;

class Ingredient {
private:
    std::string displayName;
    bool isAllergen;
    std::vector<std::shared_ptr<Dish>> dishesUsedIn; // Idk if this is how we want to do it
public:
    Ingredient();
    ~Ingredient();
    
    void toggleAllergen();
    
    std::string getDisplayName();
    bool getAllergenStatus();
    std::vector<std::shared_ptr<Dish>> getDishesUsedIn;
};

}
#endif /* Ingredient_hpp */
