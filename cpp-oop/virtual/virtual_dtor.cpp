/**
 * virtual_dtor.cpp
 * 覆盖: 虚析构函数 (delete via base ptr)
 *
 * class Base { virtual ~Base() { cleanup(); } }
 * class Derived : Base { ~Derived() { cleanup2(); } }
 *
 * Base* p = new Derived();
 * delete p; → 触发 Derived::~Derived() → Base::~Base()
 * count = 2 (两次 cleanup 计数)
 * 退出码: 2
 */
static int cleanup_count = 0;

class Base {
public:
    virtual ~Base() { cleanup_count++; }
};

class Derived : public Base {
public:
    ~Derived() { cleanup_count++; }
};

int main() {
    cleanup_count = 0;
    Base* p = new Derived();
    delete p;
    return cleanup_count;  // 2 (Derived dtor + Base dtor)
}
