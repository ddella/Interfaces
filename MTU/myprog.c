#include <stdlib.h>
#include <stdio.h>
#include "get_if_mtu.h"

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

	return EXIT_SUCCESS;
}
