#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// 系统调用：获取进程的内存信息
uint64 sys_meminfo(void) {
  struct proc *p = myproc();  // 获取当前进程
  struct meminfo_t meminfo;
  uint64 user_addr;

  // 获取用户传入的指针地址
  argaddr(0, &user_addr);
  if (user_addr == 0) {
    return -1; 
  }

  // 获取进程的内存信息
  meminfo.start_code = 0x80000000;  // 代码段起始地址（固定）
  meminfo.end_code = p->trapframe->epc;  // 代码段结束地址
  meminfo.start_data = PGROUNDUP(p->sz / 2);  // 数据段起始地址
  meminfo.end_data = meminfo.start_data + 0x1000;  
  meminfo.start_brk = p->sz;  // 堆起始地址
  meminfo.stack_top = p->kstack;  // 栈顶地址

  // 将数据拷贝到用户空间
  if (copyout(p->pagetable, user_addr, (char *)&meminfo, sizeof(meminfo)) < 0) {
    return -1; 
  }

  return 0;
}
