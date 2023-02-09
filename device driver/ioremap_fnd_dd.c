
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define DEV_NAME "/dev/iom_fnd"
#define IOM_FND_MAJOR_NUM 241
#define IOM_FND_ADDRESS 0xA8000200

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HGU");

int iom_fnd_init(void);
void iom_fnd_exit(void);
module_init(iom_fnd_init);
module_exit(iom_fnd_exit);

static int fndport_usage = 0;
static unsigned char *iom_fnd_addr;

int major_num = 0;

int iom_fnd_open (struct inode *, struct file *);
int iom_fnd_release (struct inode *, struct file *);
ssize_t iom_fnd_write (struct file *, const char __user *, size_t, loff_t *);


struct file_operations iom_fnd_fops = {
	.open = iom_fnd_open,
	.release = iom_fnd_release,
	.write = iom_fnd_write,
};

int iom_fnd_open (struct inode *inode, struct file *filep)
{
	if (fndport_usage != 0)
		return -EBUSY;
	fndport_usage = 1;	

	return 0;
}

int iom_fnd_release (struct inode *inode, struct file *filep)
{

	fndport_usage = 0;
	return 0;
}


ssize_t iom_fnd_write (struct file *filep, const char __user *buf, size_t count, loff_t *f_ops)
{
	unsigned char led_data;

	if(copy_from_user(&led_data, buf, count))
		return -EFAULT;
	outb(led_data, (unsigned int) iom_fnd_addr);
	return count;
}


int __init iom_fnd_init(void)
{
	major_num = register_chrdev(IOM_FND_MAJOR_NUM, DEV_NAME, &iom_fnd_fops);

	//error check
	if(major_num < 0){
		printk(KERN_WARNING"%s: can't get or assign major number. %d\n", DEV_NAME, IOM_FND_MAJOR_NUM);
		return major_num;
	}
	printk("Success to load the device %s. Major number is %d \n", DEV_NAME, IOM_FND_MAJOR_NUM);

	iom_fnd_addr = ioremap(IOM_FND_ADDRESS, 0x2);
	
	return 0;
}


void __exit iom_fnd_exit(void)
{
	iounmap(iom_fnd_addr);

	unregister_chrdev(IOM_FND_MAJOR_NUM, DEV_NAME);
	printk("Success to unload the device %s...\n", DEV_NAME);
}
