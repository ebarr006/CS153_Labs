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

char * kmalloc(void){
  char *mem;
  uint a;
  a = PGROUNDUP(myproc()->sz + PGSIZE);
  mem = kalloc();
  if(mem == 0){
     cprintf("kmalloc fail \n");
     return( (char *)0);
  }
  memset(mem, 0, PGSIZE);
  if(mappages(myproc()->pgdir,(char*)a, PGSIZE,V2P(mem),PTE_W|PTE_U) < 0){
     cprintf("kmalloc fail to map pages \n");
     kfree(mem);
     return ((char* )0);
  }

 // cprintf("mem: %d\n",*mem);
  return ((char*) V2P(mem)); 

}
//***********************************************************************
int shm_open(int id, char **pointer) {
   int i, index = 0;
   char * frame; 
   uint a;
   
  // initlock(&shm_table.lock),"SHM lock");
   acquire(&(shm_table.lock));
   //traverse the share memory page table 
   // 
   for(i = 0; i < 64; i++){
    	if(shm_table.shm_pages[i].id == id)
           goto located; 
        index++;
   }
   cprintf("case 2 \n");
   index = 0;
   for(i = 0; i < 64; i++){
       if(shm_table.shm_pages[i].refcnt == 0)
           break;
       index++;
   }
   shm_table.shm_pages[index].refcnt++;
   shm_table.shm_pages[index].id = id; 
   shm_table.shm_pages[index].frame = kmalloc();
   cprintf("id %d\n",id);
   *pointer = (char *)shm_table.shm_pages[index].frame;
  // cprintf("pointer %s\n", pointer);
   myproc()->sz+= PGSIZE;
   release(&(shm_table.lock));
   return id;
   located:
          cprintf("case 1\n");
	  a = PGROUNDUP(myproc()->sz + PGSIZE);
          frame = shm_table.shm_pages[index].frame;
          cprintf("a: %d  frame: %x\n",a,frame);
          if(mappages(myproc()->pgdir,(char *)a,PGSIZE,V2P(frame),PTE_W|PTE_U) < 0){
		cprintf("fail to map from exiting page");
		release(&(shm_table.lock));
		return (-1);
	  }
          shm_table.shm_pages[index].refcnt++;
 	  *pointer =(char*)frame;
          myproc()->sz += PGSIZE;
          release(&(shm_table.lock));
 	return  id;
         

   release(&(shm_table.lock));
   return 0; //added to remove compiler warning -- you should decide what to return
}


int shm_close(int id) {
//you write this too!
    for(int i = 0; i < 0; i++){
	if(shm_table.shm_pages[i].id == id){
	   shm_table.shm_pages[i].refcnt--;
	   if(shm_table.shm_pages[i].refcnt == 0){
		shm_table.shm_pages[i].id = 0; 
           }
           break;
       }
   }

    return 0; //added to remove compiler warning -- you should decide what to return
}
