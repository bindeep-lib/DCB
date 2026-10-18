/**
 * for_loop_nested.c
 * 覆盖: 嵌套 for 循环 (2D 求和)
 *
 * 计算: i 从 0..2, j 从 0..2, sum += i*3 + j
 *   i=0: 0+1+2 = 3
 *   i=1: 3+4+5 = 12
 *   i=2: 6+7+8 = 21
 * 总和: 36
 * 退出码: 36
 */
int main(void) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += i * 3 + j;
        }
    }
    return sum;
}
