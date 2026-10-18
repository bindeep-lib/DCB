/**
 * switch_case.c
 * 覆盖: switch 多 case + fallthrough
 *
 * value=2, 命中 case 2: 10 + case 3 fallthrough: 10 + 5 = 15
 * 退出码: 15
 */
int main(void) {
    int value = 2;
    int sum = 0;

    switch (value) {
        case 1:
            sum += 1;
            break;
        case 2:
            sum += 10;
            // fallthrough
        case 3:
            sum += 5;
            break;
        case 4:
        case 5:
            sum += 100;
            break;
        default:
            sum += 999;
            break;
    }

    return sum;  // 15
}
