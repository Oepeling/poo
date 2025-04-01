#include <iostream>

using namespace std;

class Base {
private:
    int privateX = 3;

protected:
    int protectedX = 4;

public:
    int publicX = 5;

    int getX() {
        return privateX;
    }
};

class PrivateDerived : private Base {
public:
    int getX() {
//        return privateX;
        return protectedX;
    }
};

class ProtectedDerived : protected Base {
public:
    int getX() {
//        return privateX;
        return protectedX;
    }
};

class PublicDerived : public Base {
public:
    int getX() {
//        return privateX;
        return protectedX;
    }
};

class SecondDerived : PrivateDerived {
public:
    int getX() {
        return this->getX();
    }
};

int main() {
    Base b;
    cout << b.publicX << "\n";

    PrivateDerived priD;
    cout << priD.getX() << "\n";

    ProtectedDerived proD;
    cout << proD.getX() << "\n";

    PublicDerived pubD;
    cout << pubD.publicX << "\n";
    return 0;
}

// ENUM!!!
