# 反编译能力测试集 · Decompiler Capability Benchmark (DCB)

**中文** · [English](README.en.md)

本目录**自足**：32 个源文件，无外部依赖、无隐藏元数据。用系统 `gcc` / `g++` 加随附的 `build.sh` 即可生成 128 个测试二进制。

| | |
|---|---|
| **中文名** | 反编译能力测试集 |
| **英文名** | **Decompiler Capability Benchmark (DCB)** |
| 规模 | 32 个源文件 → **128** 个测试二进制 |
| 用途 | 衡量反编译器的产物能否被重新编译、运行结果是否与原程序一致 |

---

## 1. 实测结果

> **bindec 是 binforge 平台的二进制反编译模块（https://bindeep.cn/）** ，是本系列被测的对象。

以下数字由本测试集生成的 128 个二进制，经三个反编译工具处理后**重新编译、链接、执行**得出。

**被测版本**：bindec 1.0.2 / IDA Pro 9.1 / Ghidra 12.1.4


### 1.1 结果对照：直接反编译 vs 经过修补

**每一个「测试二进制 × 工具」都走这四步**：

| 步骤 | 做什么 | 测什么 |
|---|---|---|
| **步骤 1** | 反编译 | 得到**原始产物**（反编译器直接吐出来的 C） |
| **步骤 2** | `gcc -c` 原始产物 | 测**原生产物质量** |
| **步骤 3** | 对原始产物做源码修补 | 补声明、换写法、注入 C++ class 壳；**bindec 跳过这一步** |
| **步骤 4** | `gcc -c` → `ld` → 执行 | 测拿去实际能不能用 |

**bindec 没有步骤 3** —— 它的产物直接进 gcc，所以它的「直接反编译」和「经过修补」是同一个产物。

| 工具 | 【直接反编译】能编译 | 【直接反编译】能跑对 | 【经过修补】能编译 | 【经过修补】能跑对 |
|---|---|---|---|---|
| **bindec**（**不需要修补**） | **117 / 128 = 91.4%** | **111 / 128 = 86.7%** | **不需要修补** | **不需要修补** |
| IDA Pro 9.1 | **0 / 128 = 0.0%** | 0 / 128 = 0.0% | 57 / 128 = 44.5% | 52 / 128 = 40.6% |
| Ghidra 12.1.4 | **22 / 128 = 17.2%** | 0 / 128 = 0.0% | 44 / 128 = 34.4% | 44 / 128 = 34.4% |

> **bindec 的「经过修补」两列都标记为“不需要修补”**，因为它**不存在修补环节** —— 反编译产物直接进 gcc。
> 这正是本表要说明的核心：**另外两家必须经过修补才能编译，bindec 不需要。**

> 📌 **放宽编译参数时 bindec 是多少？** 如果允许 `-fpermissive` 并附一份 C++ 辅助头文件，
> bindec 是 **127 / 128 = 99.2%** 能编译、**121 / 128 = 94.5%** 能跑对。
> ⇒ 上表的 117 / 111 是**原样口径**（产物长什么样就拿什么去编）；
> 两者之差**全部落在 C++ 的严格类型转换**上（`invalid conversion` / `narrowing conversion`），
> **不是 ABI 问题，也不是语义问题**。

**源码修补的净贡献：**

| 工具 | 能编译 | 能跑对 |
|---|---|---|
| IDA Pro 9.1 | 0% → 44.5%（**+44.5 pp**） | 0% → 40.6%（+40.6 pp） |
| Ghidra 12.1.4 | 17.2% → 34.4%（**+17.2 pp**） | 0% → 34.4%（+34.4 pp） |
| **bindec** | **不需要修补**（0 pp） | **不需要修补**（0 pp） |

两个直接可见的事实：

**① IDA 的 128 个原始产物，一个都编不过。** 这不是黑 IDA —— 它的反编译**内容是对的**，例如 `enum_basic` 的产物 12 行里 `return 20` 完全正确，只是函数名前多了一个 `__fastcall`（MSVC 调用约定宏，只存在于 IDA 自己的类型库里）。

**② 全部 22 个 Ghidra 能编过的原始产物，跑对的仍是 0。** 能编译不等于行为正确 —— 静态分析工具能读懂的代码，未必还原了原程序的语义。

### 1.2 按类别（经过修补后）

每一类是独立的一组（该类用例数 × 4 变体）：

| 类别 | 数量 | bindec 编译 / 跑对 | IDA 编译 / 跑对 | Ghidra 编译 / 跑对 |
|---|---|---|---|---|
| `c-basic` | 48 | **48/48 = 100.0%** / 100.0% | 39/48 = 81.2% / 75.0% | 28/48 = 58.3% / 58.3% |
| `c-advanced` | 48 | **48/48 = 100.0%** / **42/48 = 87.5%** | 16/48 = 33.3% / 33.3% | 16/48 = 33.3% / 33.3% |
| `cpp-oop` | 32 | **21/32 = 65.6%** / 65.6% | 2/32 = 6.2% / **0.0%** | **0/32 = 0.0%** / 0.0% |

难度递增非常清晰：`c-basic` → `c-advanced` 的落差主要来自 ABI（结构体返回、变参），`cpp-oop` 则是对象模型与异常表 —— 这是伪 C 最容易彻底失真的地方。

`cpp-oop` 那一列值得单独看：**IDA 编译通过 2 个，跑对 0 个。**

## 2. 目录结构

```
DCB/
├── c-basic/          12 个   入门：C 基本语法
│   ├── control-flow/         break_continue, for_loop_basic, for_loop_nested,
│   │                         if_else_simple, nested_if, switch_case, while_do_while
│   ├── data-types/           enum_basic, multi_dim_array, struct_basic, union_basic
│   └── pointers/             pointer_arith
│
├── c-advanced/       12 个   进阶：编译器与 ABI 相关
│   ├── func-ptr/             func_ptr_callback, func_ptr_dispatch
│   ├── goto/                 goto_cross_decl, goto_simple
│   ├── inline-asm/           inline_asm_basic, inline_asm_extended
│   ├── setjmp/               setjmp_longjmp
│   ├── struct-return/        struct_by_value, struct_return_large, struct_return_small
│   └── variadic/             variadic_printf, variadic_sum
│
└── cpp-oop/           8 个   C++：对象模型与异常
    ├── class/                class_basic
    ├── exceptions/           try_catch
    ├── inheritance/          inherit_multi, inherit_single
    ├── templates/            template_class, template_func
    └── virtual/              virtual_dtor, virtual_func
```

每个用例是**单文件、单 `main`、无外部输入、无网络、不依赖第三方库**，因此在任意机器上编译结果都可复现。

---

## 3. 生成 128 个二进制

### 3.1 四个变体

| 变体 | 含义 | 编译命令 |
|---|---|---|
| `x64_dyn` | 64 位 · 动态链接 | `gcc -O0 -no-pie -g` |
| `x64_static` | 64 位 · 静态链接 | `gcc -O0 -g -static -D_GNU_SOURCE=1` |
| `x86_dyn` | 32 位 · 动态链接 | `gcc -O0 -m32 -no-pie -g` |
| `x86_static` | 32 位 · 静态链接 | `gcc -O0 -m32 -g -static -D_GNU_SOURCE=1` |

`.cpp` 用 `g++` 替换 `gcc`，其余参数完全一致。

两个维度的用意：

- **架构（x64 / x86）** —— 32 位和 64 位的调用约定、结构体返回、变参传递规则不同。反编译器在这两处最容易出错。
- **链接方式（dyn / static）** —— 动态链接时 libc 符号由 PLT/GOT 提供，反编译器容易沿用符号名；静态链接时整座 glibc 被链进二进制，产物里必须自己补出所有函数原型。**这是区分「伪 C」和「编译单元」最锋利的一档**：同一个 `enum_basic`，静态版产物 bindec 337 行，IDA 12 行、Ghidra 16 行。

### 3.2 前置依赖

```bash
sudo apt install gcc g++          # C / C++ 编译器
sudo apt install gcc-multilib g++-multilib   # 32 位支持（必需）
```

验证 32 位可用：

```bash
gcc -m32 -E -x c /dev/null && echo "multilib OK"
```

> ⚠️ **multilib 是硬依赖。** 缺它时 64 个 `x86_*` 二进制会全部编译失败 —— 而 128 会悄悄变成 64。如果你的测试结果里 32 位大面积「失败」，先确认这一条。

### 3.3 一键生成

用随附的 `build.sh` 一键生成：

```bash
bash build.sh
```

预期输出：

```
生成 128 / 128 个二进制
```

产物落在 `bin/<用例名>_<变体>`，共 128 个。

若输出的数目少于 128，脚本会列出失败的变体名并以非零码退出。最常见的原因是缺 32 位支持：

```
有 64 个编译失败。若集中在 x86_* 变体，请先确认 32 位支持已安装：
    sudo apt install gcc-multilib g++-multilib
```

### 3.4 产物命名

```
<用例名>_<变体>       例如：enum_basic_x64_dyn
```

共 128 个，全部平铺在 `bin/` 下。

---

## 4. 这个测试集要考什么

测试集不是随机收集的 C 程序，而是**按「反编译器最可能在哪里失手」分层挑选**的：

| 类别 | 考什么 | 代表用例 |
|---|---|---|
| `c-basic/control-flow` | 基本控制流是否还原正确 | `switch_case`、`nested_if` |
| `c-basic/data-types` | 结构体 / 枚举 / 联合 / 多维数组的类型信息能否自洽 | `enum_basic`、`struct_basic` |
| `c-basic/pointers` | 指针算术的表达式重建 | `pointer_arith` |
| `c-advanced/struct-return` | **ABI 层面**：结构体按值返回（寄存器 / 内存两种路径） | `struct_return_small`、`struct_return_large` |
| `c-advanced/variadic` | **ABI 层面**：可变参数传递（va_list 布局） | `variadic_printf`、`variadic_sum` |
| `c-advanced/func-ptr` | 间接调用与函数指针表 | `func_ptr_dispatch` |
| `c-advanced/goto` | **非结构化控制流**：跳转表 / cross declaration | `goto_simple` |
| `c-advanced/inline-asm` | 编译器内联汇编黑盒 | `inline_asm_basic` |
| `c-advanced/setjmp` | 非局部跳转，编译器生成的隐藏状态 | `setjmp_longjmp` |
| `cpp-oop/virtual` | **vtable / 对象模型**：这是伪 C 最容易彻底失真的地方 | `virtual_func`、`virtual_dtor` |
| `cpp-oop/exceptions` | **异常处理表**（`.gcc_except_table`）的还原 | `try_catch` |
| `cpp-oop/inheritance` | 成员布局与基类偏移 | `inherit_multi` |
| `cpp-oop/templates` | 模板实例化后的符号还原 | `template_class` |

三类难度在系列中被明确区分：

- **写法问题** —— 工具用了自己的词汇（`__fastcall`、`undefined8`），跑正则即可换成标准 C
- **语义问题** —— 缺类型定义、缺函数声明、C++ 成员调用方式不对，必须真正理解二进制
- **C++ 对象模型** —— 连「这是什么」都判断错了，正则和桩都救不回来

---

## 5. 关于测试集的来源

测试集为原创编写，用于本次对比，无第三方来源。

如需复现系列中引用的具体数字（91.4% / 44.5% / 34.4% 等），请以系列正文所述的协议和工具版本为准：

- 被测版本：bindec 1.0.2 / IDA Pro 9.1 / Ghidra 12.1.4
- bindec 一列是 **bindec 1.0.2** 的实测；IDA / Ghidra 两列来自**同一次运行**（同一批二进制、同一组变体、同一套协议），不是跨时点拼接
- 所有百分比均可从原始结果数据重算，未手工填写

> 每个用例的 `main` 都返回各自的计算结果作为判据，**32 个退出码全部非 0 且互不相同** —— 若都返回 0，任何「跑错」的产物也会返回 0，判据就失效了。可用 `./bin/<用例>_x64_dyn ; echo $?` 逐一复核。