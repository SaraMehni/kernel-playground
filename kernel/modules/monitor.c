#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/ip.h>
#include <linux/ipv6.h>

static struct nf_hook_ops nfho_ipv4;
static struct nf_hook_ops nfho_ipv6;

static unsigned int monitor_hook_ipv4(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *ip_header = ip_hdr(skb);

    if (ip_header &&
        ip_header->saddr == htonl(0x7F000001) &&
        ip_header->daddr == htonl(0x7F000001)) {
        printk(KERN_INFO "Localhost IPv4 Packet: %pI4 -> %pI4\n",
               &ip_header->saddr, &ip_header->daddr);
    }

    return NF_ACCEPT;
}

static unsigned int monitor_hook_ipv6(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct ipv6hdr *ip6_header = ipv6_hdr(skb);

    if (ip6_header &&
        ipv6_addr_loopback(&ip6_header->saddr) &&
        ipv6_addr_loopback(&ip6_header->daddr)) {
        printk(KERN_INFO "Localhost IPv6 Packet: %pI6c -> %pI6c\n",
               &ip6_header->saddr, &ip6_header->daddr);
    }

    return NF_ACCEPT;
}

static int __init monitor_init(void)
{
    printk(KERN_INFO "Localhost Monitor Loaded\n");

    nfho_ipv4.hook = monitor_hook_ipv4;
    nfho_ipv4.hooknum = NF_INET_PRE_ROUTING;
    nfho_ipv4.pf = PF_INET;
    nfho_ipv4.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_ipv4);

    nfho_ipv6.hook = monitor_hook_ipv6;
    nfho_ipv6.hooknum = NF_INET_PRE_ROUTING;
    nfho_ipv6.pf = PF_INET6;
    nfho_ipv6.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_ipv6);

    return 0;
}

static void __exit monitor_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho_ipv4);
    nf_unregister_net_hook(&init_net, &nfho_ipv6);

    printk(KERN_INFO "Localhost Monitor Unloaded\n");
}

module_init(monitor_init);
module_exit(monitor_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sara Mehni");
MODULE_DESCRIPTION("Localhost Traffic Monitor");
