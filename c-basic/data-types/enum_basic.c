/**
 * enum_basic.c
 * 覆盖: enum + switch
 *
 * enum Color { RED=1, GREEN=2, BLUE=3 }
 * 选中 GREEN (2), sum = 20
 * 退出码: 20
 */
enum Color {
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

int main(void) {
    enum Color c = GREEN;
    int sum = 0;

    switch (c) {
        case RED:   sum = 10; break;
        case GREEN: sum = 20; break;
        case BLUE:  sum = 30; break;
    }
    return sum;  // 20
}
