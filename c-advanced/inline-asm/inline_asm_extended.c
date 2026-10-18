/**
 * inline_asm_extended.c
 * 覆盖: GCC extended asm (input/output/clobber)
 *
 * 用 extended asm 将 result 改为指定值
 * 退出码: 77
 */
int main(void) {
    int result = 0;
    int input = 100;
    int output = 0;

    // extended asm: output=output, input=input, clobber memory
    asm volatile (
        "movl %1, %0"
        : "=r"(output)
        : "r"(input)
        : "memory"
    );

    result = output - 23;  // 100 - 23 = 77
    return result;
}
