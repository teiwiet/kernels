#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x8c16b828, "i2c_register_driver" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xafd1a6b9, "i2c_transfer_buffer_flags" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x92997ed8, "_printk" },
	{ 0xf9a482f9, "msleep" },
	{ 0x5141c1c5, "i2c_del_driver" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E7D8BAF5C707101100EF28A");
