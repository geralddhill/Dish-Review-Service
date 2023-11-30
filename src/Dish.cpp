#include "Dish.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::ostream;
using std::to_string;

namespace dishReviewService {

Dish::IngredientWrapper::IngredientWrapper(std::shared_ptr<Ingredient> newIngredient, std::string newText) :
    ingredient(newIngredient),
    ingredientText(newText) {}

ostream& operator<<(ostream& output, const Dish::IngredientWrapper& outputIngredient) {
    output << outputIngredient.ingredientText;
    return output;
}



Dish::Dish(string newDisplayName) :
    displayName(newDisplayName) {}

Dish::~Dish() {}


void Dish::addIngredient(const std::shared_ptr<Ingredient>& newIngredient, const std::string& newText) {
    IngredientWrapper newWrapper(newIngredient, newText);
    ingredientsList.push_back(newWrapper);
}

void Dish::removeIngredient(const int& indexToRemove) {
    ingredientsList.erase(ingredientsList.begin()+indexToRemove);
}

void Dish::addTool(const string& newTool) {
    toolsList.push_back(newTool);
}

void Dish::removeTool(const int& indexToRemove) {
    toolsList.erase(toolsList.begin()+indexToRemove);
}

void Dish::addStep(const string& newStep) {
    instructions.push_back(newStep);
}

void Dish::removeStep(const int& indexToRemove) {
    instructions.erase(instructions.begin()+indexToRemove);
}



string Dish::getDisplayName() const {
    return displayName;
}

vector<shared_ptr<Ingredient>> Dish::getIngredients() const {
    vector<shared_ptr<Ingredient>> outputIngredientsList;
    
    for (auto const& ingredientWrapper: ingredientsList) {
        outputIngredientsList.push_back(ingredientWrapper.ingredient);
    }
    
    return outputIngredientsList;
}

vector<string> Dish::getTools() const {
    return toolsList;
}

vector<string> Dish::getInstructions() const {
    return instructions;
}



string Dish::formatStep(int stepNumber, string stepText) const {
    string outputString;
    string word;
    string line;
    
    line = to_string(stepNumber) + ")\t";
    
    for (int cursor = 0; cursor < stepText.length(); cursor++)
        {
            if (!isspace(stepText[cursor]))
            {
                word += stepText[cursor];
            }
            else
            {
                if ( (line.length() + word.length()) > MAX_LINE_LENGTH)
                {
                    outputString = outputString + line + "\n";
                    line = "\t";
                }
                line = line + word + " ";
                word.clear();
            }
        }
        line = line + word;
        word.clear();
        outputString = outputString + line;
        line.clear();

        return outputString;
}



ostream& operator<<(ostream& output, const Dish& outputDish) {
    output << outputDish.displayName;
    return output;
}

void Dish::printDetailed(ostream& output) const {
    output << displayName << "\n\n";
    
    output << "Ingredients:\n";
    for (auto const& ingredient: ingredientsList) {
        output << "\t" << ingredient << "\n";
    }
    output << "\n";
    
    output << "Tools:\n";
    for (auto const& tool: toolsList) {
        output << "\t" << tool << "\n";
    }
    output << "\n";
    
    output << "Instructions:\n";
    int stepNumber = 1;
    for (auto const& step: instructions) {
        output << formatStep(stepNumber, step) << "\n";
        stepNumber++;
    }
}

}
