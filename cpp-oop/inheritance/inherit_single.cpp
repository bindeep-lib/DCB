/**
 * inherit_single.cpp
 * 覆盖: 单继承
 *
 * class Animal { speak() → "generic" }
 * class Dog : Animal { speak() → "woof" }
 *
 * Animal* a = new Dog();
 * a->speak() → "woof" (返回 1 因为 Dog)
 * return 1
 * 退出码: 1
 */
#include <string>

class Animal {
public:
    virtual ~Animal() {}
    virtual int speak() { return 0; }  // 0 = generic
};

class Dog : public Animal {
public:
    int speak() override { return 1; }  // 1 = woof
};

int main() {
    Animal* a = new Dog();
    int result = a->speak();
    delete a;
    return result;
}
