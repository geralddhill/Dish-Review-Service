/*
 simpleSingletonDatabase: Allows user to store a list of anything in a program
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
    - get(): Takes an entry key and returns a pointer to an entry if the entry key is found
        - This function only searches through the entry keys, so make sure your formatting is consistent
        - If no entry is found with a matching entry key, the function returns NULL
    - existsInDatabase(): Returns true if the supplied entry id exists in the database
        - Used in get()
    - operator<<(): Allows use of << operator
        - Make sure that if you're using a custom datatype, that you're custom datatype also overloads the << operator
 */
#ifndef Database_hpp
#define Database_hpp

#include <map>
#include <mutex>
#include <memory>

namespace simpleSingletonDatabase {
using Identifier = std::string;

template <typename Type>
class Database {
private:
    // For Singleton
    static inline Database<Type> *instance;
    static inline std::mutex mutex;
    
    // Properties
    Identifier typeId;
    std::map<Identifier, std::shared_ptr<Type>> data;
    
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
    std::shared_ptr<Type> get(const Identifier& entryKey);
    bool existsInDatabase(const Identifier& entryKey);
    
    template <typename T>
    friend std::ostream& operator<<(std::ostream& output, const Database<T>& outputDatabase);
};

template <typename Type>
Database<Type>::Database() : typeId(typeid(Type).name()) {}

template <typename Type>
Database<Type>::~Database() {
    delete instance;
}


template <typename Type>
Database<Type>* Database<Type>::getInstance() {
    // Idk what this line does I copied it from a tutorial
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Database<Type>;
    }
    return instance;
}


template <typename Type>
void Database<Type>::add(const std::shared_ptr<Type>& entry, const Identifier& entryId) {
    data[entryId] = entry;
}

template <typename Type>
void Database<Type>::remove(const Identifier& entryId) {
    data.erase(entryId);
}

template <typename Type>
std::shared_ptr<Type> Database<Type>::get(const Identifier& entryKey) {
    if (existsInDatabase(entryKey)) {
        return data[entryKey];
    }
    return NULL;
}

template <typename Type>
bool Database<Type>::existsInDatabase(const Identifier& entryKey) {
    return data.count(entryKey) > 0;
}

template <typename Type>
std::ostream& operator<<(std::ostream& output, const Database<Type>& outputDatabase) {
    for (auto const& iterator: outputDatabase.data) {
        output << *iterator.second << "\n";
    }
    return output;
}

}
#endif /* Database_hpp */
