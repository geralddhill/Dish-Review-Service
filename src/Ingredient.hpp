#ifndef Ingredient_hpp
#define Ingredient_hpp

#include "Dish.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace dishReviewService {

class Ingredient {
private:
    std::string displayName;
    bool isAllergen;
public:
    // Constructor and Deconstructor
    Ingredient(const std::string& newDisplayName);
    ~Ingredient();
    
    // Toggles whether or not the ingredient can be an allergen
    void toggleAllergen();
    
    // Simple accessor function
    std::string getDisplayName() const;
    bool getAllergenStatus() const;
    
    // << Overload in order to print
    friend std::ostream& operator<<(std::ostream& output, const Ingredient& outputIngredient);
};

}
#endif /* Ingredient_hpp */
