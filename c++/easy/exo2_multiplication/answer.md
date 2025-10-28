# Performance Comparison Between `endl` and `"\n"` in C++

## Overview

The program takes approximately **20 times less time** to execute when using `"\n"` instead of `endl`.

This performance difference is caused by the way `endl` works in C++.  
While both `endl` and `"\n"` insert a newline character, `endl` also **flushes the output buffer** each time it is called.  

Flushing forces the program to immediately write all buffered data to the output file or console.  
When this happens repeatedly (for example, 100,000 times in a loop), it causes a significant performance slowdown because disk writes are much slower than writing to memory.

In contrast, `"\n"` simply adds a newline character **without forcing a flush**.  
This allows the system to buffer many writes and perform them in larger chunks, which is **much more efficient**.

---

## Summary Table

| Method | Behavior | Performance |
|---------|-----------|-------------|
| `endl` | Inserts newline **and flushes the buffer** each time | ❌ Much slower |
| `"\n"` | Inserts newline only; buffer flushed automatically later | ✅ Much faster |

---

## Conclusion

Using `endl` is appropriate when immediate output is required — for example, when printing interactive messages or debugging information.  
However, for writing large amounts of data to a file, such as generating 100,000 lines of output, it is **much more efficient to use `"\n"`** instead of `endl`.

---
