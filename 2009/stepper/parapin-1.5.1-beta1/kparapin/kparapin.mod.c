#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x91dff6c7, "struct_module" },
	{ 0x3ce4ca6f, "disable_irq" },
	{ 0xe8788c17, "parport_put_port" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x88bff696, "parport_find_number" },
	{ 0x1b7d4074, "printk" },
	{ 0x3873de02, "parport_unregister_device" },
	{ 0xb65b373d, "parport_claim" },
	{ 0x79c52c33, "parport_release" },
	{ 0x30f63b25, "parport_register_device" },
	{ 0xfcec0987, "enable_irq" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=parport";


MODULE_INFO(srcversion, "D3E7F6BE4056763A804423C");
