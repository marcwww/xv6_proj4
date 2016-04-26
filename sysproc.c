#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern int free_frame_cnt; // NUAA OS: for mem proj
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
int sys_shutdown(void)
{
  outw(0xB004, 0x0|0x2000);

  return 0;
}
int sys_print_free_frame_cnt(void)
{  
	//uint i;
	//pte_t *pte;
 
    cprintf("free-frames %d\n", free_frame_cnt);
  /*
	 if(strncmp( proc->name,"lpatest",sizeof(proc->name)/sizeof(char))==0)
	  {
		  cprintf("sz=0x%x\n",proc->sz+4096*2048);
		  for(i = 0; i < proc->sz+4096*2048; i += PGSIZE){
			if((pte = walkpgdir(proc->pgdir, (void *) i, 0)) == 0)
			{
				cprintf("1 sz=0x%x\n",i);
				panic("copyuvm: pte should exist");
			}
			if(!(*pte & PTE_P))
			{
				cprintf("2 sz=0x%x\n",i);
				continue;
				return 0;
				panic("copyuvm: page not present");
			}
		   }
	  }
	 */
	
	return 0;
}


int
sys_set_page_allocator(void)
{
	int n;
	if(argint(0, &n) < 0)
	    return -1;

	set_page_allocator(n);
	return 0;
}

