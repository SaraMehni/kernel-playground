#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

static struct nf_hook_ops nfho;

static unsigned int monitor_hook(void *priv,
                                 struct sk_buff *skb,
                                 const struct nf_hook_state *state)
{
    struct iphdr *ip_header;

    ip_header = ip_hdr(skb);

    if (ip_header &&
        ip_header->saddr == htonl(0x7F000001) &&
        ip_header->daddr == htonl(0x7F000001))
    {
        printk(KERN_INFO "Localhost Packet: %pI4 -> %pI4\n",
               &ip_header->saddr,
               &ip_header->daddr);
    }

    return NF_ACCEPT;
}

static int __init monitor_init(void)
{
    printk(KERN_INFO "Localhost Monitor Loaded\n");

    nfho.hook = monitor_hook;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);

    return 0;
}

static void __exit monitor_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho);

    printk(KERN_INFO "Localhost Monitor Unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sara Mehni");
MODULE_DESCRIPTION("Localhost Traffic Monitor");
