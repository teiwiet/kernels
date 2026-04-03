#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

static struct kprobe kp;

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
#ifdef CONFIG_X86_64
    const char __user *filename = (const char __user *)regs->si;
    printk(KERN_INFO "[open_hook] file opened: %s\n", filename);
#endif
    return 0;
}

static int __init hook_init(void)
{
    kp.symbol_name = "__x64_sys_openat";  // kernel 64-bit
    kp.pre_handler = handler_pre;

    if (register_kprobe(&kp) < 0) {
        printk(KERN_ERR "register_kprobe failed\n");
        return -1;
    }

    printk(KERN_INFO "kprobe registered\n");
    return 0;
}

static void __exit hook_exit(void)
{
    unregister_kprobe(&kp);
    printk(KERN_INFO "kprobe unregistered\n");
}

module_init(hook_init);
module_exit(hook_exit);

MODULE_LICENSE("GPL");
