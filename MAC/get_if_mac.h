#ifndef __GET_IF_MAC_H__
#define __GET_IF_MAC_H__

// IFHWADDRLEN is not defined on all platform, like macOS.
#ifndef IFHWADDRLEN
	#define ETHERNET_MAC_LEN	6
	//#define MAC_ADDRSTRLEN	6
#else
	#define ETHERNET_MAC_LEN	IFHWADDRLEN
#endif

// Simple structure for the Ethernet MAC address
struct mac_addr {
   uint8_t byte[ETHERNET_MAC_LEN];
};

	/************************************************/
	/***          Functions prototype             ***/
	/************************************************/

int get_mac_address (struct mac_addr *, const char *);

#endif