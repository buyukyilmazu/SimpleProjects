#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/pid.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/capability.h>
asmlinkage long set_casper(pid_t pid, int value){
	if(value>3 || value<0)
		return -EPERM;
	if(capable(CAP_SYS_ADMIN)){				// if process having root privilege
	struct task_struct *a;
    	 a=find_task_by_vpid(pid);
	 a->casper = value;
	return a->casper;
	}else{
		return -EPERM;						//if proccess having user privilege
	}
	}
