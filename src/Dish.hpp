#ifndef Dish_hpp
#define Dish_hpp

#include "Ingredient.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace dishReviewService {
class Ingredient;

class Dish {
private:
    std::string displayName;
    std::vector<std::shared_ptr<Ingredient>> ingredientsList;
    std::vector<std::string> toolsList;
    std::vector<std::string> instructions;
    // By convention in the ingredients class,
    //we'd add a restaurants vector here with corresponding classes
    
public:
    Dish() {}
    ~Dish() {}
    
    void addIngredient(const std::shared_ptr<Ingredient>& newIngredient);
    void removeIngredient(const std::shared_ptr<Ingredient>& existingIngredient);
    void addTool(const std::string& newTool);
    void removeTool(const std::string& existingTool);
    void addStep(const std::string& newStep);
    void removeStep(const std::string& existingStep);
    
    std::string getDisplayName();
    std::vector<std::shared_ptr<Ingredient>> getIngredients();
    std::vector<std::string> getTools();
    std::vector<std::string> getInstructions();
    
    friend std::ostream& operator<<(std::ostream& output, const Dish& outputDish);
};

}
#endif
