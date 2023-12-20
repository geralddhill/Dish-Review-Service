#include "Dish.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::map;
using std::ostream;
using std::to_string;

namespace dishReviewService {

/*Dish::IngredientWrapper::IngredientWrapper(const shared_ptr<Ingredient>& newIngredient, const string& newText) :
    ingredient(newIngredient),
    ingredientText(newText) {}*/

ostream& operator<<(ostream& output, const Dish::IngredientWrapper& outputIngredient) {
    output << outputIngredient.ingredientText;
    return output;
}


// Constructor and Deconstructor
Dish::Dish(const string& newDisplayName) :
    displayName(newDisplayName) {}

Dish::~Dish() {}

// Adds ingredient and ingredient text (i.e. "2 slices of cheese") into a wrapper then inserts wrapper into ingredientsList map
void Dish::addIngredient(const std::shared_ptr<Ingredient>& newIngredient, const string& newText, const string& newIngredientId) {
    IngredientWrapper newWrapper;
    newWrapper.ingredient = newIngredient;
    newWrapper.ingredientText = newText;
    ingredientsList[newIngredientId] = newWrapper;
}

void Dish::removeIngredient(const std::string& keyToRemove) {
    ingredientsList.erase(keyToRemove);
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


// Simple accessor functions
string Dish::getDisplayName() const {
    return displayName;
}

map<string, Dish::IngredientWrapper> Dish::getIngredients() const {
    return ingredientsList;
}

vector<string> Dish::getTools() const {
    return toolsList;
}

vector<string> Dish::getInstructions() const {
    return instructions;
}


// Takes in Step info and Step Number and formats in order to print properly
string Dish::formatStep(const int& stepNumber, const string& stepText) const {
    string outputString;
    string word;
    string line;
    
    // Adds step number
    line = to_string(stepNumber) + ")\t";
    
    // Iterates cursor one char at a time
    for (int cursor = 0; cursor < stepText.length(); cursor++)
        {
            // If char after cursor is NOT a 'space', add char to word
            if (!isspace(stepText[cursor]))
            {
                word += stepText[cursor];
            }
            // If char after cursor IS a 'space'
            else
            {
                // If current line plus most recent word is greater than the max line length, move to the next line
                if ( (line.length() + word.length()) > MAX_LINE_LENGTH)
                {
                    outputString = outputString + line + "\n";
                    line = "\t";
                }
                // Add the word and move on
                line = line + word + " ";
                word.clear();
            }
        }
        // Add final word to line
        line = line + word;
        word.clear();
        // Add final line to output
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
    
    // Iterates through ingredientsList
    output << "Ingredients:\n";
    for (auto const& ingredient: ingredientsList) {
        output << "\t" << ingredient.second << "\n";
    }
    output << "\n";
    
    // Iterates through toolsList
    output << "Tools:\n";
    for (auto const& tool: toolsList) {
        output << "\t" << tool << "\n";
    }
    output << "\n";
    
    // Iterates through steps
    // first, step number is created and is iterated as we move through the steps
    output << "Instructions:\n";
    int stepNumber = 1;
    for (auto const& step: instructions) {
        output << formatStep(stepNumber, step) << "\n";
        stepNumber++;
    }
}


// Child classes for Dish
// each overrides the getType() function and returns its corresponding type
AppetizerDish::~AppetizerDish() {};

DishType AppetizerDish::getType() {
    return Appetizer;
}


EntreeDish::~EntreeDish() {};

DishType EntreeDish::getType() {
    return Entree;
}


DessertDish::~DessertDish() {};

DishType DessertDish::getType() {
    return Dessert;
}

}


