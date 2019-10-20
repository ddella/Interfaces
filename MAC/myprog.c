#include <stdlib.h>
#include <stdio.h>
#include "get_if_mac.h"

int main(int argc, char *argv[]) {
struct mac_addr mac_addr;
int result;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <interface name>\n", argv[0]);
		return EXIT_FAILURE;
	}

	result = get_mac_address (&mac_addr, argv[1]);
	if (result == EXIT_SUCCESS) {
		printf("get_mac_address: %02x:%02x:%02x:%02x:%02x:%02x\n",\
			mac_addr.byte[0], mac_addr.byte[1], mac_addr.byte[2], mac_addr.byte[3], mac_addr.byte[4], mac_addr.byte[5]);
	} else {
		printf ("Error in get_mac_address with interface %s\n", argv[1]);
	}
	return EXIT_SUCCESS;
}
