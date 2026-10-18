/**
 * struct_by_value.c
 * 覆盖: struct 作为函数参数 (pass-by-value)
 *
 * Point { x, y }
 * make_point(10, 20) → 调用, 计算 p.x*p.y + offset
 * p1 = (3, 4), p2 = (5, 6), p3 = (10, 20)
 *   sum: (3*4=12) + (5*6=30) + (10*20=200) = 242
 * 退出码: 242
 */
struct Point {
    int x;
    int y;
};

int compute(struct Point p, int offset) {
    return p.x * p.y + offset;
}

int main(void) {
    struct Point p1 = {3, 4};
    struct Point p2 = {5, 6};
    struct Point p3 = {10, 20};
    int sum = 0;
    sum += compute(p1, 0);   // 12
    sum += compute(p2, 0);   // 30
    sum += compute(p3, 0);   // 200
    return sum;  // 242
}
