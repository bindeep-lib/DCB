/**
 * setjmp_longjmp.c
 * 覆盖: setjmp/longjmp 异常风格流程
 *
 * 第一次 setjmp 返回 0: 初始化, 调用 deep_func
 *   deep_func 错误: longjmp 返回到 setjmp (值=1)
 * setjmp 第二次返回 1: 错误处理
 *
 * 退出码: 42 (错误处理返回值)
 */
#include <setjmp.h>

static jmp_buf jump_buffer;

int deep_func(int value) {
    if (value < 0) {
        longjmp(jump_buffer, 1);  // 错误, 跳回 setjmp
    }
    return value * 2;
}

int main(void) {
    int result = 0;
    int val = -1;  // 触发 longjmp

    if (setjmp(jump_buffer) == 0) {
        // 正常路径
        result = deep_func(val);
    } else {
        // 错误路径
        result = 42;
    }
    return result;  // 42
}
