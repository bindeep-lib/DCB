/**
 * template_class.cpp
 * 覆盖: 类模板 (STL-style)
 *
 * template<T> Box { T value; get(); set(); }
 * Box<int> bi(10); bi.set(20); → 20
 * Box<int> bi2(5); → 5
 * sum = 20 + 5 = 25
 * 退出码: 25
 */
template<typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
    void set(T v) { value = v; }
};

int main() {
    Box<int> bi(10);
    bi.set(20);
    Box<int> bi2(5);
    return bi.get() + bi2.get();  // 20 + 5 = 25
}
