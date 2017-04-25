//netfilter_firewall
//cute eleven 2014-7-20

#include <linux/module.h>  
#include <linux/ioctl.h>  
#include <linux/wait.h> 
#include <linux/poll.h> 
#include <linux/device.h>
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/errno.h>  
#include <linux/mm.h>  
#include <linux/sched.h>  
#include <linux/init.h>  
#include <linux/cdev.h>
#include <linux/in.h>   
#include <linux/ip.h>   
#include <linux/tcp.h>   
#include <linux/icmp.h>   
#include <linux/netdevice.h>   
#include <linux/netfilter.h>   
#include <linux/netfilter_ipv4.h>   
#include <asm/io.h>  
#include <asm/system.h>  
#include <asm/uaccess.h>

#define CE_FW_DEV_IOC_MAGIC  'k'
#define FW_DEV_IOC_REF_DENY_IP        _IO(CE_FW_DEV_IOC_MAGIC,1)
#define FW_DEV_IOC_REF_DENY_PORT        _IO(CE_FW_DEV_IOC_MAGIC,2)
#define FW_DEV_IOC_ADD_DENY_IP  _IOW(CE_FW_DEV_IOC_MAGIC,3,unsigned int)
#define FW_DEV_IOC_ADD_DENY_PORT  _IOW(CE_FW_DEV_IOC_MAGIC,4,short)

static int ce_fw_major;
struct cdev cdev;
struct ce_fw_dev *ce_fw_devp;  /*设备结构指针*/ 
dev_t devno;
unsigned int kernel_deny_ip[10];
unsigned short kernel_deny_port[10];

struct ce_fw_dev  //定义设备文件结构体
{  
    char *data;  
    unsigned long size;  
};

//定义netfilter钩子函数 五个不可改变的字符型数组指针
const char* hooks[] ={ "NF_IP_PRE_ROUTING",           //路由前钩子
                             "NF_IP_LOCAL_IN",         //进本地钩子
                             "NF_IP_FORWARD",          //发出钩子
                             "NF_IP_LOCAL_OUT",        //本地出钩子
                             "NF_IP_POST_ROUTING"};    //路由后钩子

//ip过滤函数
unsigned int ip_filter(struct iphdr *iph)
{
	int i;	
	for(i=0;i<10;i++)
	{
		if(kernel_deny_ip[i] == 0)
		{
			continue;
		}
		else
		{
			if((kernel_deny_ip[i] == iph->saddr)||(kernel_deny_ip[i] == iph->daddr)) //无符号整型判断
			{
				return NF_DROP;
			}
		}
	}
	return NF_ACCEPT;
	 
}

//TCP过滤函数
unsigned int tcp_filter(struct tcphdr *th)
{
	int i;
	for(i=0;i<10;i++)
	{
		if(kernel_deny_port[i] == 0)
		{
			continue;
		}
		else
		{
			if((kernel_deny_port[i] == th->source)||(kernel_deny_port[i] == th->dest)) //无符号短整型判断
			{
				return NF_DROP;
			}
		}
	}
	return NF_ACCEPT;
}


// hook函数
unsigned int packet_filter(unsigned int hooknum,
			       struct sk_buff **skb,
			       const struct net_device *in,
			       const struct net_device *out,
			       int (*okfn)(struct sk_buff *))  //各种要导入的数据格式参数
{
	struct sk_buff* nskb;  //定义socket缓冲数据结构指针
	struct iphdr *iph = NULL;	//定义IP报头数据结构指针 初始值为NULL
	struct tcphdr *th = NULL;  //定义TCP报头数据结构指针 初始值为NULL
	
	nskb = *skb;//提取socket报头
	if(nskb==NULL)  //判断socket是否存在
		return NF_ACCEPT; //不存在则放行

	iph = nskb->nh.iph; //提取IP报头
	if(iph == NULL)    //判断IP报头是否存在
		return NF_ACCEPT;  //不存在则放行
	else
		return ip_filter(iph); //调用ip地址过滤函数判断
		
	th = nskb->h.th;  //提取TCP报头
	if(iph == NULL)  //判断TCP报头是否存在
		return NF_ACCEPT;  //不存在则放行
	else
		return tcp_filter(th); //调用ip地址过滤函数判断
		
	return NF_ACCEPT; //满足以上所有规则 放行
}

 //控制钩子位置 暂时就截取进出本地的
static struct nf_hook_ops packet_filter_opt[] = {
        {
                .hook                = packet_filter,
                .owner                = THIS_MODULE,
                .pf                = PF_INET,
                .hooknum        = NF_IP_PRE_ROUTING,
                .priority = NF_IP_PRI_FIRST,
        },
        {
                .hook                = packet_filter,
                .owner                = THIS_MODULE,
                .pf                = PF_INET,
                .hooknum        = NF_IP_LOCAL_IN,
                .priority = NF_IP_PRI_FIRST,
        },
        {
                .hook                = packet_filter,
                .owner                = THIS_MODULE,
                .pf                = PF_INET,
                .hooknum        = NF_IP_FORWARD,
                .priority = NF_IP_PRI_FIRST,
        },
        {
                .hook                = packet_filter,
                .owner                = THIS_MODULE,
                .pf                = PF_INET,
                .hooknum        = NF_IP_LOCAL_OUT,
                .priority = NF_IP_PRI_FIRST,
        },
        {
                .hook                = packet_filter,
                .owner                = THIS_MODULE,
                .pf                = PF_INET,
                .hooknum        = NF_IP_PRE_ROUTING,
                .priority = NF_IP_POST_ROUTING,
        },
};


//设备打开
int ce_fw_open(struct inode *inode,struct file *filp)
{ 
			printk("ce_fw_open---------------------ok\n");
	return 0;
}  

//设备释放
int ce_fw_release(struct inode *inode,struct file *filp)  
{  
			printk("ce_fw_release------------------ok\n");
    return 0;  
}  

//设备控制
int  ce_fw_ioctl(struct inode *inode,struct file *filp,
					unsigned int cmd,unsigned long arg)
{
	int ret =0;
	int i;
	unsigned int ip_ioarg =0;
	unsigned short tcp_ioarg =0;
	
	switch(cmd)  //设备控制命令集
	{
		/*获取参数*/
		case FW_DEV_IOC_REF_DENY_IP:  //通过设备清除所有IP地址条目
			for(i=0;i<10;i++)
			{
				kernel_deny_ip[i] =0;
			}
			printk("FW_DEV_IOC_REF_DENY_IP---------ok\n");
			break;
			
		case FW_DEV_IOC_ADD_DENY_IP:  //通过设备添加IP地址条目 
			ret =__get_user(ip_ioarg,(unsigned int *)arg); 
			//数据来自用户程序定义变量 user_add_deny_ip 转为指针
			for(i=0;i<10;i++)
			{
				if(kernel_deny_ip[i] == 0)
				{
					kernel_deny_ip[i] = ip_ioarg;
					break;
				}
			}
			printk("FW_DEV_IOC_ADD_DENY_IP---------ok\n");
			break;
		
		case FW_DEV_IOC_REF_DENY_PORT:  //通过设备清除所有IP地址条目
			for(i=0;i<10;i++)
			{
				kernel_deny_port[i] =0;
			}
			printk("FW_DEV_IOC_REF_DENY_PORT-------ok\n");
			break;
		
		case FW_DEV_IOC_ADD_DENY_PORT:  //通过设备添加TCP地址条目
			ret =__get_user(tcp_ioarg,(unsigned short *)arg);
			//数据来自用户程序定义变量 user_add_deny_tcp 转为指针
			for(i=0;i<10;i++)
			{
				if(kernel_deny_port[i] == 0)
				{
					kernel_deny_port[i] = tcp_ioarg;
					break;
				}
			}
			printk("FW_DEV_IOC_ADD_DENY_PORT-------ok\n");
			break;
			
		default:
			return 0;
	}
	return 0;
}


static const struct file_operations ce_fw_fops =  
{  
    .owner = THIS_MODULE,  
    .llseek = NULL,  
    .read = NULL,  
    .write = NULL,  
    .open = ce_fw_open,  
    .release = ce_fw_release,  
    .ioctl = ce_fw_ioctl,
};  





//设备初始化和钩子注册
static int ce_fw_init(void)
{
	int result;
	result = alloc_chrdev_region(&devno,0,1,"ce_fw_dev");	
	ce_fw_major = MAJOR(devno); 
	
    if(result < 0)
        return result; 
	
    cdev_init(&cdev,&ce_fw_fops);  
    cdev.owner = THIS_MODULE;  
    cdev.ops = &ce_fw_fops;   
	           
    cdev_add(&cdev,devno,1); 
	ce_fw_devp = kmalloc(sizeof(struct ce_fw_dev),GFP_KERNEL);	
	memset(ce_fw_devp,0,sizeof(struct ce_fw_dev));
	nf_register_hook(&packet_filter_opt);	
	return 1;
}

//设备注销和钩子注销
static void ce_fw_exit(void)
{
	cdev_del(&cdev);  
	kfree(ce_fw_devp);
	unregister_chrdev_region(devno,1);
	nf_unregister_hook(&packet_filter_opt);
}

MODULE_AUTHOR("Cute_Eleven");
MODULE_LICENSE("GPL");

module_init(ce_fw_init); 
module_exit(ce_fw_exit); 



