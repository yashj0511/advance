
23 APR

//1
#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

int main() {
    try {
        // Allocate a huge amount of memory to raise bad_alloc exception
        size_t size = 1000000000000; // 1 terabyte (unrealistic size)
        int* huge_array = new int[size];
        delete[] huge_array;
    } catch(const bad_alloc& e) {
        cerr << "Caught bad_alloc: " << e.what() << endl;
    }

    return 0;
}

//2
#include <iostream>
#include <stdexcept>

using namespace std;

void risky_function(int value) {
    if (value < 0) {
        throw invalid_argument("Negative value not allowed");
    }
    // Some risky operations
}

int main() {
    try {
        risky_function(-5);
    } catch(const exception& e) {
        cerr << "Caught exception: " << e.what() << endl;
    }

    return 0;
}

//3
#include <iostream>
#include <stdexcept>

using namespace std;

class ClassB {
public:
    ClassB() {
        // Simulate an error condition
        throw runtime_error("Error in ClassB constructor");
    }
};

class ClassA {
public:
    ClassA() {
        try {
            // Try to instantiate ClassB
            ClassB b;
        } catch(const exception& e) {
            cerr << "Caught exception in ClassA constructor: " << e.what() << endl;
            // Handle the exception or rethrow it
        }
    }
};

int main() {
    try {
        // Instantiate ClassA
        ClassA a;
    } catch(const exception& e) {
        cerr << "Caught exception in main: " << e.what() << endl;
        // Handle the exception
    }

    return 0;
}


25 APR

#include <iostream>
#include <map>

using namespace std;

class Numbers {
public:
    Numbers() {
        cout << "Default constructor invoked" << endl;
    }

    Numbers(int num) {
        cout << "Parameterized constructor invoked with " << num << endl;
    }

    Numbers(const Numbers& other) {
        cout << "Copy constructor invoked" << endl;
    }

    ~Numbers() {
        cout << "Destructor invoked" << endl;
    }
};

class Employee {
private:
    string name;

public:
    Employee() : name("NoName") {
        cout << "Default constructor invoked" << endl;
    }

    Employee(const string& newName) : name(newName) {
        cout << "Parameterized constructor invoked with " << newName << endl;
    }

    Employee(const Employee& other) : name(other.name) {
        cout << "Copy constructor invoked" << endl;
    }

    ~Employee() {
        cout << "Destructor invoked for Employee " << name << endl;
    }

    void setName(const string& newName) {
        name = newName;
    }

    string getName() const {
        return name;
    }
};

void Print(Employee emp) {
    cout << "Printing employee by value: " << emp.getName() << endl;
}

void PrintByRef(const Employee& emp) {
    cout << "Printing employee by reference: " << emp.getName() << endl;
}

class Car {
private:
    int* yearOfEstablishment;
    map<string, int> modelNameToQuantity;

public:
    Car() {
        yearOfEstablishment = new int(2020); // Initialize with some default value
        cout << "Default constructor invoked" << endl;
    }

    Car(const Car& other) {
        yearOfEstablishment = new int(*other.yearOfEstablishment);
        cout << "Copy constructor invoked" << endl;
    }

    ~Car() {
        delete yearOfEstablishment;
        cout << "Destructor invoked" << endl;
    }

    // Method to demonstrate deep copy
    void setYearOfEstablishment(int year) {
        *yearOfEstablishment = year;
    }

    int getYearOfEstablishment() const {
        return *yearOfEstablishment;
    }
};

int main() {
    // Testing Numbers class
    Numbers num1; // Default constructor
    Numbers num2(5); // Parameterized constructor
    Numbers num3(num2); // Copy constructor

    cout << endl;

    // Testing Employee class
    Employee emp1; // Default constructor
    Employee emp2("John Doe"); // Parameterized constructor
    Employee emp3 = emp2; // Copy constructor

    Print(emp3); // Print by value
    PrintByRef(emp3); // Print by reference

    cout << endl;

    // Testing Car class
    Car car1; // Default constructor
    Car car2(car1); // Copy constructor
    cout << "Year of establishment for car1: " << car1.getYearOfEstablishment() << endl;
    cout << "Year of establishment for car2: " << car2.getYearOfEstablishment() << endl;

    car1.setYearOfEstablishment(2010); // Change year for car1
    cout << "Year of establishment for car1 after modification: " << car1.getYearOfEstablishment() << endl;
    cout << "Year of establishment for car2: " << car2.getYearOfEstablishment() << endl;

    return 0;
}


//29 APR

#include <iostream>
#include <memory>

using namespace std;

class Integer {
private:
    int* value;

public:
    // Default constructor
    Integer() : value(new int(0)) {
        cout << "Default constructor invoked" << endl;
    }

    // Parameterized constructor
    Integer(int val) : value(new int(val)) {
        cout << "Parameterized constructor invoked with " << val << endl;
    }

    // Copy constructor
    Integer(const Integer& other) : value(new int(*other.value)) {
        cout << "Copy constructor invoked" << endl;
    }

    // Move constructor
    Integer(Integer&& other) noexcept : value(other.value) {
        other.value = nullptr; // Reset the source object
        cout << "Move constructor invoked" << endl;
    }

    // Destructor
    ~Integer() {
        delete value;
        cout << "Destructor invoked" << endl;
    }

    // Assignment operator
    Integer& operator=(const Integer& other) {
        if (this != &other) {
            delete value; // Release the old resource
            value = new int(*other.value);
        }
        cout << "Assignment operator invoked" << endl;
        return *this;
    }

    // Move assignment operator
    Integer& operator=(Integer&& other) noexcept {
        if (this != &other) {
            delete value; // Release the old resource
            value = other.value;
            other.value = nullptr; // Reset the source object
        }
        cout << "Move assignment operator invoked" << endl;
        return *this;
    }

    // Getter function
    int getValue() const {
        return *value;
    }
};

void useSmartPointer(unique_ptr<Integer>& ptr) {
    cout << "Value of Integer: " << ptr->getValue() << endl;

    // Reset function
    ptr.reset(new Integer(10)); // Resets the smart pointer to point to a new Integer object

    if (ptr) {
        cout << "After reset, value of Integer: " << ptr->getValue() << endl;
    } else {
        cout << "Pointer is empty after reset" << endl;
    }

    // Release function
    Integer* released = ptr.release(); // Releases ownership of the managed object
    if (!ptr) {
        cout << "Pointer is empty after release" << endl;
    }

    // Get function
    unique_ptr<Integer> newPtr(released); // Takes ownership of the released pointer
    cout << "Value of Integer from released pointer: " << newPtr->getValue() << endl;
}

int main() {
    // Using unique_ptr with Integer
    unique_ptr<Integer> ptr(new Integer(5));
    useSmartPointer(ptr);

    return 0;
}


//2 MAY
//first
#include <iostream>
#include <memory>

using namespace std;

class MyClass {
public:
    void someFunction() {
        cout << "someFunction() called" << endl;
    }

    void anotherFunction() {
        cout << "anotherFunction() called" << endl;
    }
};

int main() {
    unique_ptr<MyClass> ptr(new MyClass());

    if (ptr) {
        cout << "Smart pointer is not null" << endl;
        ptr->someFunction(); // Accessing member function using smart pointer
        ptr->anotherFunction(); // Accessing another member function using smart pointer
    } else {
        cout << "Smart pointer is null" << endl;
    }

    return 0;
}

//second

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string inputFileName, outputFileName;

    cout << "Enter the name of the input file: ";
    cin >> inputFileName;

    cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            outputFile << line << endl;
        }
        cout << "File content copied to " << outputFileName << endl;
    } else {
        cout << "Unable to open input file: " << inputFileName << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}



//3 rd
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readAndPrintFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file: " << fileName << endl;
    }
}

int main() {
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;

    readAndPrintFile(fileName);

    return 0;
}





