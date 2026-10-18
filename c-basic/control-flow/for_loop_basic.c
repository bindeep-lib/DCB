/**
 * for_loop_basic.c
 * 覆盖: for 累加循环
 *
 * 计算: sum(0..9) = 45
 * 退出码: 45
 */
int main(void) {
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    return sum;
}
