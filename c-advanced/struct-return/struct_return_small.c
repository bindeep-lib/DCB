/**
 * struct_return_small.c
 * 覆盖: struct 返回 <16 字节 (rax 寄存器对)
 *
 * Small { a, b }
 * make_small(10, 20) → return struct
 *   .a + .b = 30
 *   main 接收后取 .a + .b = 30
 * 退出码: 30
 */
struct Small {
    int a;
    int b;
};

struct Small make_small(int a, int b) {
    struct Small s;
    s.a = a;
    s.b = b;
    return s;
}

int main(void) {
    struct Small s = make_small(10, 20);
    return s.a + s.b;  // 30
}
