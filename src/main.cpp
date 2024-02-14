#include "RestaurantInterface.hpp"
#include "Database.hpp"
#include "DetailedOutput.hpp"
#include <iostream>

using namespace dishReviewService;

int main() {
    RestaurantInterface myInterface;
    myInterface.run();
    
//    Database<Ingredient>* ingredientDatabase = Database<Ingredient>::getInstance();
//    shared_ptr<Ingredient> lemonPtr = make_shared<Ingredient>("Lemon");
//    shared_ptr<Ingredient> pepperPtr = make_shared<Ingredient>("Pepper");
//    shared_ptr<Ingredient> chickenPtr = make_shared<Ingredient>("Chicken");
//
//    ingredientDatabase->add(lemonPtr, "lemon");
//    ingredientDatabase->add(pepperPtr, "pepper");
//    ingredientDatabase->add(chickenPtr, "chicken");
//
//    Database<Dish>* dishDatabase = Database<Dish>::getInstance();
//    shared_ptr<Dish> lemonPepperChickenPtr = make_shared<EntreeDish>("Lemon Pepper Chicken");
//
//    dishDatabase->add(lemonPepperChickenPtr, "lemon_pepper_chicken");
//
//    lemonPepperChickenPtr->addIngredient(lemonPtr, "2 Lemons", "lemon");
//    lemonPepperChickenPtr->addIngredient(chickenPtr, "700g Chicken Breast", "pepper");
//    lemonPepperChickenPtr->addIngredient(pepperPtr, "Pepper to taste", "chicken");
//    lemonPepperChickenPtr->addTool("Cast Iron Skillet");
//    lemonPepperChickenPtr->addTool("Bowl");
//    lemonPepperChickenPtr->addStep("Place chicken breast in bowl and season with lemon and pepper.");
//    lemonPepperChickenPtr->addStep("Sear chicken on cast iron skillet on medium heat.");
//    lemonPepperChickenPtr->addStep("Garnish and serve.");
//
//
//
//    cout << *ingredientDatabase << "\n\n";
//    cout << *dishDatabase << "\n\n";
//    cout << detailed(*lemonPepperChickenPtr);
    
    return 0;
}
