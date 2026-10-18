/**
 * break_continue.c
 * 覆盖: break/continue 语义
 *
 * 循环 0..9:
 *   i=0 (偶): continue
 *   i=1: sum=1
 *   i=2 (偶): continue
 *   i=3: sum=4
 *   i=4 (偶): continue
 *   i=5: sum=9
 *   i=6 (偶): continue
 *   i=7: sum=16
 *   i=8 (偶): continue
 *   i=9: sum=25
 *   i=10: break
 * 退出码: 25
 */
int main(void) {
    int sum = 0;
    for (int i = 0; i < 100; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过偶数
        }
        sum += i;
        if (i > 8) {
            break;  // i > 8 时退出
        }
    }
    return sum;  // 1+3+5+7+9 = 25
}
