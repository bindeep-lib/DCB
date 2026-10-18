/**
 * union_basic.c
 * 覆盖: union 共享内存
 *
 * union U { int i; char c[4]; }
 * 写入 i = 0x01020304 (little-endian)
 *   c[0] = 0x04, c[1] = 0x03, c[2] = 0x02, c[3] = 0x01
 * sum = c[0] + c[1] + c[2] + c[3] = 4+3+2+1 = 10
 * 退出码: 10
 */
union U {
    int i;
    char c[4];
};

int main(void) {
    union U u;
    u.i = 0x01020304;
    int sum = u.c[0] + u.c[1] + u.c[2] + u.c[3];
    return sum;  // little-endian: 4+3+2+1 = 10
}
