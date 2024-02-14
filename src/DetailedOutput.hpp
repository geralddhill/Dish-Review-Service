/*
 DetailedOutput:
    - Allows you to define a default << for each class to print with a database,
      and a detailed << to print the full details of the class.
 
 How to Use:
    - In the class, created the method:
        void printDetailed(ostream& output); // Output can be anything it's just an argument name
    - In that method, use output and << to print the detailed version of your class.
    - To call the detailed version use (cout as an example):
        cout << detailed(className);
*/
#ifndef DetailedOutput_hpp
#define DetailedOutput_hpp

#include <iostream>

namespace dishReviewService {

template<typename Type>
class detailed {
private:
    const Type& baseObject;
    
public:
    // Constructs object wrapper and allows new operator<< overload
    // Constructor allows the object to exist only once.
    detailed(const Type& newObject);
    ~detailed();
    
    template<typename T>
    friend std::ostream& operator<<(std::ostream& output, const detailed<T>& detailedObject);
};



template<typename Type>
detailed<Type>::detailed(const Type& newObject) :
baseObject(newObject) {}

template<typename Type>
detailed<Type>::~detailed() {}



template<typename Type>
std::ostream& operator<<(std::ostream& output, const detailed<Type>& detailedObject) {
    // Runs the printDetailed() function of the object when running detailed()
    detailedObject.baseObject.printDetailed(output);
    return output;
}

}
#endif
