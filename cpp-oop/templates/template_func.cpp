/**
 * template_func.cpp
 * 覆盖: 函数模板 (多实例化)
 *
 * template<T> max(a, b) → 返回较大值
 * max(3, 5) = 5
 * max(2.5, 1.5) = 2.5  (用 int: max(2, 1) = 2)
 * max(10, 7) = 10
 *
 * sum = 5 + 2 + 10 = 17
 * 退出码: 17
 */
template<typename T>
T my_max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    int a = my_max(3, 5);     // 5
    int b = my_max(2, 1);     // 2
    int c = my_max(10, 7);    // 10
    return a + b + c;  // 17
}
