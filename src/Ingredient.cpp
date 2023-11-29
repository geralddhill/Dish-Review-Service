#include "Ingredient.hpp"

namespace dishReviewService {

using std::string;
using std::shared_ptr;
using std::vector;

Ingredient::Ingredient(string newDisplayName) {
    displayName = newDisplayName;
    isAllergen = false;
}

Ingredient::~Ingredient() {}

void Ingredient::toggleAllergen() {
    isAllergen = !isAllergen;
}

void Ingredient::addDish(shared_ptr<Dish> newDish) {
    dishesUsedIn.push_back(newDish);
}

string Ingredient::getDisplayName() {
    return displayName;
}

bool Ingredient::getAllergenStatus() {
    return isAllergen;
}

vector<shared_ptr<Dish>> Ingredient::getDishesUsedIn() {
    return dishesUsedIn;
}

std::ostream& operator<<(std::ostream& output, const Ingredient& outputIngredient) {
    output << outputIngredient.displayName;
    if (outputIngredient.isAllergen) {
        output << " (Known Allergen)";
    }
    
    return output;
}

}
