/**
 * class_basic.cpp
 * 覆盖: 简单类 + 构造/析构
 *
 * Counter c(10);
 * c.increment() → 11
 * c.increment() → 12
 * c.increment() → 13
 * return c.get() = 13
 * 退出码: 13
 */
class Counter {
private:
    int value;
public:
    Counter(int v) : value(v) {}
    ~Counter() {}

    void increment() { value++; }
    int get() const { return value; }
};

int main() {
    Counter c(10);
    c.increment();
    c.increment();
    c.increment();
    return c.get();
}
