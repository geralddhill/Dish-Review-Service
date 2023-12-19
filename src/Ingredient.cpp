#include "Ingredient.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::ostream;

namespace dishReviewService {

Ingredient::Ingredient(const std::string& newDisplayName) :
    displayName(newDisplayName),
    isAllergen(false) {}

Ingredient::~Ingredient() {}



void Ingredient::toggleAllergen() {
    isAllergen = !isAllergen;
}



string Ingredient::getDisplayName() const {
    return displayName;
}

bool Ingredient::getAllergenStatus() const {
    return isAllergen;
}



ostream& operator<<(ostream& output, const Ingredient& outputIngredient) {
    output << outputIngredient.displayName;
    if (outputIngredient.isAllergen) {
        output << " (Known Allergen)";
    }
    
    return output;
}

}
