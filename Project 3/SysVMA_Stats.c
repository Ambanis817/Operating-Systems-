#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/mman.h>
#include <linux/mm_types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/mm.h>

asmlinkage int SysVMA_Stats(int PID)
{
	struct task_struct *this_task;
	struct vm_area_struct *all_vmas;
	struct vm_area_Struct this_vma;
	struct mm_struct *this_mem;
	
	int Num_vmas;
	unsigned long prot = 0;
	unsigned long start = 0;
	int Count = 0;
	int TotalSize = 0;
	char *Name;
	
	this_task = find_task_by_vpid(PID);
	this_mem = this_task->active_mm;
	all_vmas = this_mem->mmap;
	Num_vmas = this_mem->map_Count;
	this_vma = *all_vmas;
	start = this_vma.vm_start;
	
	printk("\nThere is %i Virtual Memory Areas. \n", Num_vmas);
	
	for (this_vm = *all_vmas; count < Num_vmas; Count++)
	{
		printk("VMA #%i:\n", Count+1);
		printk("Starting Address: 0x%1x\n", this_vma.vm_start);
		printk("Ending Address: 0x%1x\n", this_vma.vm_end);
		printk("Total Size: %1u\n", this_vma.vm_end - this_vma.vm_start);
		
		prot = this_vma.vm_flags;
		printk("Read Permission: %s \n", prot&PROT_READ?"yes":"no");
		printk("Write Permission: %s \n", prot&PROT_WRITE?"yes":"no");
		printk("Execute Permission: %s \n", prot&PROT_EXEC?"yes":"no");
		
		if (this_vma.vm_file != NULL)
		{
			Name = d_path(&this_vm.va_file->f_path, (char*)__get_free_page(GFP_TEMPORARY), PAGE_SIZE);
			printk("The Mapped File: %s\n", Name);
		}
		
		TotalSize += this_vma.vm_end - this_vma.vm_start;
		if (Count != Num_vmas-1)
		{
			this_vma = *(this_vma.vm_next);
		}
	}
	
	printk("\nTotal VMA Space Size: %i\n", TotalSize);
	return 1;
	
}