#include "Ingredient.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::ostream;

namespace dishReviewService {

// Constructor and Deconstructor
Ingredient::Ingredient(const std::string& newDisplayName) :
    displayName(newDisplayName),
    isAllergen(false) {}

Ingredient::~Ingredient() {}

// Toggles whether or not the ingredient can be an allergen
void Ingredient::toggleAllergen() {
    isAllergen = !isAllergen;
}

// Simple accessor function
string Ingredient::getDisplayName() const {
    return displayName;
}

bool Ingredient::getAllergenStatus() const {
    return isAllergen;
}

// << Overload in order to print
// " (Known Allergen)" is added after the name if ingredient is allergen
ostream& operator<<(ostream& output, const Ingredient& outputIngredient) {
    output << outputIngredient.displayName;
    if (outputIngredient.isAllergen) {
        output << " (Known Allergen)";
    }
    
    return output;
}

} /* Ingredient_cpp */
