/**
 * inherit_multi.cpp
 * 覆盖: 多继承
 *
 * class A { foo() → 10 }
 * class B { bar() → 20 }
 * class C : A, B { baz() → 30 }
 *
 * c.foo() + c.bar() + c.baz() = 10 + 20 + 30 = 60
 * 退出码: 60
 */
class A {
public:
    int foo() { return 10; }
};

class B {
public:
    int bar() { return 20; }
};

class C : public A, public B {
public:
    int baz() { return 30; }
};

int main() {
    C c;
    return c.foo() + c.bar() + c.baz();
}
