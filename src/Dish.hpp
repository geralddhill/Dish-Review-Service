#ifndef Dish_hpp
#define Dish_hpp

#include "Ingredient.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace dishReviewService {
class Ingredient;

class Dish {
private:
    struct IngredientWrapper {
        std::shared_ptr<Ingredient> ingredient;
        std::string ingredientText;
        
        IngredientWrapper(std::shared_ptr<Ingredient> newIngredient, std::string newText);
    };
    friend std::ostream& operator<<(std::ostream& output, const IngredientWrapper& outputIngredient);
    
    std::string displayName;
    std::vector<IngredientWrapper> ingredientsList;
    std::vector<std::string> toolsList;
    std::vector<std::string> instructions;
    // By convention in the ingredients class,
    // we'd add a restaurants vector here with corresponding classes
    
    const int MAX_LINE_LENGTH = 70;
    std::string formatStep(int stepNumber, std::string stepText) const;
    
public:
    Dish(std::string newDisplayName);
    ~Dish();
    
    void addIngredient(const std::shared_ptr<Ingredient>& newIngredient, const std::string& newText);
    void removeIngredient(const int& indexToRemove);
    void addTool(const std::string& newTool);
    void removeTool(const int& indexToRemove);
    void addStep(const std::string& newStep);
    void removeStep(const int& indexToRemove);
    
    std::string getDisplayName() const;
    std::vector<std::shared_ptr<Ingredient>> getIngredients() const;
    std::vector<std::string> getTools() const;
    std::vector<std::string> getInstructions() const;
    
    friend std::ostream& operator<<(std::ostream& output, const Dish& outputDish);
    void printDetailed(std::ostream& output) const;
};

}
#endif
