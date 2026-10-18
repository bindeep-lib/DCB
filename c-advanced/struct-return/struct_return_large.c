/**
 * struct_return_large.c
 * 覆盖: struct 返回 ≥16 字节 (hidden pointer)
 *
 * Large { a, b, c, d, e }  (5*4 = 20 bytes > 16)
 * make_large(1,2,3,4,5) → return struct (hidden pointer 传递)
 *   sum of all fields = 15
 * 退出码: 15
 */
struct Large {
    int a;
    int b;
    int c;
    int d;
    int e;
};

struct Large make_large(int a, int b, int c, int d, int e) {
    struct Large l;
    l.a = a;
    l.b = b;
    l.c = c;
    l.d = d;
    l.e = e;
    return l;
}

int main(void) {
    struct Large l = make_large(1, 2, 3, 4, 5);
    return l.a + l.b + l.c + l.d + l.e;  // 15
}
