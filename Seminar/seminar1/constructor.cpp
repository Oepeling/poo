#include <iostream>

using namespace std;

class Base {
private:
    int privateX = 3;
    int privateY;
    const int privateConstZ = 6;

public:
    Base() {
        privateY = 4;
        cout << "abc";
    }

    Base(int y /* = 0 */) : privateConstZ(8) {
        privateY = y;
        // You can't change the value of a constant, not even in the constructor
        // but you can call it's constructor
//        privateConstZ = 7;
        cout << "def";
    }

    Base(const Base& other) {
        privateX = other.privateX;
        privateY = other.privateY;
    }
};

int main() {
    Base b = Base();
    Base c(5);
    Base d(b);
    return 0;
}
