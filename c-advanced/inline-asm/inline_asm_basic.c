/**
 * inline_asm_basic.c
 * 覆盖: GCC basic asm (no operands)
 *
 * 调用 basic asm, 然后返回特定值
 * 退出码: 99
 */
int main(void) {
    // basic asm - 无 operands, 仅指令
    asm("nop");
    asm("nop");
    return 99;
}
