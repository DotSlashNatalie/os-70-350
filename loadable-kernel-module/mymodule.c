// http://www.tldp.org/LDP/lkmpg/2.6/html/hello2.html

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int simple_init(void)
{
	printk(KERN_INFO, "Loading Module\n");
	
	return 0;
}

void simple_exit(void)
{
	printk(KERN_INFO, "Removing Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("LICENSE");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Your Name");