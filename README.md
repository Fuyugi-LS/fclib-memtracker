<div align="center">

# ✨ libmemtracker ✨
A robust, lightweight memory tracker in C.

<p>
    <img src="https://img.shields.io/badge/Norme-42_Compliant-blue?style=flat&logo=42" alt="Norminette Compliant">
    <img src="https://img.shields.io/badge/Valgrind-Clean-brightgreen?style=flat" alt="Valgrind Clean">
    <img src="https://img.shields.io/badge/Language-C-purple?style=flat" alt="Language C">
    <img src="https://img.shields.io/badge/License-MIT-lightblue?style=flat" alt="License MIT">
</p>

</div>

Tired of hunting down memory leaks? libmemtracker is a simple, norminette-compliant static library that wraps your memory allocations in a robust tracking system. It's designed to be lightweight, fast, and, most importantly, 100% leak-free.

This project provides a simple API to register, free, and manage allocated pointers, complete with robust error handling for edge cases like buffer overflows.

# 🔮 Core Features

- Leak-Proof: 100% clean reports from Valgrind.
- Norminette Compliant: Passes all norminette checks for clean, compliant C code.
- Lightweight & Fast: Designed with performance in mind, avoiding slow, redundant checks (like duplicate address verification).
- Granular Control: Includes functions to free all tracked pointers (mem_free_all) or only specific ones (mem_free_partial).
- Robust Error Handling: Built-in checks for buffer overflow (mem_perror) and invalid configuration (MAX_TRACKER size).

# Installation & Usage

1. Build the Library
A Makefile is included to compile all source files into a static library (.a file).
```
# Compile all .c files into .o files and archive them into the library
make
```
This will create libmemtracker.a in the root directory.

2. Link Against Your Project
When compiling your main program, link against the libmemtracker library.

# Example:

Compiling a test program named 'basic.c'
```
# -L. tells the compiler to look for libraries in the current directory
# -lmemtracker links the 'libmemtracker.a' library
cc -Wall -Wextra -Werror basic.c -L. -lmemtracker -o my_program
```
3. Use in Your Code
Include the memtracker.h header in your C files to use the tracker's functions.
```
/* basic.c */
#include "memtracker.h"
#include <stdlib.h>

int main(void)
{
    // Allocate memory
    void *ptr1 = malloc(100);
    void *ptr2 = malloc(200);

    // Register the pointers with the tracker
    // (2 pointers total)
    mem_register(2, ptr1, ptr2);

    // ... do work with your pointers ...

    // Clean up everything at the end
    mem_free_all();
    return (0);
}
```

# LICENSE

MIT License. For detailed informations, read LICENSE.md