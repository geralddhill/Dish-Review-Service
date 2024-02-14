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

// Used in getType() function
enum DishType {
    Appetizer,
    Entree,
    Dessert
};

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
    // Constructor and Deconstructor
    Dish(const std::string& newDisplayName);
    virtual ~Dish();
    
    // Pure virtual function that allows us to access the dishType
    virtual DishType getType() = 0;

    // Adds and Removes from ingredientsList map using a newIngredient pointer and a key
    void addIngredient(const std::shared_ptr<Ingredient>& newIngredient, const std::string& newText, const std::string& newIngredientId);
    void removeIngredient(const std::string& keyToRemove);

    // Adds and Removes from toolList vector using a newTool and an index in order to remove it
    void addTool(const std::string& newTool);
    void removeTool(const int& indexToRemove);

    // Adds and Removes from instructions vector using a newStep and an index in order to remove it
    void addStep(const std::string& newStep);
    void removeStep(const int& indexToRemove);
    
    // Simple accessor functions in order to return dish name, ingredients, tools, and instructions
    std::string getDisplayName() const;
    std::map<std::string, IngredientWrapper> getIngredients() const;
    std::vector<std::string> getTools() const;
    std::vector<std::string> getInstructions() const;
    
    // Multiple ways to print the dish
    friend std::ostream& operator<<(std::ostream& output, const Dish& outputDish);
    void printDetailed(std::ostream& output) const;
};


// Child classes for Dish
// each overrides the getType() function and returns its corresponding type
class AppetizerDish : public Dish {
public:
    using Dish::Dish;
    virtual ~AppetizerDish();
    
    virtual DishType getType();
};

class EntreeDish : public Dish {
public:
    using Dish::Dish;
    virtual ~EntreeDish();
    
    virtual DishType getType();
};

class DessertDish : public Dish {
public:
    using Dish::Dish;
    virtual ~DessertDish();
    
    virtual DishType getType();
};

}
#endif
