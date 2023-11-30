#include "Ingredient.hpp"

using std::string;
using std::shared_ptr;
using std::vector;
using std::ostream;

namespace dishReviewService {

Ingredient::Ingredient(string newDisplayName) :
    displayName(newDisplayName),
    isAllergen(false) {}

Ingredient::~Ingredient() {}



void Ingredient::toggleAllergen() {
    isAllergen = !isAllergen;
}

void Ingredient::addDish(shared_ptr<Dish> newDish) {
    dishesUsedIn.push_back(newDish);
}



string Ingredient::getDisplayName() const {
    return displayName;
}

bool Ingredient::getAllergenStatus() const {
    return isAllergen;
}

vector<shared_ptr<Dish>> Ingredient::getDishesUsedIn() const {
    return dishesUsedIn;
}



ostream& operator<<(ostream& output, const Ingredient& outputIngredient) {
    output << outputIngredient.displayName;
    if (outputIngredient.isAllergen) {
        output << " (Known Allergen)";
    }
    
    return output;
}

}
