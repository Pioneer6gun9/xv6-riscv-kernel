# **XV6 RISC-V: `meminfo` 系统调用 & 动态内存监控**
---

## **📌 项目简介**
本项目扩展了 **XV6 RISC-V** 操作系统，新增 **`meminfo` 系统调用**，用于获取当前进程的内存布局信息，包括：
- **代码段（Code Segment）**
- **数据段（Data Segment）**
- **堆（Heap）**
- **栈（Stack）**

此外，还开发了 **`mem_monitor` 用户态程序**，支持 **实时监控进程内存**，并允许用户通过 `sbrk()` 触发动态内存变化。

---

## **📌 主要功能**
### **✅ `meminfo` 系统调用**
- 提供进程的 **代码段、数据段、堆、栈** 地址信息。
- 通过 `copyout()` 传递数据到用户态。

### **✅ `mem_monitor` 动态内存监控**
- 定期调用 `meminfo` 并显示进程的内存状态。
- **交互模式**：按 `a` 触发 `sbrk(0x1000)` 申请一页内存，模拟进程增长。

示例输出：
```
Code: 0x80000000 - 0x80000698 | Data: 0x3000 - 0x4000 | Heap: 0x5000 | Stack: 0x3FFFFF9000
Press 'a' to allocate memory, or Enter to continue:
Allocated one page at 0x6000
```

---

## **📌 编译 & 运行**
### **🔹 重新编译内核**
```sh
make clean
make
make qemu
```
### **🔹 运行 `mem_monitor`**
```sh
mem_monitor
```
---

