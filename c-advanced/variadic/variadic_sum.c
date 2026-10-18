/**
 * variadic_sum.c
 * 覆盖: 自定义 variadic 函数求和
 *
 * sum(3, 1, 2, 3) = 6
 * sum(5, 10, 20, 30, 40, 50) = 150
 * sum(4, 5, 5, 5, 5) = 20
 * 总和 = 6 + 150 + 20 = 176 (超出 0-255 范围, 取模: 176)
 * 退出码: 176
 */
#include <stdarg.h>

int sum(int n, ...) {
    int total = 0;
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int main(void) {
    int s1 = sum(3, 1, 2, 3);      // 6
    int s2 = sum(5, 10, 20, 30, 40, 50);  // 150
    int s3 = sum(4, 5, 5, 5, 5);  // 20
    return s1 + s2 + s3;  // 176
}
