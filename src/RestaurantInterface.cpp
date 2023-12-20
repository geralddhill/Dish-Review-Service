#include "RestaurantInterface.hpp"
#include "fstream"
#include "algorithm"

using namespace ssd;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::make_shared;
using std::replace;
using std::transform;
using std::ios;

namespace dishReviewService {

RestaurantInterface::RestaurantInterface() {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    ifstream inFile;
    string inputId;
    string inputDisplayName;
    Address inputAddress;
    
    inFile.open(RESTAURANTS_FILE_LOCATION, ios::in);
    
    // Checks if file was opened successfully
    if (inFile.fail())
    {
        cout << "Error with opening restaurant file.\n";
        exit(1);
    }
    
    
    // Puts every restaurant from file in database
    while(inFile.peek() != EOF) {
        inFile >> inputId;
        inFile.ignore();
        getline(inFile, inputDisplayName);
        getline(inFile, inputAddress.streetAddress);
        getline(inFile, inputAddress.city);
        inFile >> inputAddress.stateAbbreviated;
        inFile >> inputAddress.zipcode;
        inFile.ignore();
        
        restaurantDatabase->add(make_shared<Restaurant>(inputDisplayName, inputAddress), inputId);
    }
    
    inFile.close();
}

RestaurantInterface::~RestaurantInterface() {}



void RestaurantInterface::runRestaurantView() const {
    Database<Restaurant> *restaurantDatabase = Database<Restaurant>::getInstance();
    
    // If restaurant database is still empty, add a restaurant
    if (restaurantDatabase->getSize() == 0) {
        addRestaurant();
    }
    
    cout << *restaurantDatabase;
}

string RestaurantInterface::convertToId(const string& input) const {
    string output = input;
    transform(output.begin(), output.end(), output.begin(), ::tolower);
    replace(output.begin(), output.end(), ' ', '_');
    return output;
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
    cout << "Enter Street Address: ";
    getline(cin, inputAddress.streetAddress);
    cout << "Enter City: ";
    getline(cin, inputAddress.city);
    cout << "Enter State Abbreviation: ";
    cin >> inputAddress.stateAbbreviated;
    cout << "Enter Zipcode: ";
    cin >> inputAddress.zipcode;
    cin.ignore();
    
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

}
