#include "user/user.h"
#include "kernel/fcntl.h"   

int main() {
    struct meminfo_t info;
    char *allocated[100];  // 用于保存 sbrk 返回的内存指针
    int alloc_index = 0;
    char input[16];        // 用于读取用户输入

    while (1) {
        // 获取进程内存信息
        if (meminfo(&info) < 0) {
            printf("meminfo failed!\n");
            exit(1);
        }

        // 在屏幕上打印内存信息
        printf("Code: %p - %p | Data: %p - %p | Heap: %p | Stack: %p\n",
               (void*)info.start_code, (void*)info.end_code,
               (void*)info.start_data, (void*)info.end_data,
               (void*)info.start_brk, (void*)info.stack_top);

        // 提示用户输入以模拟外部变化
        printf("Press 'a' then Enter to allocate one page, or just Enter to continue: ");
        gets(input, sizeof(input));

        // 如果用户输入 'a'，则调用 sbrk(0x1000) 申请一页内存
        if (input[0] == 'a') {
            char *p = sbrk(0x1000);
            if (p == (void*)-1) {
                printf("sbrk failed!\n");
            } else {
                allocated[alloc_index++] = p;
                printf("Allocated one page at %p\n", p);
            }
        }
        sleep(1);

        // 使用 allocated 变量以避免未使用警告
        (void)allocated;
    }

    exit(0);
}
