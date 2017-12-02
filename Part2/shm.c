#include "param.h"
#include "types.h"
#include "defs.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct shm_page {
    uint id;
    char *frame;
    int refcnt;
  } shm_pages[64];
} shm_table;

void shminit() {
  int i;
  initlock(&(shm_table.lock), "SHM lock");
  acquire(&(shm_table.lock));
  for (i = 0; i< 64; i++) {
    shm_table.shm_pages[i].id =0;
    shm_table.shm_pages[i].frame =0;
    shm_table.shm_pages[i].refcnt =0;
  }
  release(&(shm_table.lock));
}

int shm_open(int id, char **pointer) {
   int i, index = 0;
   char * frame; 
   
   //initlock(&shm_table.lock),"SHM lock");
   acquire(&(shm_table.lock));
   //traverse the share memory page table 
   // loo 
   for(i = 0; i < 64; i++){
    	if(shm_table.shm_pages[i].id == id)
           goto located; 
        index++;
   }

   index = 0;
   for(i = 0; i < 64; i++){
       if(shm_table.shm_pages[i].refcnt == 0)
           break;
       index++;
   }
   shm_table.shm_pages[index].refcnt++;
   shm_table.shm_pages[index].id = id; 
   shm_table.shm_pages[index].frame = kalloc();
   *pointer = (char *)shm_table.shm_pages[index].frame;
   
   release(&(shm_table.lock));
   return id;
   located:
	  frame = shm_table.shm_pages[index].frame;
          if(mappages(myproc()->pgdir,(char *)myproc()->sz,PGSIZE,V2P(frame),PTE_W|PTE_U) < 0){
		cprintf("fail to map from exiting page");
		release(&(shm_table.lock));
		return (-1);
	  }
          shm_table.shm_pages[index].refcnt++;
 	  *pointer =(char*)frame;
          myproc()->sz += PGSIZE;
          release(&(shm_table.lock));
 	return  id;

   return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!




return 0; //added to remove compiler warning -- you should decide what to return
}
