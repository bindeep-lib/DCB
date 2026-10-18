/**
 * nested_if.c
 * 覆盖: 嵌套 if 3 层
 *
 * 计算: 100 → 100 → 100 → 100 = 100
 * 退出码: 100
 */
int classify(int x, int y, int z) {
    if (x > 0) {
        if (y > 0) {
            if (z > 0) {
                return x + y + z;  // 100
            } else {
                return 1;
            }
        } else {
            return 2;
        }
    } else {
        return 3;
    }
}

int main(void) {
    return classify(50, 30, 20);
}
