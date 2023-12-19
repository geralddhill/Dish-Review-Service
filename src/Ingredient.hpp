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
    Ingredient(const std::string& newDisplayName);
    ~Ingredient();
    
    void toggleAllergen();
    
    std::string getDisplayName() const;
    bool getAllergenStatus() const;
    
    friend std::ostream& operator<<(std::ostream& output, const Ingredient& outputIngredient);
};

}
#endif /* Ingredient_hpp */
