/**
 * func_ptr_dispatch.c
 * 覆盖: switch by func ptr (dispatch table)
 *
 * ops[0]=add (1+2=3), ops[1]=sub (10-3=7), ops[2]=mul (5*4=20)
 * sum = 3 + 7 + 20 = 30
 * 退出码: 30
 */
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

typedef int (*binop)(int, int);

int main(void) {
    binop ops[3] = {add, sub, mul};
    int result = 0;

    result += ops[0](1, 2);   // add: 3
    result += ops[1](10, 3);  // sub: 7
    result += ops[2](5, 4);   // mul: 20
    return result;  // 30
}
