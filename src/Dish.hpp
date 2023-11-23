#ifndef Dish_hpp
#define Dish_hpp

#include <string>
#include <vector>

namespace dishReviewService {

class Dish {
private:
    std::vector<std::string> ingredientsList;
    std::vector<std::string> toolsList;
    std::vector<std::string> instructions;
    
public:
    Dish() {}
    ~Dish() {}
    
    void addIngredient(std::string newIngredient);
    void removeIngredient(std::string existingIngredient);
    void addTool(std::string newTool);
    void removeTool(std::string existingTool);
    void addStep(std::string newStep);
    void removeStep(std::string existingStep);
    
    std::vector<std::string> getIngredients();
    std::vector<std::string> getTools();
    std::vector<std::string> getInstructions();
};

}
#endif
