#include <linux/module.h>
#include <linux/kernel.h>

int __init mod_hello_init(void)
{
	pr_info("LOADED\n");
	return 0;
}

void __exit mod_hello_cleanup(void)
{
	pr_info("UNLOADED\n");
}

module_init(mod_hello_init);
module_exit(mod_hello_cleanup);
MODULE_LICENSE("GPLv2");
MODULE_DESCRIPTION("desc");
