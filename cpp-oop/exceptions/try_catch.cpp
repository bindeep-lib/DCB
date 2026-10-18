/**
 * try_catch.cpp
 * 覆盖: C++ 异常处理 (throw/catch)
 *
 * risky(0) → 正常, return 10
 * risky(-1) → throw 99, catch 块 return 99
 *
 * main: 调用两次
 *   s = 10 + 99 = 109
 * 退出码: 109
 */
#include <stdexcept>

int risky(int x) {
    if (x < 0) {
        throw std::runtime_error("error");
    }
    return 10;
}

int main() {
    int sum = 0;
    try {
        sum += risky(0);  // 10
    } catch (...) {
        sum += 1;
    }

    try {
        sum += risky(-1);  // throw
    } catch (...) {
        sum += 99;  // 错误处理
    }
    return sum;  // 10 + 99 = 109
}
