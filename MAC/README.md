 
The function *get_mac_address*, returns the MAC address of an Ethernet interface.

This module will compile on macOS and any modern Linux that has GCC compiler. It has been tested with macOS Catalina (10.15) and Linux Mint 19.2 (Kernel 4.15.0-62).

* To compile as a stand alone program, do **gcc -Wall get_if_mac.c -D__MAIN__ -o get_if_mac**.
* To compile as an object file, do **gcc -Wall -c get_if_mac.c**.
* If compiled as a stand alone program, simply call it with one argument that is the string of the Ethernet interface:  **./get_if_mac eth0**. It will print something like **get_mac_address: aa:bb:cc:dd:ee:ff**.

The program will print the MAC address as a string **"xx:xx:xx:xx:xx:xx"**.
 
