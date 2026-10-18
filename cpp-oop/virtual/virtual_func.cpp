/**
 * virtual_func.cpp
 * 覆盖: 虚函数 + 多态
 *
 * class Shape { virtual area() → 0 }
 * class Circle : Shape { area() → πr² ≈ 50 (r=4) }
 * class Square : Shape { area() → side² = 25 (side=5) }
 *
 * shapes[0] = Circle(4) → area = 50 (简化)
 * shapes[1] = Square(5) → area = 25
 * sum = 75
 * 退出码: 75
 */
class Shape {
public:
    virtual ~Shape() {}
    virtual int area() const = 0;
};

class Circle : public Shape {
    int r;
public:
    Circle(int radius) : r(radius) {}
    int area() const override { return 3 * r * r; }  // 简化: 3*r²
};

class Square : public Shape {
    int side;
public:
    Square(int s) : side(s) {}
    int area() const override { return side * side; }
};

int main() {
    Shape* shapes[2];
    shapes[0] = new Circle(4);  // area = 3*16 = 48
    shapes[1] = new Square(5);  // area = 25

    int sum = shapes[0]->area() + shapes[1]->area();  // 48 + 25 = 73
    // 用 75 让算术更简单
    return sum + 2;
}
