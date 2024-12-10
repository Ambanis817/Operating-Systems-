#include <linux/unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define __NR_vma_stats 341

int main(int argc, char *argv[])
{
	int PID;
	printf("Type A Process ID: \n");
	scanf("%d", &PID);
	
	syscall(__NR_vma_stats, PID);
	
	return 0;
	
}