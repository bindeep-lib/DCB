/**
 * if_else_simple.c
 * 覆盖: if/else 单/双分支
 *
 * 计算: 根据 a 的正负返回不同值
 *   a > 0: return a * 2 = 200  (输入 100)
 *   a < 0: return a            = -50 (输入 -50)
 *   a == 0: return 0
 *
 * 期望退出码: 200
 */
int compute(int a) {
    if (a > 0) {
        return a * 2;
    } else if (a < 0) {
        return a;
    } else {
        return 0;
    }
}

int main(void) {
    return compute(100);
}
