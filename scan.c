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
    /*  Find a local bluetooth adaptor.
        Passing NULL to hci_get_route means we don't care which local bluetooth
        adaptor we get.
    */
    int dev_id = hci_get_route(NULL);
    if (dev_id < 0) {
        /* Could not find a local bluetooth adaptor. This is not necessarily an
            error if Bluetooth is turned off on the host system.
        */
        printf("Could not find a local Bluetooth adaptor.\n");
        exit(EXIT_SUCCESS);
    }

    printf("Found a bluetooth adaptor. Device ID <%d>.\n", dev_id);

    int sock = hci_open_dev(dev_id);
    if (sock < 0) {
        /* Could not open socket to bluetooth device */
        perror("Could not open socket to bluetooth adaptor.");
        exit(EXIT_FAILURE);
    }

    printf("Opened socket <%d> to adaptor <%d>.\n", sock, dev_id);

    const int MAX_RSP = 255;
    inquiry_info *ii = malloc(MAX_RSP * sizeof(inquiry_info));
    if (ii) {
        const int LEN = 8;
        const int FLAGS = IREQ_CACHE_FLUSH;
        const int TIMEOUT = 0;

        /* Use the adaptor to scan for nearby bluetooth devices. */
        int num_rsp = hci_inquiry(dev_id, LEN, MAX_RSP, NULL, &ii, FLAGS);
        if (num_rsp < 0) perror("hci_inquiry");

        printf("Found <%d> Bluetooth devices.\n", num_rsp);

        char addr[19] = { 0 };
        char name[248] = { 0 };

        int i = 0;
        for (; i < num_rsp; ++i)
        {
            ba2str(&(ii+i)->bdaddr, addr);
            memset(name, 0, sizeof(name));
            if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name,
                 TIMEOUT) < 0) {
                strcpy(name, "[unknown]");
            }

            printf("%s  %s\n", addr, name);
        }

        free(ii);
    }

    close(sock);
    exit(EXIT_SUCCESS);
}