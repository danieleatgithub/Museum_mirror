#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x91dff6c7, "struct_module" },
	{ 0xf2afa595, "param_get_charp" },
	{ 0x8785725d, "param_set_charp" },
	{ 0x4550372e, "pin_release" },
	{ 0xf31adff2, "pin_init_kernel" },
	{ 0xbb3706f0, "register_chrdev" },
	{ 0x9ef749e2, "unregister_chrdev" },
	{ 0xb7eda461, "set_pin" },
	{ 0x572a2f47, "pin_output_mode" },
	{ 0xe14695af, "clear_pin" },
	{ 0x1b7d4074, "printk" },
	{ 0xd98a7ef2, "pin_is_set" },
	{ 0x8d0474c7, "pin_input_mode" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=kparapin";


MODULE_INFO(srcversion, "A8C6B9E25DBAB78AC1F2BA9");
