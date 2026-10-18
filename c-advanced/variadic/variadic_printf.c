/**
 * variadic_printf.c
 * 覆盖: 自定义 printf (使用 vfprintf)
 *
 * 输出: "x=42, y=hello\n"
 * 验证方式: stdout 内容包含 "42" 和 "hello"
 * 退出码: 42 (固定)
 */
#include <stdio.h>
#include <stdarg.h>

void my_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

int main(void) {
    int x = 42;
    my_printf("x=%d, y=%s\n", x, "hello");
    return 42;
}
