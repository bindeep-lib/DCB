/**
 * func_ptr_callback.c
 * 覆盖: 函数指针作为参数 (回调)
 *
 * apply(10, double_it) = 20
 * apply(10, triple_it) = 30
 * apply(20, add_one) = 21
 * sum = 20 + 30 + 21 = 71
 * 退出码: 71
 */
int double_it(int x) { return x * 2; }
int triple_it(int x) { return x * 3; }
int add_one(int x)   { return x + 1; }

int apply(int x, int (*op)(int)) {
    return op(x);
}

int main(void) {
    int s = 0;
    s += apply(10, double_it);  // 20
    s += apply(10, triple_it);  // 30
    s += apply(20, add_one);    // 21
    return s;  // 71
}
