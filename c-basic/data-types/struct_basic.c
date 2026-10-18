/**
 * struct_basic.c
 * 覆盖: struct 定义 + 字段访问
 *
 * struct Point { int x, y, z; }
 * p = {10, 20, 30}
 * return p.x + p.y + p.z = 60
 * 退出码: 60
 */
struct Point {
    int x;
    int y;
    int z;
};

int main(void) {
    struct Point p;
    p.x = 10;
    p.y = 20;
    p.z = 30;
    return p.x + p.y + p.z;
}
