#include <linux/unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#define __NR_vma_props 342

int main(int argc, char argv[])
{
	int PID;
	unsigned long Adress;
	
	printf("Type a Process ID:\n");
	scanf("%d", &PID);
	
	printf("Type a Memory Address:\n");
	scanf("%1d", &Address);
	
	syscall(__NR_vma_props, Address, PID);
	
	return 0;
	
}