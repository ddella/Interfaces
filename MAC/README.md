 
The function *get_mac_address*, returns the MAC address of an Ethernet interface.

This module will compile on macOS and any modern Linux that has GCC compiler. It has been tested with macOS Catalina (10.15) and Linux Mint 19.2 (Kernel 4.15.0-62).

* To compile as a stand alone program, do **gcc -Wall get_if_mac.c -D__MAIN__ -o get_if_mac**.
* To compile as an object file, do **gcc -Wall -c get_if_mac.c**.
* If compiled as a stand alone program, simply call it with one argument that is the string of the Ethernet interface:  **./get_if_mac eth0**. It will print something like **get_mac_address: aa:bb:cc:dd:ee:ff**.
* To use it with your program, let's say *myprog*, use the Makefile supplied. Don't forget to include the [get_if_mac.h](get_if_mac.h)in your source file to get the structure and prototype.

The function *get_mac_address* takes two arguments, see at the end for the function prototype:
* A pointer to a ```struct mac_addr```. This is an output parameter. It will be filled, by the function, with the MAC address, if it succeeds.
* A string of characters that represents the interface name I want the MAC address, ex: "eth0".

The function returns either **EXIT_SUCCESS** or **EXIT_FAILURE**.

```
int get_mac_address (struct mac_addr *, const char *)

// Simple structure for the Ethernet MAC address
struct mac_addr {
   uint8_t byte[ETHERNET_MAC_LEN];
};
```
