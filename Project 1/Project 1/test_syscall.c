#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include<unistd.h>

#define __NR_helloworld 335

int main (int argc, char *argv[])
{
syscall (__NR_helloworld);
return 0;
}
