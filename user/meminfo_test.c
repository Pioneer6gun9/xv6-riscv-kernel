#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    struct meminfo_t info;

    if (meminfo(&info) < 0) {
        printf("Failed to get memory info\n");
        exit(1);
    }

    printf("Code Segment: 0x%lx - 0x%lx\n", (unsigned long)info.start_code, (unsigned long)info.end_code);
    printf("Data Segment: 0x%lx - 0x%lx\n", (unsigned long)info.start_data, (unsigned long)info.end_data);
    printf("Heap Start: 0x%lx\n", (unsigned long)info.start_brk);
    printf("Stack Top: 0x%lx\n", (unsigned long)info.stack_top);

    exit(0);
}
