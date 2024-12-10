#include <linux/kernel.h>
#include<linux/syscalls.h>


SYSCALL_DEFINE0(helloworld)
{
	printk(KERN_EMERG "Hello World !\n");
	return 1;


}

