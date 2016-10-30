/*
	Scan for nearby bluetooth devices.

	Skeleton based on: http://people.csail.mit.edu/albert/bluez-intro/c404.html
	Compile using: gcc -Wall -Wextra -o scan.out scan.c -lbluetooth
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main()
{
	int dev_id = hci_get_route(NULL);
	if (dev_id < 0) {
		/* No bluetooth device found. This is no necessarily an error if 
			bluetooth is turned off on the host system.
		*/
		printf("No local bluetooth adaptor found.\n");
		exit(EXIT_SUCCESS);
	}

	printf("Found a bluetooth adaptor. Device ID <%d>\n", dev_id);

	int sock = hci_open_dev(dev_id);
	if (sock < 0) {
		/* Could not open socket to bluetooth device */
		perror("Could not open socket to bluetooth adaptor.");
		exit(EXIT_FAILURE);
	}

	printf("Socket <%d> to adaptor <%d> opened successfully.\n", sock, dev_id);

	close(sock);

	exit(EXIT_SUCCESS);
}