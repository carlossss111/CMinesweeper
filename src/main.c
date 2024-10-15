#include "main.h"

int main(int argc, char** argv) {
    int c;

    while((c = getopt(argc, argv, "sh:w:")) != -1){
        switch(c) {
            case 's': // Screensaver
                printf("STUB \n");
                break;
            case 'w': // Width
                printf("STUB %ld\n", strtol(optarg, NULL, 10));
                break;
            case 'h': // Height
                printf("STUB %ld\n", strtol(optarg, NULL, 10));
                break;
            case '?': // Unrecognised
                printf(HELP_MESSAGE);
                return 1;
        }
    }

    return 0;
}

