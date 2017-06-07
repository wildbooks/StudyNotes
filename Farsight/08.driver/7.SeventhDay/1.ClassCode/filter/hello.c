#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/slab.h>

#include <linux/net.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <net/snmp.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/route.h>
#include <linux/skbuff.h>
#include <net/sock.h>
#include <net/arp.h>
#include <net/icmp.h>
#include <net/raw.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <linux/netfilter_ipv4.h>
#include <net/xfrm.h>
#include <linux/mroute.h>
#include <linux/netlink.h>

unsigned int filter_hook(unsigned int hooknum,
                         struct sk_buff *skb,
                         const struct net_device *in,
                         const struct net_device *out,
                         int (*okfn)(struct sk_buff *))
{
	const struct iphdr *iph;
	unsigned int addr;
	unsigned char *p;

	iph = ip_hdr(skb);
	if(iph==NULL)
	{
		return NF_ACCEPT;
	}
	printk("protocol = %d \n",iph->protocol);

	addr = iph->saddr;

	p = (unsigned char*)(&addr);

	printk("saddr :%d.%d.%d.%d ",p[0],p[1],p[2],p[3]);

	addr = iph->daddr;

	p = (unsigned char*)(&addr);

	printk(" daddr :%d.%d.%d.%d \n",p[0],p[1],p[2],p[3]);
	return NF_ACCEPT;
}


struct nf_hook_ops pkt_filter =
{
        .hook = filter_hook,
        .owner = THIS_MODULE,
        .pf = PF_INET,
        .hooknum = NF_INET_PRE_ROUTING,
        .priority = NF_IP_PRI_FIRST,
};


int hello_init(void)
{
	printk("hello_init()\n");
	nf_register_hook(&pkt_filter);
	return 0;
}
void hello_exit(void)
{
	printk("hello_exit()\n");
	nf_unregister_hook(&pkt_filter);
	return;
}
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);
