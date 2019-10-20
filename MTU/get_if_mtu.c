/**
 * @file   get_if_mtu.c
 * @author Daniel Della Noce
 * @date   October 2019
 * @version 1.0
 * @brief   A function that returns the MTU of an interface.
 * This module will compile on macOS and any modern Linux that has GCC compiler.
 *
 * Tested with macOS Catalina (10.15) and Linux Mint 19.2 (Kernel 4.15.0-62)
 *
 * Based on the following articles.
 * @see 
 * @see 
 *
 * Compile & Execute
 * =================
 *
 * To compile as a stand alone program, do not forget to define __MAIN__.
 * gcc -Wall get_if_mtu.c -D__MAIN__ -o get_if_mtu
 *
 * To compile as an object file
 * gcc -Wall -c get_if_mtu.c
 *
 * To execute, open a shell and type
 * ./get_if_mtu eth0
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

//#include "get_if_mac.h"

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
/** @brief This function returns the MTU of an interface.
 *  The interface is passed in paranmeter as a string.
 *
 *  @param mtu:		The MTU of the interface. Undefined if an error occured.
 *  @param if_name:	The string of the interface name, ex: "en0", "eth0"
 *
 *  @return returns EXIT_SUCCESS if successful
 *  @return returns EXIT_FAILURE if NOT successful
 */
	int get_if_mtu (uint32_t *mtu, char *if_name) {
		return (EXIT_FAILURE);
	}
	#endif
#elif __linux
	int get_if_mtu (uint32_t *mtu, char *if_name) {
		int fd;
		struct ifreq ifr;
	
		if (strlen (if_name) > IFNAMSIZ) {
//			fprintf (stderr, "get_if_mtu: interface name > %u", IFNAMSIZ);
			return (EXIT_FAILURE);
		}

		fd = socket (AF_INET, SOCK_DGRAM, 0);
		if (fd < 0) {
//			perror("get_if_mtu: socket failed");
			return (EXIT_FAILURE);
		}

		ifr.ifr_addr.sa_family = AF_INET;
		strncpy(ifr.ifr_name, if_name, sizeof(ifr.ifr_name));

		if (ioctl(fd, SIOCGIFMTU, &ifr) == 0) {
			*mtu = ifr.ifr_mtu;
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
uint32_t mtu;
int result;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <interface name>\n", argv[0]);
		return 1;
	}

	result = get_if_mtu (&mtu, argv[1]);
	if (result == EXIT_SUCCESS) {
		printf("get_if_mtu: %u\n", mtu);
	} else {
		printf ("Error in get_if_mtu with interface %s\n", argv[1]);
	}

	return 0;
}
#endif
