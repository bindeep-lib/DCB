/**
 * pointer_arith.c
 * 覆盖: 指针算术 *(p+i) vs p[i]
 *
 * arr = {10, 20, 30, 40, 50}
 * 通过指针访问:
 *   *p = 10
 *   *(p+1) = 20
 *   p[2] = 30
 *   *(p+3) = 40
 *   p[4] = 50
 * sum = 10+20+30+40+50 = 150
 * 退出码: 150
 */
int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;

    int sum = 0;
    sum += *p;        // 10
    sum += *(p + 1);  // 20
    sum += p[2];      // 30
    sum += *(p + 3);  // 40
    sum += p[4];      // 50
    return sum;  // 150
}
