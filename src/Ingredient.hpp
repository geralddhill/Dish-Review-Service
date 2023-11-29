#ifndef Ingredient_hpp
#define Ingredient_hpp

#include "Dish.hpp"
#include <iostream>
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
    Ingredient(std::string newDisplayName);
    ~Ingredient();
    
    void toggleAllergen();
    void addDish(std::shared_ptr<Dish> newDish);
    
    std::string getDisplayName();
    bool getAllergenStatus();
    std::vector<std::shared_ptr<Dish>> getDishesUsedIn();
    
    friend std::ostream& operator<<(std::ostream& output, const Ingredient& outputIngredient);
};

}
#endif /* Ingredient_hpp */
