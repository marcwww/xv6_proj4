/*
  * Project 4: lazy page allocation test
  */

#include "types.h"
#include "user.h"


extern void set_page_allocator(int allocator);

  
void usage(void)
{
    printf(1, "Usage: lpatest 0|1 \n"
              "\t0: Default page allocator \n"
              "\t1: Lazy page allocator \n");
}
  
int
main(int argc, char *argv[])
{
    int a = 0;
    int size = 0;
    char * addr = (void *)0;
    char * cur_break = (void *)0;
    char * old_break = (void *)0;

    if (argc < 2)
    {
        usage();
        exit();
    }

    if (argv[1][0] == '0')
    {
        a = 0;
        printf(1, "\nUsing the DEFAULT page allocator ...\n");
    }
    else
    {
        a = 1;
        printf(1, "\nUsing the LAZY page allocator ...\n");
    }  

    set_page_allocator(a);

    //=========================
    size = 10;
    printf(1, "\n=========== TEST 1: sbrk(%d) ===========\n");
    cur_break = sbrk(0);
    printf(1, "Before sbrk(%d), break 0x%x ", size, cur_break);
    print_free_frame_cnt();
    printf(1, "Calling sbrk(%d) ... \n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After sbrk(%d), break 0x%x ", size, cur_break);
    print_free_frame_cnt();


    printf(1, "\n=========== TEST 2: writing valid bytes ===========\n");
    cur_break = sbrk(0);
    printf(1, "Before the write, break 0x%x ", cur_break);
    print_free_frame_cnt();
    addr = cur_break-1;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();

    printf(1, "\nBefore the write, ");
    print_free_frame_cnt();
    addr = cur_break -  2;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();


    printf(1, "\n=========== TEST 3: sbrk(+) --> sbrk(-) --> write ===========\n");
    cur_break = sbrk(0);
    printf(1, "Before the sbrk(+), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = 0x10;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(+), break 0x%x ", cur_break);
    print_free_frame_cnt();

    cur_break = sbrk(0);
    printf(1, "\nBefore the sbrk(-), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = -1;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(-), break 0x%x ", cur_break);
    print_free_frame_cnt();

    printf(1, "\nBefore the write, ");
    print_free_frame_cnt();
    addr = cur_break-1;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();


    printf(1, "\n==========="
              "TEST 4: sbrk(3 pages) --> "
              "write in 1st/2nd pages --> "
              "sbrk(-1 page) --> "
              "sbrk(-1 page) --> "
              "sbrk(-1 page)"
              "===========\n");
    cur_break = sbrk(0);
    old_break = cur_break;
    printf(1, "Before the sbrk(3 pages), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = 4096 * 3;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(3 pages), break 0x%x ", cur_break);
    print_free_frame_cnt();

    printf(1, "\nBefore the write (in 2st page), ");
    print_free_frame_cnt();
    addr = old_break -1+ 4096*2;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();

    printf(1, "\nBefore the write (in 1st page), ");
    print_free_frame_cnt();
    addr = old_break -1+  4096;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, ");
    print_free_frame_cnt();

    cur_break = sbrk(0);
    old_break = cur_break;
    printf(1, "\nBefore the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = -4096;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();

    cur_break = sbrk(0);
    old_break = cur_break;
    printf(1, "\nBefore the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = -4096;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();

    cur_break = sbrk(0);
    old_break = cur_break;
    printf(1, "\nBefore the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();
    size = -4096;
    printf(1, "Calling sbrk(%d) ...\n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After the sbrk(-1 page), break 0x%x ", cur_break);
    print_free_frame_cnt();


    printf(1, "\n=========== TEST 5: allocating too much memory ===========\n");
    size = 0x7FFFFFFF;
    cur_break = sbrk(0);
    printf(1, "Before sbrk(0x%x), break 0x%x ", size, cur_break);
    print_free_frame_cnt();
    printf(1, "Calling sbrk(0x%x) ... \n", size);
    sbrk(size);
    cur_break = sbrk(0);
    printf(1, "After sbrk(0x%x), break 0x%x ", size, cur_break);
    print_free_frame_cnt();

    printf(1,"\n=============TEST 6: fork()=========\n");
    printf(1,"Before sbrk(1024 pages),");
    print_free_frame_cnt();
    sbrk(4096*1024);
    printf(1,"After sbrk(1024 pages),");
    print_free_frame_cnt();
    *(sbrk(0)-1)=1;
    printf(1,"After write a byte at the last page, ");
    print_free_frame_cnt();
    if(fork()==0){//child
      printf(1,"fork() success\n");
      sbrk(-4096*1024);
      exit();
    }else{
      wait();
    }
    sbrk(-4096*1024);

    printf(1, "\n=========== TEST 7: writing in unallocated page ===========\n");
    cur_break = sbrk(0);
    printf(1, "Before the write, break 0x%x ", cur_break);
    print_free_frame_cnt();
    addr = cur_break-1 + 4096;
    printf(1, "Writing byte 0x%x ...\n", addr);
    *addr = 1;
    printf(1, "After the write, "); // shouldn't reach here
    print_free_frame_cnt(); // shouldn't reach here

    printf(1, "\n");
    //=========================
    
    exit();
}

