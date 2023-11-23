/*
 simpleDatabase: Allows user to store a list of anything in a program
    - Uses singleton pattern, so only one can exist of each type
 
 To Construct/Assign:
    - Declare a Database pointer of the type you want:
    - Call the getInstance() method.
        - This first call will construct the database of that type
    - Ex:
        Database<int>* intDatabase = Database<int>::getInstance();
  
 Additional Methods:
    - add(): Takes a shared_ptr to an entry and an identifier for that entry and adds it to the database
    - remove(): Takes an identifier for an entry and removes it from the database (shared_ptr handles deletion)
    - search(): Takes a search key and returns a pointer to an entry if the search key is found
        - This function only searches the entry keys, so make sure your formatting is consistent
        - If no entry is found with a matching entry key, the function returns NULL
 */
#ifndef Database_hpp
#define Database_hpp

#include <map>
#include <mutex>
#include <memory>

namespace simpleDatabase {
using Identifier = std::string;

template <typename Type> class Database {
private:
    // For Singleton
    static inline Database<Type> *instance;
    static inline std::mutex mutex;
    
    // Properties
    std::string typeId;
    std::map<std::string, std::shared_ptr<Type>> data;
    
    // Constructor/Destructor
    Database();
    ~Database();
    
public:
    // For Singleton
    Database<Type>(Database<Type>& other) = delete;
    void operator=(const Database<Type>& other) = delete;
    
    // The single instance of the database of this type
    static Database<Type>* getInstance();
    
    // Methods
    void add(const std::shared_ptr<Type>& entry, const Identifier& entryId);
    void remove(const Identifier& entryId);
    std::shared_ptr<Type> search(const Identifier& searchKey);
};

template <typename Type> Database<Type>::Database() {
    typeId = typeid(Type).name();
}

template <typename Type> Database<Type>::~Database() {}


template <typename Type> Database<Type>* Database<Type>::getInstance() {
    // Idk what this line does I copied it from a tutorial
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Database<Type>;
    }
    return instance;
}


template <typename Type> void Database<Type>::add(const std::shared_ptr<Type>& entry, const Identifier& entryId) {
    data[entryId] = entry;
}

template <typename Type> void Database<Type>::remove(const Identifier& entryId) {
    data.erase(entryId);
}

template <typename Type> std::shared_ptr<Type> Database<Type>::search(const Identifier& searchKey) {
    if (data.count(searchKey) != 0) {
        return data[searchKey];
    }
    return NULL;
}

}
#endif /* Database_hpp */
