/**
 * while_do_while.c
 * 覆盖: while 与 do-while 区分
 *
 * while 循环: 条件 false 时不进入, sum=0
 * do-while 循环: 至少执行一次, sum=10
 * 总和: 10
 * 退出码: 10
 */
int main(void) {
    int sum = 0;
    int x = 10;

    // while: x 已经是 10, 不进入
    while (x < 5) {
        sum += x;
        x++;
    }

    // do-while: 至少执行一次
    int y = 10;
    do {
        sum += y;
        y++;
    } while (y < 5);

    return sum;  // 10
}
