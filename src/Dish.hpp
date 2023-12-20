#ifndef Dish_hpp
#define Dish_hpp

#include "Ingredient.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <optional>

namespace dishReviewService {
class Ingredient;

class Dish {
private:
    // IngredientWrapper contains the ingredient object and the text to display for the recipe
    struct IngredientWrapper {
        std::shared_ptr<Ingredient> ingredient;
        std::string ingredientText;
        
        //IngredientWrapper(const std::shared_ptr<Ingredient>& newIngredient, const std::string& newText);
    };
    friend std::ostream& operator<<(std::ostream& output, const IngredientWrapper& outputIngredient);
    
    std::string displayName;
    std::map<std::string, IngredientWrapper> ingredientsList;
    std::vector<std::string> toolsList;
    std::vector<std::string> instructions;
    // By convention in the ingredients class,
    // we'd add a restaurants vector here with corresponding classes
    
    const int MAX_LINE_LENGTH = 70;
    std::string formatStep(const int& stepNumber, const std::string& stepText) const;
    
public:
    Dish(const std::string& newDisplayName);
    ~Dish();
    
    void addIngredient(const std::shared_ptr<Ingredient>& newIngredient, const std::string& newText, const std::string& newIngredientId);
    void removeIngredient(const std::string& keyToRemove);
    void addTool(const std::string& newTool);
    void removeTool(const int& indexToRemove);
    void addStep(const std::string& newStep);
    void removeStep(const int& indexToRemove);
    
    std::string getDisplayName() const;
    std::map<std::string, IngredientWrapper> getIngredients() const;
    std::vector<std::string> getTools() const;
    std::vector<std::string> getInstructions() const;
    
    friend std::ostream& operator<<(std::ostream& output, const Dish& outputDish);
    void printDetailed(std::ostream& output) const;
};

}
#endif
