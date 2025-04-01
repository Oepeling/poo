#include <iostream>

using namespace std;

class PrivateConstructor {
private:
    int privateX;

    // A private constructor cannot be called => this class can't be initialized
    // So why do we need it?
    PrivateConstructor() {}

public:
};

class Singleton {
    static Singleton instance;
    int privateX;

    Singleton() {
        privateX = 3;
        cout << "Constructor Singleton\n";
    }

public:
    static Singleton& getInstance() {
        return instance;
    }

    int getX() {
        return privateX;
    }

    static int getInstanceX() {
        // You can't call a non-static method in from a static context
//        return getX();
        // or a non-static field
//        return privateX;
        return instance.getX();
        return instance.privateX;
    }
};

int main() {
    // You can't initialize a class with a private constructor
//    PrivateConstructor pc;

    Singleton sg = Singleton::getInstance();
    cout << sg.getX() << " " << sg.getInstanceX() << " " << Singleton::getInstanceX() << "\n";
    Singleton* ptr = &(Singleton::getInstance());
    cout << ptr->getX() << "\n";
    return 0;
}
