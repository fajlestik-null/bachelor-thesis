#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Required for usleep()
#include <signal.h> // Required for SIGINT signal handling
#include <nfc/nfc.h>
#include "freefare.h"

//Global vars
nfc_context *context;
nfc_device *device;
static volatile int exit_flag = 1;

// Register escape -> Ctrl+C
void sigint_handler(int sig)
{
    (void)sig;
    exit_flag = 0;
}

// Init reader
void reader_init()
{
    nfc_init(&context);
    if (!context)
    {
        fprintf(stderr, "Unable to init libnfc\n");
        exit(EXIT_FAILURE);
    }

    device = nfc_open(context, NULL);
    if (!device)
    {
        fprintf(stderr, "ERROR: Unable to open NFC device.\n");
        nfc_exit(context);
        exit(EXIT_FAILURE);
    }
}

void run_loop(){
    while (exit_flag)
    {
        FreefareTag *tags = freefare_get_tags(device);

        if (tags)
        {
            for (int i = 0; tags[i]; i++)
            {
                if (freefare_get_tag_type(tags[i]) == MIFARE_DESFIRE)
                {
                    printf("Found MIFARE DESFire tag!\n");

                    if (mifare_desfire_connect(tags[i]) == 0)
                    {
                        char *uid = NULL;
                        /*if (mifare_desfire_get_card_uid(tags[i], &uid) == 0)
                        {
                            printf("\tTag UID: %s\n", uid);
                            free(uid);
                        }*/
                       uid = freefare_get_tag_uid(tags[i]);
                        if (uid)
                        {
                            printf("\tTag UID: %s\n", uid);
                            free(uid);
                        }

                        struct mifare_desfire_version_info version_info;
                        if (mifare_desfire_get_version(tags[i], &version_info) == 0)
                        {
                            printf("\tHW Version: 0x%02x.%d\n", version_info.hardware.version_major, version_info.hardware.version_minor);
                            printf("\tStorage Size Code: 0x%02x\n", version_info.hardware.storage_size);
                        }

                        mifare_desfire_disconnect(tags[i]);
                        printf("----------------------------------------\n");
                    }
                    else
                    {
                        perror("Failed to connect to DESFire tag");
                    }
                }
            }

            freefare_free_tags(tags);
        }

        usleep(2000000);
    }
}

int main(void)
{
    signal(SIGINT, sigint_handler);
 
    reader_init();


    printf("NFC Reader opened successfully: %s\n", nfc_device_get_name(device));
    printf("Continuously polling for DESFire cards... Press Ctrl+C to exit.\n\n");

    run_loop();

    printf("\nExiting and closing NFC reader...\n");
    nfc_close(device);
    nfc_exit(context);
    return EXIT_SUCCESS;
}