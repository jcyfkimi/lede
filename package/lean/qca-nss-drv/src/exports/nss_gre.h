/*
 **************************************************************************
 * Copyright (c) 2017, The Linux Foundation. All rights reserved.
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 **************************************************************************
 */

/**
 * @file nss_gre.h
 *	NSS GRE interface definitions.
 */
#ifndef _NSS_GRE_H_
#define _NSS_GRE_H_

#include <net/ip_tunnels.h>
#include <net/ip6_tunnel.h>

/**
 * @addtogroup nss_gre_subsystem
 * @{
 */

/**
 * Maximum number of session debug statistics
 */
#define NSS_GRE_MAX_DEBUG_SESSION_STATS 16

/**
 * GRE flags
 */
#define NSS_GRE_CONFIG_IKEY_VALID	0x00000001	/**< Incoming key of GRE header. */
#define NSS_GRE_CONFIG_OKEY_VALID	0x00000002	/**< Key for outgoing GRE header. */
#define NSS_GRE_CONFIG_ISEQ_VALID	0x00000004	/**< Enable sequence checking for incoming GRE traffic. */
#define NSS_GRE_CONFIG_OSEQ_VALID	0x00000008	/**< Add sequence number for out going GRE packets. */
#define NSS_GRE_CONFIG_ICSUM_VALID	0x00000010	/**< Validate incoming GRE header Checksum. */
#define NSS_GRE_CONFIG_OCSUM_VALID	0x00000020	/**< Add CS header to GRE header*/
#define NSS_GRE_CONFIG_TOS_INHERIT	0x00000040	/**< Inherit inner IP TOS to tunnel header, if not set configure provided TOS. */
#define NSS_GRE_CONFIG_TTL_INHERIT	0x00000080	/**< Inherit inner IP TTL to tunnel header, if not set configure provided TTL. */
#define NSS_GRE_CONFIG_SET_DF		0x00000100	/**< Enable DF bit on tunnel IP header. */
#define NSS_GRE_CONFIG_SET_MAC		0x00000200	/**< Add MAC header to GRE+IP tunnel header. */
#define NSS_GRE_CONFIG_SET_PADDING	0x00000400	/**< Add PADDING to align tunnel IP/GRE header. */
#define NSS_GRE_CONFIG_NEXT_NODE_AVAILABLE  0x00000800	/**< Use provided next_node instead of existing next node. */

/**
 * nss_gre_info
 *	GRE private information.
 */
struct nss_gre_info {
	union {
		struct ip_tunnel t4;	/**< IPv4 tunnel */
		struct ip6_tnl t6;	/**< IPv6 tunnel */
	} t;
	int nss_if_number;		/**< NSS interface number */
	struct net_device *next_dev;	/**< Next net device */
	uint8_t gre_hlen;		/**< GRE header length */
	uint8_t pad_len;		/**< Pad length */
};

/**
 * nss_gre_msg_types
 *	Message types for GRE requests and responses.
 */
enum nss_gre_msg_types {
	NSS_GRE_MSG_CONFIGURE = NSS_IF_MAX_MSG_TYPES + 1,
	NSS_GRE_MSG_DECONFIGURE,
	NSS_GRE_MSG_SESSION_STATS,
	NSS_GRE_MSG_BASE_STATS,
	NSS_GRE_MSG_MAX
};

/**
 * GRE Mode Types
 */
enum nss_gre_mode {
	NSS_GRE_MODE_TUN,	/**< GRE Tunnel interface. */
	NSS_GRE_MODE_TAP,	/**< GRE Tap interface. */
	NSS_GRE_MODE_MAX	/**< Maxmum GRE mode. */
};

/**
 * GRE IP Types
 */
enum nss_gre_ip_types {
	NSS_GRE_IP_IPV4,	/**<  Outer Tunnel is IPV4. */
	NSS_GRE_IP_IPV6,	/**<  Outer Tunnel is IPV6. */
	NSS_GRE_IP_MAX,		/**<  Maximum IP Types. */
};

/**
 * GRE Base debug statistics
 */
enum nss_gre_base_debug_types {
	GRE_BASE_RX_PACKETS,			/**< Rx packet count. */
	GRE_BASE_RX_DROPPED,			/**< Number of packet dropped at Rx. */
	GRE_BASE_EXP_ETH_HDR_MISSING,		/**< Ethernet header missing. */
	GRE_BASE_EXP_ETH_TYPE_NON_IP,		/**< Packet is not IPV4 or IPV6. */
	GRE_BASE_EXP_IP_UNKNOWN_PROTOCOL,	/**< Packet protocol is unknown. */
	GRE_BASE_EXP_IP_HEADER_INCOMPLETE,	/**< Bad IP header. */
	GRE_BASE_EXP_IP_BAD_TOTAL_LENGTH,	/**< IP total lenghth is invalid. */
	GRE_BASE_EXP_IP_BAD_CHECKSUM,		/**< IP checksum is bad. */
	GRE_BASE_EXP_IP_DATAGRAM_INCOMPLETE,	/**< Bad packet. */
	GRE_BASE_EXP_IP_FRAGMENT,		/**< IP packet is a fragment. */
	GRE_BASE_EXP_IP_OPTIONS_INCOMPLETE,	/**< IP option is invalid. */
	GRE_BASE_EXP_IP_WITH_OPTIONS,		/**< IP packet with options. */
	GRE_BASE_EXP_IPV6_UNKNOWN_PROTOCOL,	/**< Protocol is unknown. */
	GRE_BASE_EXP_IPV6_HEADER_INCOMPLETE,	/**< Incomplete ipv6 header. */
	GRE_BASE_EXP_GRE_UNKNOWN_SESSION,	/**< Unknown GRE session. */
	GRE_BASE_EXP_GRE_NODE_INACTIVE,		/**< GRE node is inactive. */
	GRE_BASE_DEBUG_MAX,			/**< GRE base debug max. */
};

/*
 * GRE session Packet drop and exception events.
 */
enum gre_session_debug_types {
	GRE_SESSION_PBUF_ALLOC_FAIL,		/**< Pbuf allocation failure. */
	GRE_SESSION_DECAP_FORWARD_ENQUEUE_FAIL,	/**< Rx forward enqueue failure. */
	GRE_SESSION_ENCAP_FORWARD_ENQUEUE_FAIL,	/**< Tx forward enqueue failure. */
	GRE_SESSION_DECAP_TX_FORWARDED,		/**< Number of packets forwarded after decap. */
	GRE_SESSION_ENCAP_RX_RECEIVED,		/**< Number of packets received for encap. */
	GRE_SESSION_ENCAP_RX_DROPPED,		/**< Packets dropped while enqueuing for encap. */
	GRE_SESSION_ENCAP_RX_LINEAR_FAIL,	/**< Packets dropped during encap linearization. */
	GRE_SESSION_EXP_RX_KEY_ERROR,		/**< Rx KEY error. */
	GRE_SESSION_EXP_RX_SEQ_ERROR,		/**< Rx Sequence number error. */
	GRE_SESSION_EXP_RX_CS_ERROR,		/**< Rx checksum error */
	GRE_SESSION_EXP_RX_FLAG_MISMATCH,	/**< Rx flag mismatch. */
	GRE_SESSION_EXP_RX_MALFORMED,		/**< Rx packet is malformed. */
	GRE_SESSION_EXP_RX_INVALID_PROTOCOL,	/**< Rx packet protocol is invalid. */
	GRE_SESSION_EXP_RX_NO_HEADROOM,		/**< Packet does not have enough headroom. */
	GRE_SESSION_DEBUG_MAX,			/**< Session debug max. */
};

/**
 * GRE create message structure.
 */
struct nss_gre_config_msg {
	uint32_t src_ip[4];			/**< Source IPv4 or IPv6 Adddress. */
	uint32_t dest_ip[4];			/**< Destination IPv4 or IPv6 Adddress. */
	uint32_t flags;				/**< GRE Flags. */
	uint32_t ikey;				/**< GRE rx KEY.*/
	uint32_t okey;				/**< GRE tx KEY. */
	uint32_t mode;				/**< GRE TUN or TAP. */
	uint32_t ip_type;			/**< IPv4 or IPv6 type. */
	uint32_t next_node_if_num;		/**< To whom to forward packets. */
	uint16_t src_mac[3];			/**< Source MAC address. */
	uint16_t dest_mac[3];			/**< Destination MAC address. */
	uint8_t ttl;				/**< TTL or HOPLIMIT. */
	uint8_t tos;				/**< Type of service. */
	uint16_t reserved;			/**< Padding Reservation. */
};

/**
 * GRE link up message structure
 */
struct nss_gre_linkup_msg {
	int if_number;			/**< Interface number. */
};

/**
 * GRE link down message structure
 */
struct nss_gre_linkdown_msg {
	int if_number;			/**< Interface number. */
};

/**
 * GRE deconfig message structure
 */
struct nss_gre_deconfig_msg {
	int if_number;			/**< Interface number */
};

/**
 * GRE session statistics message
 */
struct nss_gre_session_stats_msg {
	struct nss_cmn_node_stats node_stats;	/**< Common node statistics. */
	uint32_t stats[GRE_SESSION_DEBUG_MAX];	/**< Session debug statistics. */
};

/**
 * GRE base statistics message
 */
struct nss_gre_base_stats_msg {
	uint32_t stats[GRE_BASE_DEBUG_MAX];	/**< Base debug statistics. */
};

/**
 * nss_gre_msg
 *	Message structure to send/receive GRE messages
 */
struct nss_gre_msg {
	struct nss_cmn_msg cm;					/**< Common message header */

	/**
	 * Payload of a GRE message.
	 */
	union {
		struct nss_gre_config_msg cmsg;			/**< GRE session config message. */
		struct nss_gre_deconfig_msg dmsg;		/**< GRE session deconfig message. */
		struct nss_gre_linkup_msg linkup;		/**< GRE link up message. */
		struct nss_gre_linkdown_msg linkdown;		/**< GRE link down message. */
		struct nss_gre_session_stats_msg sstats;	/**< GRE session statistics message. */
		struct nss_gre_base_stats_msg bstats;		/**< Base statistics message. */
	} msg;							/**< Message payload. */
};

/**
 * Callback function to receive GRE messages
 *
 * @datatypes
 * nss_gre_msg
 *
 * @param[in] app_data  Pointer to the application context of the message.
 * @param[in] msg       Pointer to the message data.
 */
typedef void (*nss_gre_msg_callback_t)(void *app_data, struct nss_gre_msg *msg);

/**
 * nss_gre_tx_msg
 *	Sends GRE messages to the NSS.
 *
 * @datatypes
 * nss_ctx_instance \n
 * nss_gre_msg
 *
 * @param[in] nss_ctx  Pointer to the NSS context.
 * @param[in] msg      Pointer to the message data.
 *
 * @return
 * Status of the Tx operation.
 */
extern nss_tx_status_t nss_gre_tx_msg(struct nss_ctx_instance *nss_ctx, struct nss_gre_msg *msg);

/**
 * nss_gre_tx_msg_sync
 *	Sends GRE messages to the NSS synchronously.
 *
 * @datatypes
 * nss_ctx_instance \n
 * nss_gre_msg
 *
 * @param[in] nss_ctx  Pointer to the NSS context.
 * @param[in] msg      Pointer to the message data.
 *
 * @return
 * Status of the Tx operation.
 */
extern nss_tx_status_t nss_gre_tx_msg_sync(struct nss_ctx_instance *nss_ctx, struct nss_gre_msg *msg);

/**
 * nss_gre_tx_buf
 *	Sends packet to the NSS
 *
 * @datatypes
 * nss_ctx_instance \n
 * sk_buff
 *
 * @param[in] nss_ctx  Pointer to the NSS context.
 * @param[in] if_num   Nss interface number.
 * @param[in] skb      Pointer to sk_buff.
 *
 * @return Tx status
 */
extern nss_tx_status_t nss_gre_tx_buf(struct nss_ctx_instance *nss_ctx, uint32_t if_num, struct sk_buff *skb);

/**
 * nss_gre_get_context.
 *	Gets the GRE context used in nss_gre_tx.
 *
 * @return
 * Pointer to the NSS core context.
 */
extern struct nss_ctx_instance *nss_gre_get_context(void);

/**
 * Callback function for receiving GRE session data.
 *
 * @datatypes
 * net_device \n
 * sk_buff \n
 * napi_struct
 *
 * @param[in] netdev  Pointer to the associated network device.
 * @param[in] skb     Pointer to the data socket buffer.
 * @param[in] napi    Pointer to the NAPI structure.
 */
typedef void (*nss_gre_data_callback_t)(struct net_device *netdev, struct sk_buff *skb, struct napi_struct *napi);

/**
 * nss_gre_base_debug_stats_get
 *	Gets NSS GRE base debug statistics.
 *
 * @param[in]  stats_mem  Pointer to memory to which stats should be copied.
 * @param[in]  size 	  Stats memory size.
 * @param[out] stats_mem  Pointer to the memory address, which must be large
 *                         enough to hold all the statistics.
 * @return
 * None.
 */
extern void nss_gre_base_debug_stats_get(void *stats_mem, int size);

/**
 * nss_gre_session_debug_stats_get
 *	Gets NSS GRE session debug statistics.
 *
 * @param[in]  stats_mem  Pointer to memory to which stats should be copied.
 * @param[in]  size 	  Stats memory size.
 * @param[out] stats_mem  Pointer to the memory address, which must be large
 *                         enough to hold all the statistics.
 * @return
 * None.
 */
extern void nss_gre_session_debug_stats_get(void *stats_mem, int size);

/**
 * nss_gre_register_if
 *	Registers the GRE interface with the NSS for sending and
 *	receiving messages.
 *
 * @datatypes
 * nss_gre_data_callback_t \n
 * nss_gre_msg_callback_t \n
 * net_device
 *
 * @param[in] if_num		     NSS interface number.
 * @param[in] nss_gre_data_callback  Callback for the data.
 * @param[in] msg_callback	     Callback for the message.
 * @param[in] netdev		     Pointer to the associated network device.
 * @param[in] features		     Socket buffer types supported by this interface.
 *
 * @return
 * Pointer to the NSS core context.
 */
extern struct nss_ctx_instance *nss_gre_register_if(uint32_t if_num, nss_gre_data_callback_t gre_callback,
					nss_gre_msg_callback_t msg_callback, struct net_device *netdev, uint32_t features);

/**
 * nss_gre_unregister_if
 *	Deregisters the GRE interface from the NSS.
 *
 * @param[in] if_num  NSS interface number.
. *
 * @return
 * None.
 *
 * @dependencies
 * The tunnel interface must have been previously registered.
 */
extern void nss_gre_unregister_if(uint32_t if_num);

/**
 * nss_gre_msg_init
 *	Initializes a GRE message.
 *
 * @datatypes
 * nss_gre_msg
 *
 * @param[in,out] ncm       Pointer to the message.
 * @param[in]     if_num    Interface number
 * @param[in]     type      Type of message.
 * @param[in]     len       Size of the payload.
 * @param[in]     cb        Pointer to the message callback.
 * @param[in]     app_data  Pointer to the application context of the message.
 *
 * @return
 * None.
 */
extern void nss_gre_msg_init(struct nss_gre_msg *ncm, uint16_t if_num, uint32_t type,  uint32_t len, void *cb, void *app_data);

/**
 * nss_gre_register_handler
 *	Registers the GRE interface with the NSS debug statistics handler.
 *
 * @return
 * None.
 */
extern void nss_gre_register_handler(void);

/**
 * Callback function for updating stats.
 *
 * @datatypes
 * net_device \n
 * sk_buff \n
 *
 * @param[in] netdev  Pointer to the associated network device.
 * @param[in] skb     Pointer to the data socket buffer.
 *
 * @return
 * None.
 */
typedef void (*nss_gre_pkt_callback_t)(struct net_device *netdev, struct sk_buff *skb);

/**
 * nss_gre_register_pkt_callback
 *	Register for rx packet call back.
 *
 * @datatypes
 * nss_gre_pkt_callback_t
 *
 * @param[in] cb  Call back function which needs to be registered.
 *
 * @return
 * None.
 */
extern void nss_gre_register_pkt_callback(nss_gre_pkt_callback_t cb);

/**
 * nss_gre_unregister_pkt_callback
 *	Unregister for rx packet call back.
 *
 * @datatypes
 * nss_gre_pkt_callback_t
 *
 * @return
 * None.
 */
extern void nss_gre_unregister_pkt_callback(void);

/**
 * @}
 */

#endif /* _NSS_GRE_H_ */
