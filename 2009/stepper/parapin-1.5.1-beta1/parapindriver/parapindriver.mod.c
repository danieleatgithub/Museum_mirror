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
	{ 0xbb3706f0, "register_chrdev" },
	{ 0x9ef749e2, "unregister_chrdev" },
	{ 0xecadb480, "set_pin" },
	{ 0x2e23d71d, "pin_output_mode" },
	{ 0xe26514b4, "clear_pin" },
	{ 0x98c9fb02, "pin_is_set" },
	{ 0xb16426cf, "pin_input_mode" },
	{ 0x1b7d4074, "printk" },
	{ 0xf31adff2, "pin_init_kernel" },
	{ 0x3d20b1a0, "pin_release" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=kparapin";


MODULE_INFO(srcversion, "D608D9C2CC2687CDCFB77F4");
