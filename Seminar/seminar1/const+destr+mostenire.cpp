#include <iostream>

using namespace std;

class Base {
private:
    int privateX = 3;

public:
    int getX() {
        return privateX;
    }

    Base() {
        cout << "Constructor Base\n";
    }

    Base(int x) {
        privateX = x;
        cout << "Other Constructor Base\n";
    }

    ~Base() {
        cout << "Destructor Base\n";
    }
};

class Derived : Base {
public:
    Derived() {
        cout << "Constructor Derived\n";
    }
    Derived(int x) : Base(x) {
        cout << "Other Constructor Derived\n";
    }
    ~Derived() {
        cout << "Destructor Derived\n";
    }
};

class SecondDerived : Derived {
public:
    SecondDerived() {
        cout << "Constructor SecondDerived\n";
    }
//    SecondDerived(int x) : Base(x) {
    SecondDerived(int x) : Derived(x) {
        cout << "Other Constructor SecondDerived\n";
    }
    ~SecondDerived() {
        cout << "Destructor SecondDerived\n";
    }
};

int main() {
    SecondDerived obj;
    SecondDerived otherObj(10);
    return 0;
}
