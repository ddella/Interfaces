/**
 * @file   get_if_mac.c
 * @author Daniel Della Noce
 * @date   October 2019
 * @version 1.0
 * @brief   A function that returns the MAC address of an Ethernet interface.
 * This module will compile on macOS and any modern Linux that has GCC compiler.
 *
 * Tested with macOS Catalina (10.15) and Linux Mint 19.2 (Kernel 4.15.0-62)
 *
 * Based on the following articles.
 * @see http://nadeausoftware.com/articles/2012/01/c_c_tip_how_use_compiler_predefined_macros_detect_operating_system#OSXiOSandDarwin
 * @see https://stackoverflow.com/questions/3964494/having-a-problem-figuring-out-how-to-get-ethernet-interface-info-on-mac-os-x-usi
 *
 * Compile & Execute
 * =================
 *
 * To compile as a stand alone program, do not forget to define __MAIN__.
 * gcc -Wall get_if_mac.c -D__MAIN__ -o get_if_mac
 *
 * To compile as an object file
 * gcc -Wall -c get_if_mac.c
 *
 * To execute, open a shell and type
 * ./get_if_mac eth0
 *
*/

#include <sys/sysctl.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#ifdef __APPLE__
	#include <net/if_dl.h>
#endif
#include <ifaddrs.h>
#include <sys/types.h>
#include <stdint.h>

#ifdef __linux
	#include <stdint.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

#include "get_if_mac.h"

#ifdef _WIN64
   //define something for Windows (64-bit)
#elif _WIN32
   //define something for Windows (32-bit)
#elif __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE && TARGET_IPHONE_SIMULATOR
		// define something for simulator   
	#elif TARGET_OS_IPHONE
		// define something for iphone  
	#else
/** @brief This function returns the MAC address of an Ethernet interface.
 *  The interface is passed in paranmeter as a string.
 *
 *  @param mac_addr:	The MAC address of the interface. Undefined if an error occured.
 *		The MAC address is return in a simple structure of 6 uint8_t bytes.
 *  @param if_name:	The string of the interface name, ex: "en0", "eth0"
 *
 *  @return returns EXIT_SUCCESS if successful
 *  @return returns EXIT_FAILURE if NOT successful
 */
		int get_mac_address (struct mac_addr *mac_addr, const char *if_name) {
		struct ifaddrs *iflist;
		struct sockaddr_dl *sdl;
		struct ifaddrs *cur;
		int found = EXIT_FAILURE;

			if (strlen (if_name) > IFNAMSIZ) {
				//fprintf (stderr, "get_mac_address: interface name > %u\n", IFNAMSIZ);
				return (EXIT_FAILURE);
			}

			//This way, the struct would be defined in case of error!
			//memset(mac_addr, 0xff, ETHERNET_MAC_LEN);
			if (getifaddrs(&iflist) == 0) {
				for (cur = iflist; cur; cur = cur->ifa_next) {
					if ((cur->ifa_addr->sa_family == AF_LINK) && 
					(strcmp(cur->ifa_name, if_name) == 0) && cur->ifa_addr) {
						sdl = (struct sockaddr_dl*)cur->ifa_addr;
						/*Make sure we don't copy more than ETHERNET_MAC_LEN bytes,
						  this condition should never happen */
						if (sdl->sdl_alen == ETHERNET_MAC_LEN) {
							memcpy(mac_addr, LLADDR(sdl), sdl->sdl_alen);
							found = EXIT_SUCCESS;
						}
						break;
					}
				}
				freeifaddrs(iflist);
			}
			return (found);
		}
	#endif
#elif __linux
	int get_mac_address (struct mac_addr *mac_addr, char *if_name) {
		int fd;
		struct ifreq ifr;
		//struct mac_addr *mac = NULL;
	
		if (strlen (if_name) > IFNAMSIZ) {
//			fprintf (stderr, "get_mac_address: interface name > %u", IFNAMSIZ);
			return (EXIT_FAILURE);
		}

		memset (&ifr, 0, sizeof(ifr));
		fd = socket (AF_INET, SOCK_DGRAM, 0);
		if (fd < 0) {
//			perror("get_mac_address: socket failed");
			return (EXIT_FAILURE);
		}

		ifr.ifr_addr.sa_family = AF_INET;
		strncpy(ifr.ifr_name, if_name, sizeof(ifr.ifr_name));

		if (ioctl (fd, SIOCGIFHWADDR, &ifr) == 0) {
			memcpy (mac_addr, (uint8_t *)ifr.ifr_hwaddr.sa_data, ETHERNET_MAC_LEN);
			close(fd);
			return (EXIT_SUCCESS);
		}
		return (EXIT_FAILURE);
	}
#elif __unix // all unices not caught above
    // Unix
#elif __posix
    // POSIX
#endif

#ifdef __MAIN__
int main(int argc, char *argv[]) {
struct mac_addr mac_addr;
int result;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <interface name>\n", argv[0]);
		return 1;
	}

	result = get_mac_address (&mac_addr, argv[1]);
	if (result == EXIT_SUCCESS) {
		printf("get_mac_address: %02x:%02x:%02x:%02x:%02x:%02x\n",\
			mac_addr.byte[0], mac_addr.byte[1], mac_addr.byte[2], mac_addr.byte[3], mac_addr.byte[4], mac_addr.byte[5]);
	} else {
		printf ("Error in get_mac_address with interface %s\n", argv[1]);
	}

	return 0;
}
#endif
