# Decompiler Capability Benchmark (DCB)

[中文](README.md) · **English**

The test suite used throughout the series *"Can decompiled code be recompiled?"*.

This repository is **self-contained**: 32 source files, no external dependencies, no hidden metadata. With the system `gcc` / `g++` and the bundled `build.sh`, you can generate 128 test binaries.

| | |
|---|---|
| **Chinese name** | 反编译能力测试集 |
| **English name** | **Decompiler Capability Benchmark (DCB)** |
| Scale | 32 source files → **128** test binaries |
| Purpose | Measure whether a decompiler's output can be recompiled, and whether it still behaves like the original program |

---

## 1. Measured results

> **bindec is the binary decompilation module of the binforge platform (https://bindeep.cn/)** — it is the subject under test in this series.

The numbers below come from running the 128 binaries produced by this suite through three decompilers, then **recompiling, linking and executing** the results.

**Versions tested**: bindec 1.0.1 / IDA Pro 9.1 / Ghidra 12.1.4

### 1.1 Raw decompilation vs. after source repair

**Every "test binary × tool" cell goes through these four steps**:

| Step | What | Measures |
|---|---|---|
| **Step 1** | Decompile | Produce the **raw artifact** (the C the decompiler emits directly) |
| **Step 2** | `gcc -c` the raw artifact | Measures **raw artifact quality** |
| **Step 3** | Source repair on the raw artifact | Add missing declarations, rewrite non-standard constructs, inject C++ class stubs; **bindec skips this step** |
| **Step 4** | `gcc -c` → `ld` → execute | Measures whether it is actually usable |

**bindec has no step 3** — its output goes straight into gcc, so its "raw decompilation" and "after repair" are the same artifact.

| Tool | 【Raw】compiles | 【Raw】behaves correctly | 【Repaired】compiles | 【Repaired】behaves correctly |
|---|---|---|---|---|
| **bindec** (**needs no repair**) | **113 / 128 = 88.3%** | **100 / 128 = 78.1%** | **needs no repair** | **needs no repair** |
| IDA Pro 9.1 | **0 / 128 = 0.0%** | 0 / 128 = 0.0% | 57 / 128 = 44.5% | 52 / 128 = 40.6% |
| Ghidra 12.1.4 | **22 / 128 = 17.2%** | 0 / 128 = 0.0% | 44 / 128 = 34.4% | 44 / 128 = 34.4% |

> **Both "after repair" columns for bindec are marked "needs no repair"** because it **has no repair stage** — the decompiled output goes directly into gcc.
> This is the core point of the table: **the other two can only compile after repair; bindec does not need it.**

**Net contribution of source repair:**

| Tool | Compiles | Behaves correctly |
|---|---|---|
| IDA Pro 9.1 | 0% → 44.5% (**+44.5 pp**) | 0% → 40.6% (+40.6 pp) |
| Ghidra 12.1.4 | 17.2% → 34.4% (**+17.2 pp**) | 0% → 34.4% (+34.4 pp) |
| **bindec** | **needs no repair** (0 pp) | **needs no repair** (0 pp) |

Two facts are directly visible:

**① Not one of IDA's 128 raw artifacts compiles.** This is not a dig at IDA — its decompiled **content is correct**. For example, `enum_basic` produces 12 lines in which `return 20` is exactly right; the only problem is a `__fastcall` in front of the function name (an MSVC calling-convention macro that exists only inside IDA's own type library).

**② Of the 22 raw artifacts Ghidra can compile, zero still behave correctly.** Compiling is not the same as being correct — code a static analysis tool can read is not necessarily code that preserves the original program's semantics.

### 1.2 By category (after repair)

Each category is an independent group (number of cases × 4 variants):

| Category | Count | bindec compile / correct | IDA compile / correct | Ghidra compile / correct |
|---|---|---|---|---|
| `c-basic` | 48 | **48/48 = 100.0%** / 100.0% | 39/48 = 81.2% / 75.0% | 28/48 = 58.3% / 58.3% |
| `c-advanced` | 48 | **43/48 = 89.6%** / 77.1% | 16/48 = 33.3% / 33.3% | 16/48 = 33.3% / 33.3% |
| `cpp-oop` | 32 | **22/32 = 68.8%** / 46.9% | 2/32 = 6.2% / **0.0%** | **0/32 = 0.0%** / 0.0% |

The difficulty gradient is unmistakable: the drop from `c-basic` to `c-advanced` comes mainly from the ABI (struct return, variadic passing), while `cpp-oop` is about the object model and the exception tables — the place where pseudocode is most likely to be completely wrong.

Worth looking at the `cpp-oop` column on its own: **IDA compiles 2, and 0 of them behave correctly.**

### 1.3 bindec's own failures (not hidden)

88.3% is not 100%. bindec has **15 cells that do not compile** and **another 13 that compile but behave incorrectly**:

| Case | Count | Detail |
|---|---|---|
| Failed during decompilation | 5 | Timeout / crash |
| Failed during compilation | 10 | 5 of them involve missing declarations and missing types (in static C++ output, libgcc/libstdc++ symbols such as `_Unwind_GetDataRelBase` and `__cxa_call_terminate` are undeclared) |
| Compiled but wrong result | 13 | **All on 32-bit** (x86-*); zero on x86-64 |

The 13 incorrect results cluster on 32-bit ABI and object-model paths:

```
struct_return_large   ×2    struct_return_small  ×2    setjmp_longjmp    ×1
variadic_printf       ×1    class_basic         ×2    inherit_single    ×1
template_class        ×2    virtual_dtor        ×1    virtual_func      ×1
```

---

## 2. Directory layout

```
DCB/
├── c-basic/          12     Introductory: core C syntax
│   ├── control-flow/       break_continue, for_loop_basic, for_loop_nested,
│   │                       if_else_simple, nested_if, switch_case, while_do_while
│   ├── data-types/         enum_basic, multi_dim_array, struct_basic, union_basic
│   └── pointers/           pointer_arith
│
├── c-advanced/       12     Advanced: compiler- and ABI-related
│   ├── func-ptr/           func_ptr_callback, func_ptr_dispatch
│   ├── goto/               goto_cross_decl, goto_simple
│   ├── inline-asm/         inline_asm_basic, inline_asm_extended
│   ├── setjmp/             setjmp_longjmp
│   ├── struct-return/      struct_by_value, struct_return_large, struct_return_small
│   └── variadic/           variadic_printf, variadic_sum
│
└── cpp-oop/           8     C++: object model and exceptions
    ├── class/              class_basic
    ├── exceptions/         try_catch
    ├── inheritance/        inherit_multi, inherit_single
    ├── templates/          template_class, template_func
    └── virtual/            virtual_dtor, virtual_func
```

Each case is a **single file, single `main`, no external input, no network, no third-party libraries**, so the compilation result is reproducible on any machine.

---

## 3. Generating the 128 binaries

### 3.1 The four variants

| Variant | Meaning | Compile command |
|---|---|---|
| `x64_dyn` | 64-bit · dynamically linked | `gcc -O0 -no-pie -g` |
| `x64_static` | 64-bit · statically linked | `gcc -O0 -g -static -D_GNU_SOURCE=1` |
| `x86_dyn` | 32-bit · dynamically linked | `gcc -O0 -m32 -no-pie -g` |
| `x86_static` | 32-bit · statically linked | `gcc -O0 -m32 -g -static -D_GNU_SOURCE=1` |

`.cpp` files use `g++` instead of `gcc`; all other arguments are identical.

Why these two dimensions:

- **Architecture (x64 / x86)** — calling conventions, struct return and variadic passing rules differ between 32-bit and 64-bit. These are exactly the places decompilers get wrong most often.
- **Linking (dyn / static)** — with dynamic linking, libc symbols come from the PLT/GOT and a decompiler can often just reuse the symbol names; with static linking, the whole of glibc is linked into the binary, so the output must supply every function prototype itself. **This is the sharpest single discriminator between "pseudocode" and "a translation unit"**: for the same `enum_basic`, the static build yields 813 lines from bindec, 12 from IDA and 16 from Ghidra.

### 3.2 Prerequisites

```bash
sudo apt install gcc g++                    # C / C++ compilers
sudo apt install gcc-multilib g++-multilib # 32-bit support (required)
```

Verify 32-bit support:

```bash
gcc -m32 -E -x c /dev/null && echo "multilib OK"
```

> ⚠️ **multilib is a hard dependency.** Without it all 64 `x86_*` binaries fail to compile — and 128 silently becomes 64. If your results show widespread 32-bit "failures", check this first.

### 3.3 One-command build

```bash
bash build.sh
```

Expected output:

```
生成 128 / 128 个二进制
```

Artifacts land in `bin/<case>_<variant>`, 128 in total.

If fewer than 128 are produced, the script lists the failing variants and exits non-zero. The most common cause is missing 32-bit support:

```
有 64 个编译失败。若集中在 x86_* 变体，请先确认 32 位支持已安装：
    sudo apt install gcc-multilib g++-multilib
```

### 3.4 Artifact naming

```
<case>_<variant>       e.g. enum_basic_x64_dyn
```

128 in total, all flat under `bin/`.

---

## 4. What this test suite is designed to probe

The suite is not a random collection of C programs. Cases were **stratified by where decompilers are most likely to fail**:

| Category | What it probes | Representative cases |
|---|---|---|
| `c-basic/control-flow` | Whether basic control flow is reconstructed correctly | `switch_case`、`nested_if` |
| `c-basic/data-types` | Whether type information for structs / enums / unions / multidim arrays is self-consistent | `enum_basic`、`struct_basic` |
| `c-basic/pointers` | Expression reconstruction for pointer arithmetic | `pointer_arith` |
| `c-advanced/struct-return` | **ABI level**: struct return by value (register and memory paths) | `struct_return_small`、`struct_return_large` |
| `c-advanced/variadic` | **ABI level**: variadic argument passing (`va_list` layout) | `variadic_printf`、`variadic_sum` |
| `c-advanced/func-ptr` | Indirect calls and function pointer tables | `func_ptr_dispatch` |
| `c-advanced/goto` | **Non-structured control flow**: jump tables / cross declarations | `goto_simple` |
| `c-advanced/inline-asm` | Compiler-emitted inline assembly as a black box | `inline_asm_basic` |
| `c-advanced/setjmp` | Non-local jumps and compiler-generated hidden state | `setjmp_longjmp` |
| `cpp-oop/virtual` | **vtables / object model**: where pseudocode most often goes completely wrong | `virtual_func`、`virtual_dtor` |
| `cpp-oop/exceptions` | Reconstruction of the **exception table** (`.gcc_except_table`) | `try_catch` |
| `cpp-oop/inheritance` | Member layout and base class offsets | `inherit_multi` |
| `cpp-oop/templates` | Symbol reconstruction after template instantiation | `template_class` |

The series draws an explicit distinction between three levels of difficulty:

- **Surface-level problems** — the tool used its own vocabulary (`__fastcall`, `undefined8`); a regular expression is enough to rewrite these into standard C
- **Semantic problems** — missing type definitions, missing function declarations, incorrect C++ member call syntax; the binary must actually be understood
- **The C++ object model** — the tool gets *what the thing is* wrong, which neither regexes nor stubs can rescue

---

## 5. Reproducing the comparison from the series

This repository ships no comparison scripts, but the four steps below are enough to reproduce the two sets of numbers on your own:

| Step | What | Measures |
|---|---|---|
| **Step 1** | Decompile | Produce the **raw artifact** (the C the decompiler emits directly) |
| **Step 2** | `gcc -c` the raw artifact | Measures **raw artifact quality** |
| **Step 3** | Source repair on the raw artifact | Add missing declarations, rewrite non-standard constructs, inject C++ class stubs; **bindec skips this step** |
| **Step 4** | `gcc -c` → `ld` → execute | Measures whether it is actually usable |

Example with `enum_basic`, running all three tools over 384 cells:

```bash
# 1) Record the original program's exit code as ground truth
./bin/enum_basic_x64_dyn ; echo "exit=$?"        # 20

# 2) Decompile with each of the three tools (commands differ per tool)
bindec-decompiler bin/enum_basic_x64_dyn -o out_bindec.c
# IDA / Ghidra likewise, each producing its own .c

# 3) Step 2 — compile the raw artifact directly; this pass rate is the "raw decompilation" column
gcc -c -w -O0 -no-pie out_ida.c -o out_ida.o     # IDA errors out on __fastcall

# 4) Step 3 — source repair (rewrite constructs, add declarations, inject C++ stubs); bindec skips this

# 5) Step 4 — recompile, link, execute; this gives the "after repair" column
gcc -c -w -O0 -no-pie out_ida_fixed.c -o out_ida_fixed.o
gcc -no-pie out_ida_fixed.o -o out_ida_fixed && ./out_ida_fixed ; echo "exit=$?"   # should be 20
```

Once this completes you have both sets of numbers from §1.1: **the pass rate before step 3 is "raw decompilation", the one after is "after repair".**

### Notes on compiling decompiler output

```bash
gcc -c -w -O0 -no-pie out.c -o out.o    # -w silences warnings, -O0 preserves behaviour, -no-pie matches the original binary
```

- **Do not use `-fpermissive`** — it swallows errors such as `int → pointer` and makes "does not compile" look like it compiles
- **Use `-c` rather than linking directly** — check whether it compiles first and whether it links second; the two failure modes have different causes
- **`-w` silences warnings, not errors** — `unknown type name 'Color'` is still an error
- **Compile flags must be identical across both stages** — otherwise the difference between "raw decompilation" and "after repair" will be contaminated by a flag change

---

## 6. Provenance

The test suite was written from scratch for this comparison and has no third-party source.

To reproduce the specific figures quoted in the series (88.3% / 44.5% / 34.4%, etc.), follow the protocol and tool versions stated in the series itself:

- Versions tested: bindec 1.0.1 / IDA Pro 9.1 / Ghidra 12.1.4
- The 384 decompilations come from **a single run**, not from figures stitched together across time
- Every percentage can be recomputed from the raw result data; none were entered by hand
