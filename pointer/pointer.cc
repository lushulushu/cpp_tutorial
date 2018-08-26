#include <iostream>
#include <string>

class Person {
public:
    // default constructor
    Person() : name_("unset"), age_(0) {}
    std::string name_;
    int age_;
};

void SetPersonByPointer(Person* p) {
    p->name_ = "A";
    p->age_ = 1;
}

void SetPersonByReference(Person& p) {
    p.name_ = "B";
    p.age_ = 2;
}

// not working
void SetPersonByInstance(Person p) {
    p.name_ = "C";
    p.age_ = 3;
}

int main() {
    Person A, B, C;

    SetPersonByPointer(&A);
    SetPersonByReference(B);
    SetPersonByInstance(C);

    std::cout << "A: " << A.name_ << " " << A.age_ << std::endl;
    std::cout << "B: " << B.name_ << " " << B.age_ << std::endl;
    std::cout << "C: " << C.name_ << " " << C.age_ << std::endl;

    return 0;
}