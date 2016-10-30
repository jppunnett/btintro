/*
	Scan for nearby bluetooth devices.

	Skeleton based on: http://people.csail.mit.edu/albert/bluez-intro/c404.html
	Compile using: gcc -o scan.out scan.c -lbluetooth
*/
#include <stdio.h>
#include <stdlib.h>
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
		printf("No bluetooth devices found.\n");
		exit(EXIT_SUCCESS);
	}

	printf("Found a bluetooth device. Device ID <%d>\n", dev_id);

	exit(EXIT_SUCCESS);
}