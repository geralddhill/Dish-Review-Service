#ifndef Dish_hpp
#define Dish_hpp

#include "Ingredient.hpp"
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
    
    void addIngredient(std::shared_ptr<Ingredient> newIngredient);
    void removeIngredient(std::shared_ptr<Ingredient> existingIngredient);
    void addTool(std::string newTool);
    void removeTool(std::string existingTool);
    void addStep(std::string newStep);
    void removeStep(std::string existingStep);
    
    std::string getDisplayName();
    std::vector<std::shared_ptr<Ingredient>> getIngredients();
    std::vector<std::string> getTools();
    std::vector<std::string> getInstructions();
};

}
#endif
