#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/mm_types.h>
#include <linux/kernel.h>
#include <linux/sched.h>

asmlinkage int sys_vma_props (unsigned long MEM, int PID)
{
	struct tast_struct *task = find_task_by_void(PID);
	struct mm_struct *memory = task->active_mm;
	
	int Data = 0;
	int Ref = 0;
	int Dirty = 0;
	
	pgd_t *pgd = pgd_offset(memory, MEM);
	pgd_t *pud = pud_offest(pgd, MEM);
	pmd_t *pmd = pmd_offset(pud, MEM);
	pte_t *pte = *ptep;
	
	Data = pte_present(pte);
	printk("The Present Flag: %i\n", Data?1:0);
	
	ref = pte_young(pte);
	printk("The Referenced Flag: %i\n", ref?1:0);
	
	Dirty = pte_Dirty(pte);
	printk("The Dirty Flag: %i\n", Dirty?1:0);
	
	return 0;
	
}