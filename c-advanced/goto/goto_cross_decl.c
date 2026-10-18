/**
 * goto_cross_decl.c
 * 覆盖: goto 越过变量声明 (bindec 已知困难)
 *
 * path 1: 声明 x, y → sum x+y → return
 * path 2: goto 到 end → 直接 return 0
 * 正常 path 1: return 5+7 = 12
 * 退出码: 12
 */
int main(void) {
    int result = 0;
    int flag = 1;

    if (flag) {
        goto end;
    }

    int x = 5;  // 跨过声明
    int y = 7;
    result = x + y;

end:
    if (flag) {
        result = 12;
    }
    return result;  // 12
}
