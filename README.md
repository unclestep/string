# string

A complete reimplementation of the `<string.h>` library, alongside advanced `sprintf` and `sscanf` functionality. This project was developed as part of the **School 21** curriculum, emphasizing low-level memory management, algorithmic accuracy, and cross-platform consistency.

## 🚀 Key Features

- **Full `<string.h>` Logic**: Implementation of all 15+ base functions (`memchr`, `strcat`, `strtoken`, etc.).
- **Advanced `sprintf`**: Complete implementation supporting all flags, widths, precisions, and length modifiers.
- **Own Arbitrary-Precision Arithmetic Library**: Built a mini version of `gmp.h` library from scratch to handle high-precision floating-point conversions.
- **Robust Testing**: Comprehensive unit tests with `check.h` and memory leak audits using `valgrind`.
- **Multi-Arch Support**: Docker environments for testing on both Ubuntu and Alpine (`musl` vs `glibc`).

## 🛠 Project Components

### 1. Standard Functions (`std/`)
The library provides all standard processing utilities such as `strlen`, `strcpy`, `strerror`, and `strtok`.

### 2. The `sprintf` Powerhouse
The `sprintf` implementation is the centerpiece of this project. It is designed to match the behavior described on [cppreference](https://en.cppreference.com/w/c/io/fprintf) exactly.
- **Specifiers Supported**: `c`, `d`, `i`, `f`, `s`, `u`, `o`, `x`, `X`, `p`, `n`, `e`, `E`, `g`, `G`.
- **Flags**: `-`, `+`, `(space)`, `#`, `0`.
- **Width & Precision**: Supports dynamic values via `*`.
- **Length Modifiers**: `h`, `l`, `L`.

### 3. Custom Mini-GMP Library (`gmp/`)
Standard `double` or `long double` types in C suffer from precision loss when converting to strings. To achieve exact output parity with the native `sprintf`, I implemented an own arbitrary-precision arithmetic library:
- **Arithmetic**: Precision-accurate addition, subtraction, multiplication, and division for arbitrarily large numbers.
- **Float Conversion**: Implemented the `mpf_t` (floating point) structure to handle mantissas and exponents separately.
- **Rounding**: Precise implementation of "Round to Even" (Banker's rounding) used by standard libraries.
- **Scientific Notation**: Dedicated logic for scientific formatting (`%e`, `%g`) to ensure the correct exponent sign and digit count.

### 4. The `sscanf` Module
The `sscanf` implementation was developed by a teammate. This module is fully compliant with the C standard and handles all scenarios documented on [cppreference](https://en.cppreference.com/w/c/io/fscanf.html).

### 5. Special String Processing (`bonus/`)
Inspired by C#, I included specialized utility functions:
- `to_upper` / `to_lower`: Case transformation.
- `insert`: Inserting a string into another at a specific index with memory reallocation.
- `trim`: Removing specific character sets from the start and end of a string.

## 🏗 Quality Assurance & Architecture

### Multi-Platform Consistency
The library was tested using Docker to ensure behavior is identical across different environments besides native macOS:
- **Ubuntu 24.04 (`glibc`)**: Standard Linux environment.
- **Alpine Linux (`musl`)**: To verify compatibility with lightweight `libc` implementations.
- **Multi-arch script**: `multiarch_test.sh` automates checks across different OSs.

### Memory & Testing
- **Unit Testing**: 300+ test cases using the `check.h` framework covering all edge cases, including `NaN`, `Inf`, and extreme values.
- **Memory Safety**: Verified via `valgrind` to ensure zero memory leaks and no invalid read/writes.
- **Coverage**: `gcov` reports generated to ensure every line of logic is exercised.

## 🛠 Building the Project

The project is managed via a `Makefile` with the following targets:
- `make all`: Builds the `s21_string.a` static library.
- `make test`: Runs the full test suite using the `check.h` library.
- `make gcov_report`: Generates an HTML coverage report.
- `make clang`: Formats code according to Google Style.
- `make valgrind`: Runs tests under memory leak detection.

```bash
git clone <repository_url>
cd src
make test
```
