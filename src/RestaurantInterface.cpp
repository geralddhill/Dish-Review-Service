#include "RestaurantInterface.hpp"
#include "DetailedOutput.hpp"
#include <fstream>
#include <cctype>
#include <sstream>

using namespace ssd;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::to_string;
using std::make_shared;
using std::replace;
using std::transform;
using std::ios;
using std::shared_ptr;
using std::vector;
using std::map;
using std::ostringstream;
using std::left;
using std::setw;

namespace dishReviewService {

RestaurantInterface::RestaurantInterface() {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    Database<Dish> *dishDatabase = Database<Dish>::getInstance();
    Database<Ingredient> *ingredientDatabase = Database<Ingredient>::getInstance();
    ifstream restaurantInFile;
    ifstream dishInFile;
    ifstream ingredientInFile;
    shared_ptr<Restaurant> restaurantInput;
    string restaurantInputId;
    string restaurantInputDisplayName;
    Address restaurantInputAddress;
    shared_ptr<Dish> dishInput;
    string dishInputType;
    string dishInputId;
    string dishInputDisplayName;
    string dishInputIngredientId;
    string dishInputIngredientName;
    string dishInputIngredientText;
    string dishInputTool;
    string dishInputStep;
    string ingredientInputId;
    string ingredientInputName;
    char ingredientAllergenChar;
    
    restaurantInFile.open(RESTAURANTS_FILE_LOCATION, ios::in);
    
    // Checks if file was opened successfully
    if (restaurantInFile.fail())
    {
        cout << "Error with opening restaurant file.\n";
        exit(1);
    }
    
    ingredientInFile.open(INGREDIENTS_FILE_LOCATION, ios::in);
    
    // Checks if file was opened successfully
    if (ingredientInFile.fail())
    {
        cout << "Error with opening ingredient file.\n";
        exit(1);
    }
    
    while(ingredientInFile.peek() != EOF) {
        // Reads file
        ingredientInFile >> ingredientInputId;
        ingredientInFile.ignore();
        getline(ingredientInFile, ingredientInputName);
        ingredientInFile.get(ingredientAllergenChar);
        ingredientInFile.ignore();
        
        // Adds to database
        shared_ptr<Ingredient> newIngredient = make_shared<Ingredient>(ingredientInputName);
        if (ingredientAllergenChar == 'Y') {
            newIngredient->toggleAllergen();
        }
        ingredientDatabase->add(newIngredient, ingredientInputId);
    }
    
    // Puts every restaurant from file in database
    while(restaurantInFile.peek() != EOF) {
        // Reads file
        restaurantInFile >> restaurantInputId;
        restaurantInFile.ignore();
        getline(restaurantInFile, restaurantInputDisplayName);
        getline(restaurantInFile, restaurantInputAddress.streetAddress);
        getline(restaurantInFile, restaurantInputAddress.city);
        restaurantInFile >> restaurantInputAddress.stateAbbreviated;
        restaurantInFile >> restaurantInputAddress.zipcode;
        restaurantInFile.ignore();
        // Adds to database
        restaurantInput = make_shared<Restaurant>(restaurantInputDisplayName, restaurantInputAddress);
        
        // Reads every dish from a file respective to the restaurant and puts in database
        dishInFile.open(FILE_PREFIX + restaurantInputId + ".txt");
        
        // Checks if file was opened successfully
        if (dishInFile.fail())
        {
            cout << "Error with opening dish file.\n";
            exit(1);
        }

        // Imports dishes for restaurant
        while(dishInFile.peek() != EOF) {
            dishInFile >> dishInputType;
            dishInFile >> dishInputId;
            dishInFile.ignore();
            getline(dishInFile, dishInputDisplayName);
            
            // Creates new dish object for database
            if (dishInputType == "APPETIZER") {
                dishInput = make_shared<AppetizerDish>(dishInputDisplayName);
            }
            else if (dishInputType == "ENTREE") {
                dishInput = make_shared<EntreeDish>(dishInputDisplayName);
            }
            else if (dishInputType == "DESSERT") {
                dishInput = make_shared<DessertDish>(dishInputDisplayName);
            }
            else {
                cout << "Error in initializing dish database.\n";
                exit(1);
            }
            
            // Gets extra line
            dishInFile >> dishInputIngredientId;
            // Reads all ingredients
            while (dishInputIngredientId != "ING_END") {
                dishInFile >> dishInputIngredientId;
                dishInFile.ignore();
                
                if (dishInputIngredientId == "ING_END") {
                    continue;
                }
                
                getline(dishInFile, dishInputIngredientName);
                getline(dishInFile, dishInputIngredientText);
                
                dishInput->addIngredient(ingredientDatabase->getEntry(dishInputIngredientId), dishInputIngredientText, dishInputIngredientId);
            }
            
            dishInFile >> dishInputTool;
            dishInFile.ignore();
            // Reads all tools
            while (dishInputTool != "TOOL_END") {
                getline(dishInFile, dishInputTool);
                
                if (dishInputTool == "TOOL_END") {
                    continue;
                }
                
                dishInput->addTool(dishInputTool);
            }
            
            dishInFile >> dishInputStep;
            dishInFile.ignore();
            // Reads all instructions
            while (dishInputStep != "INS_END") {
                getline(dishInFile, dishInputStep);
                
                if (dishInputStep == "INS_END") {
                    continue;
                }
                
                dishInput->addStep(dishInputStep);
            }
            
            // Adds to database
            dishDatabase->add(dishInput, dishInputId);
            // Adds to restaurant
            restaurantInput->addDish(dishInput, dishInputId);
        }

        dishInFile.close();
        
        // Adds to database
        restaurantDatabase->add(restaurantInput, restaurantInputId);
    }
    
    restaurantInFile.close();
}

RestaurantInterface::~RestaurantInterface() {}



void RestaurantInterface::run() const {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    int userInput;
    MainMenuOption menuInput = View_Restaurant;
    bool menuInputValid;
    
    // If restaurant database is still empty, add a restaurant
    if (restaurantDatabase->getSize() == 0) {
        addRestaurant();
        cout << "\n\n";
    }
    
    // Runs main menu
    while (menuInput != Exit) {
        menuInputValid = false;
        
        cout << "Main Menu:\n";
        cout << "1 - View a Restaurant\n";
        cout << "2 - View a Database\n";
        cout << "0 - Exit\n\n";
        
        // Checks validity
        while (!menuInputValid) {
            cout << "Enter a choice (0-2): ";
            cin >> userInput;
            cin.ignore();
            
            if (userInput < 0 || userInput > 2) {
                cout << "Please enter a valid integer.\n";
                continue;
            }
            
            menuInputValid = true;
            menuInput = MainMenuOption(userInput);
            cout << "\n\n\n";
        }
        
        switch (menuInput) {
            case View_Restaurant:
                viewRestaurant();
                break;
            case View_Database:
                viewDatabase();
                break;
            case Exit:
                break;
        }
    }
}



void RestaurantInterface::viewRestaurant() const {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    string userInput;
    bool inputValid;
    
    // Runs restaurant menu
    while (userInput != "EXIT") {
        inputValid = false;
        
        cout << *restaurantDatabase << "\n";
        
        while (!inputValid) {
            cout << "Type \"EXIT\" to go back | Type \"ADD\" to add a restaurant\n";
            cout << "Enter the ID of the restraunt you would like to view (case sensitive): ";
            cin >> userInput;
            cin.ignore();
            
            if (!restaurantDatabase->existsInDatabase(userInput) && userInput != "EXIT" && userInput != "ADD") {
                cout << "Please pick an existing ID.\n";
                continue;
            }
            
            inputValid = true;
            cout << "\n\n\n";
        }
        
        if (userInput == "ADD") {
            cout << "\n\n\n";
            addRestaurant();
        }
        else if (userInput == "EXIT") {
            continue;
        }
        else {
            viewRestaurantMenu(userInput, restaurantDatabase->getEntry(userInput));
        }
    }
}

void RestaurantInterface::viewDatabase() const {
    int userInput;
    DatabaseMenuOption menuInput = Ingredients;
    bool menuInputValid;
    
    // Runs database menu
    while (menuInput != D_Back) {
        menuInputValid = false;
        
        cout << "Database Menu:\n";
        cout << "1 - Ingredients\n";
        cout << "2 - Dishes\n";
        cout << "3 - Restaurants\n";
        cout << "0 - Go Back\n\n";
        
        // Checks validity
        while (!menuInputValid) {
            cout << "Enter a choice (0-3): ";
            cin >> userInput;
            cin.ignore();
            
            if (userInput < 0 || userInput > 3) {
                cout << "Please enter a valid integer.\n";
                continue;
            }
            
            menuInputValid = true;
            menuInput = DatabaseMenuOption(userInput);
            cout << "\n\n\n";
        }
        
        // Displays appropriate database
        switch (menuInput) {
            case Ingredients:
            {
                Database<Ingredient> *ingredientDatabase = Database<Ingredient>::getInstance();
                cout << *ingredientDatabase << "\n\n\n";
                break;
            }
            case Dishes:
            {
                Database<Dish> *dishDatabase = Database<Dish>::getInstance();
                cout << *dishDatabase << "\n\n\n";
                break;
            }
            case Restaurants:
            {
                Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
                cout << *restaurantDatabase << "\n\n\n";
                break;
            }
            case D_Back:
                break;
        }
    }
}



void RestaurantInterface::addRestaurant() const {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    ofstream outFile;
    string inputId;
    string inputName;
    Address inputAddress;
    bool nameValid = false;
    
    outFile.open(RESTAURANTS_FILE_LOCATION, ios::out | ios::app);
    
    // Checks if file was opened successfully
    if (outFile.fail())
    {
        cout << "Error with opening restaurant file.\n";
        exit(1);
    }
    
    // Gets name of restaurant and makes sure it doesn't exist
    while (!nameValid) {
        nameValid = true;
        
        cout << "Enter Restaurant Name: ";
        getline(cin, inputName);
        
        inputId = convertToId(inputName);
        if (restaurantDatabase->existsInDatabase(inputId)) {
            nameValid = false;
            cout << "Restaurant name already exists. Please pick a new name.\n";
        }
    }
    
    // Gets address
    inputAddress = createAddress();
    
    // Adds to database
    restaurantDatabase->add(make_shared<Restaurant>(inputName, inputAddress), inputId);
    
    // Adds to file
    outFile << inputId << "\n" << inputName << "\n"<< inputAddress.streetAddress << "\n"
        << inputAddress.city << "\n" << inputAddress.stateAbbreviated << "\n" << inputAddress.zipcode << "\n";
    
    outFile.close();
    
    // Creates a new file to store dish data
    outFile.open(FILE_PREFIX + inputId + ".txt", ios::out | ios::trunc);
    outFile.close();
}

void RestaurantInterface::viewRestaurantMenu(string currentRestaurantId, shared_ptr<Restaurant> currentRestaurant) const {
    int userInput;
    RestaurantMenuOption menuInput = Set_Address;
    bool menuInputValid;
    
    // Runs database menu
    while (menuInput != R_Back) {
        menuInputValid = false;
        
        // Displays restaurant details
        cout << detailed(*currentRestaurant) << "\n";
        
        cout << "Restaurant Menu:\n";
        cout << "1 - Change Address\n";
        cout << "2 - View a Dish\n";
        cout << "3 - Add a Dish\n";
        cout << "4 - Remove a Dish (Not Functioning Currently)\n";
        cout << "0 - Go Back\n\n";
        
        // Checks validity
        while (!menuInputValid) {
            cout << "Enter a choice (0-4): ";
            cin >> userInput;
            cin.ignore();
            
            if (userInput < 0 || userInput > 4) {
                cout << "Please enter a valid integer.\n";
                continue;
            }
            
            menuInputValid = true;
            menuInput = RestaurantMenuOption(userInput);
            cout << "\n\n\n";
        }
        
        switch (menuInput) {
            case Set_Address:
            {
                Address newAddress = createAddress();
                editAddressFile(currentRestaurant->getAddress(), newAddress);
                currentRestaurant->setAddress(newAddress);
                break;
            }
            case View_Dish:
                viewDish(currentRestaurant);
                break;
            case Add_Dish:
                addDish(currentRestaurantId, currentRestaurant);
                break;
            case Remove_Dish:
                removeDish();
                break;
            case R_Back:
                break;
        }
    }
}



void RestaurantInterface::editAddressFile(Address oldAddress, Address newAddress) const {
    ifstream inFile;
    ofstream outFile;
    ostringstream fullTextStream;
    string fullText;
    size_t pos;
    
    string searchKey = oldAddress.streetAddress + "\n" + oldAddress.city + "\n"
    + oldAddress.stateAbbreviated + "\n" + to_string(oldAddress.zipcode) + "\n";
    string replacement = newAddress.streetAddress + "\n" + newAddress.city + "\n"
    + newAddress.stateAbbreviated + "\n" + to_string(newAddress.zipcode) + "\n";
    
    inFile.open(RESTAURANTS_FILE_LOCATION, ios::in);
    
    // Checks to make sure that file successfully opened
    if (inFile.fail())
    {
        cout << "Error with opening restaurant file.\n";
        exit(1);
    }
    
    // Replaces text
    fullTextStream << inFile.rdbuf();
    fullText = fullTextStream.str();
    pos = fullText.find(searchKey);
    fullText.replace(pos, searchKey.length(), replacement);
    
    inFile.close();
    
    // Rewrites to new file
    outFile.open(RESTAURANTS_FILE_LOCATION, ios::out | ios::trunc);
    
    // Checks to make sure that file successfully opened
    if (outFile.fail())
    {
        cout << "Error with opening restaurant file.\n";
        exit(1);
    }
    
    outFile << fullText;
}

void RestaurantInterface::viewDish(std::shared_ptr<Restaurant> restaurant) const {
    map<string, shared_ptr<Dish>> appetizers = restaurant->getAppetizers();
    map<string, shared_ptr<Dish>> entrees = restaurant->getEntrees();
    map<string, shared_ptr<Dish>> desserts = restaurant->getDesserts();
    string userInput;
    
    while (userInput != "EXIT") {
        cout << "Appetizers:\n";
        cout << left << setw(40) << "ID" << "Name\n";
        for (auto const& item: appetizers) {
            cout << left << setw(40) << item.first << *item.second << "\n";
        }
        
        cout << "Entrees:\n";
        cout << left << setw(40) << "ID" << "Name\n";
        for (auto const& item: entrees) {
            cout << left << setw(40) << item.first << *item.second << "\n";
        }
        
        cout << "Desserts:\n";
        cout << left << setw(40) << "ID" << "Name\n";
        for (auto const& item: desserts) {
            cout << left << setw(40) << item.first << *item.second << "\n";
        }
        cout << "\n";
        
    entry:
        cout << "Enter the ID of the dish you would like to view (\"EXIT\" to go back): ";
        cin >> userInput;
        
        if (userInput == "EXIT") {
            continue;
        }
        else if (appetizers.count(userInput) > 0) {
            cout << "\n\n\n" << detailed(*appetizers[userInput]);
        }
        else if (entrees.count(userInput) > 0) {
            cout << "\n\n\n" << detailed(*entrees[userInput]);
        }
        else if (desserts.count(userInput) > 0) {
            cout << "\n\n\n" << detailed(*desserts[userInput]);
        }
        else {
            cout << "Please enter a valid id.\n";
            goto entry;
        }
        cout << "\n\n\n";
    }
}

void RestaurantInterface::addDish(string restaurantId, shared_ptr<Restaurant> restaurant) const {
    Database<Dish> *dishDatabase = Database<Dish>::getInstance();
    Database<Ingredient> *ingredientDatabase = Database<Ingredient>::getInstance();
    shared_ptr<Dish> finalInputDish;
    ofstream outFile;
    ofstream ingredientOutFile;
    string inputId;
    string inputName;
    string inputIngredientName;
    shared_ptr<Ingredient> inputIngredient;
    string inputIngredientText;
    string inputIngredientId;
    char isAllergenInput;
    string inputTool;
    string inputStep;
    bool nameValid = false;
    int typeUserInput;
    DishType typeInput;
    bool typeValid = false;
    
    outFile.open(FILE_PREFIX + restaurantId + ".txt", ios::out | ios::app);
    
    // Checks if file was opened successfully
    if (outFile.fail())
    {
        cout << "Error with opening dish file.\n";
        exit(1);
    }
    
    ingredientOutFile.open(INGREDIENTS_FILE_LOCATION, ios::out | ios::app);
    
    // Checks if file was opened successfully
    if (ingredientOutFile.fail())
    {
        cout << "Error with opening ingredient file.\n";
        exit(1);
    }
    
    cout << "Dish Types: \n";
    cout << "0 - Appetizer\n";
    cout << "1 - Entree\n";
    cout << "2 - Dessert\n\n";
    while (!typeValid) {
        cout << "Enter a choice (0-2): ";
        cin >> typeUserInput;
        cin.ignore();
        
        if (typeUserInput < 0 || typeUserInput > 2) {
            cout << "Please enter a valid integer.\n";
            continue;
        }
        
        typeValid = true;
        typeInput = DishType(typeUserInput);
        cout << "\n\n";
    }
    
    // Gets name of restaurant and makes sure it doesn't exist
    while (!nameValid) {
        nameValid = true;
        
        cout << "Enter Dish Name: ";
        getline(cin, inputName);
        
        inputId = restaurantId + ":" + convertToId(inputName);
        if (dishDatabase->existsInDatabase(inputId)) {
            nameValid = false;
            cout << "Dish name already exists. Please pick a new name.\n";
        }
    }
    

    
    // Makes a dish ptr to add based on the chosen type of dish
    switch (typeInput) {
        case Appetizer:
        {
            finalInputDish = make_shared<AppetizerDish>(inputName);
            outFile << "APPETIZER\n";
            break;
        }
        case Entree:
        {
            finalInputDish = make_shared<EntreeDish>(inputName);
            outFile << "ENTREE\n";
            break;
        }
        case Dessert:
        {
            finalInputDish = make_shared<DessertDish>(inputName);
            outFile << "DESSERT\n";
            break;
        }
    }
    
    // Adds names to file
    outFile << inputId << "\n" << inputName << "\n";
    
    // Lets user input ingredients
    outFile << "ING_START\n";
    while(inputIngredientName != "NEXT") {
        cout << "Enter the name of your ingredient (singular) (\"NEXT\" to move on): ";
        getline(cin, inputIngredientName);
        inputIngredientId = convertToId(inputIngredientName);
        
        if (inputIngredientName == "NEXT") {
            continue;
        }
        if (!ingredientDatabase->existsInDatabase(inputIngredientId)) {
            // Adds ingredient to database if unique
            inputIngredient = make_shared<Ingredient>(inputIngredientName);
            bool allergenInputValid = false;
            
            while (!allergenInputValid) {
                cout << "Is this ingredient an allergen (Y/N): ";
                cin.get(isAllergenInput);
                cin.ignore();
                
                if (toupper(isAllergenInput) == 'Y') {
                    
                    inputIngredient->toggleAllergen();
                }
                else if (toupper(isAllergenInput) != 'N') {
                    cout << "Please enter a valid character.\n";
                    continue;
                }
                allergenInputValid = true;
            }
            
            // Add ingredient to database
            ingredientDatabase->add(inputIngredient, inputIngredientId);
            // Add to file
            ingredientOutFile << inputIngredientId << "\n" << inputIngredientName << "\n"
                << static_cast<char>(toupper(isAllergenInput)) << "\n";;
        }
        else {
            // Copies if it already exists
            inputIngredient = ingredientDatabase->getEntry(inputIngredientId);
        }
        
        cout << "Enter the text that will display for the ingredient in the recipe: ";
        getline(cin, inputIngredientText);
        
        // Add to dish
        finalInputDish->addIngredient(inputIngredient, inputIngredientText, inputIngredientId);
        
        // Add to file
        outFile << inputIngredientId << "\n" << inputIngredientName << "\n" << inputIngredientText << "\n";
    }
    outFile << "ING_END\n";
    
    // Lets user input tools
    outFile << "TOOL_START\n";
    while (inputTool != "NEXT") {
        cout << "Enter the text that will display for the tool in the recipe (\"NEXT\" to move on): ";
        getline(cin, inputTool);
        
        if (inputTool == "NEXT") {
            continue;
        }
        
        // Add to dish
        finalInputDish->addTool(inputTool);
        
        // Add to file
        outFile << inputTool << "\n";
    }
    outFile << "TOOL_END\n";
    
    // Lets user input instructions
    outFile << "INS_START\n";
    while (inputStep != "NEXT") {
        cout << "Enter a step for your instructions (ENTER when step is finished) (\"NEXT\" to move on): ";
        getline(cin, inputStep);
        
        if (inputStep == "NEXT") {
            continue;
        }
        
        // Add to dish
        finalInputDish->addStep(inputStep);
        
        // Add to file
        outFile << inputStep << "\n";
    }
    outFile << "INS_END\n";
    
    // Add to restaurant
    restaurant->addDish(finalInputDish, inputId);
    
    // Adds to database
    dishDatabase->add(finalInputDish, inputId);
    
    outFile.close();
    
    cout << "\n\n\n";
}

void RestaurantInterface::removeDish() const {
    
}



Address RestaurantInterface::createAddress() const {
    Address outputAddress;
    
    cout << "Enter Street Address: ";
    getline(cin, outputAddress.streetAddress);
    cout << "Enter City: ";
    getline(cin, outputAddress.city);
    cout << "Enter State Abbreviation: ";
    cin >> outputAddress.stateAbbreviated;
    cout << "Enter Zipcode: ";
    cin >> outputAddress.zipcode;
    cin.ignore();
    cout << "\n\n\n";
    
    return outputAddress;
}



string RestaurantInterface::convertToId(const string& input) const {
    string output = input;
    
    // Moves the cursor along each char of the string and edits the characters to fit the naming convention
    for (int cursor = 0; cursor < output.length(); cursor++) {
        if (output[cursor] == ' ') {
            output[cursor] = '_';
        }
        else if (!isalnum(output[cursor])) {
            output.erase(cursor, 1);
        }
        else if (isupper(output[cursor])) {
            output[cursor] = tolower(output[cursor]);
        }
    }
    
    return output;
}



}
