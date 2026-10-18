#!/bin/bash
# 生成 128 个测试二进制：32 源文件 × 4 变体
#
# 用法：把本脚本放在 test_suite/ 目录下执行
#   bash build.sh
#
# 输出：bin/<用例名>_<变体>，共 128 个
# 依赖：gcc / g++；32 位变体需 gcc-multilib、g++-multilib

set -u

cd "$(dirname "$0")" || exit 1
mkdir -p bin

n=0
fail=0

for src in $(find . -name '*.c' -o -name '*.cpp' | sort); do
  name=$(basename "$src")
  name="${name%.*}"

  case "$src" in
    *.cpp) CC=g++ ;;
    *)     CC=gcc ;;
  esac

  # 动态链接变体：-no-pie
  for v in x64_dyn x86_dyn; do
    m32=""
    [ "$v" = "x86_dyn" ] && m32="-m32"
    if $CC -O0 -no-pie -g $m32 -o "bin/${name}_${v}" "$src"; then
      n=$((n + 1))
    else
      fail=$((fail + 1))
      echo "  [FAIL] ${name}_${v}"
    fi
  done

  # 静态链接变体：-no-pie 与 -static 冲突，故不取；改加 -D_GNU_SOURCE=1
  for v in x64_static x86_static; do
    m32=""
    [ "$v" = "x86_static" ] && m32="-m32"
    if $CC -O0 -g $m32 -static -D_GNU_SOURCE=1 -o "bin/${name}_${v}" "$src"; then
      n=$((n + 1))
    else
      fail=$((fail + 1))
      echo "  [FAIL] ${name}_${v}"
    fi
  done
done

echo "生成 $n / 128 个二进制"

if [ "$fail" -gt 0 ]; then
  echo
  echo "有 $fail 个编译失败。若集中在 x86_* 变体，请先确认 32 位支持已安装："
  echo "    sudo apt install gcc-multilib g++-multilib"
  echo "    gcc -m32 -E -x c /dev/null && echo 'multilib OK'"
  exit 1
fi

exit 0