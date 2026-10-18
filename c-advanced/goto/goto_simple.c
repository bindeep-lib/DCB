/**
 * goto_simple.c
 * 覆盖: goto 单层跳转 (错误处理)
 *
 * 模拟: try { open + return value } catch (close + return error)
 * 正常路径: return 100
 * 退出码: 100
 */
#include <stdio.h>

int open_file(int x) { return x; }
void close_file(int x) { (void)x; }

int process(int flag) {
    int handle = -1;
    int result = 0;

    handle = open_file(flag);
    if (handle < 0) {
        result = -1;
        goto cleanup;
    }

    result = handle * 100;
    goto cleanup;

cleanup:
    if (handle >= 0) {
        close_file(handle);
    }
    return result;  // 100
}

int main(void) {
    return process(1);  // 100
}
