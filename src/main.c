#include "main.h"

int main(int argc, char** argv) {
    init_logger();
    int c;

    // Command line args
    while((c = getopt(argc, argv, "hsH:W:")) != -1){
        switch(c) {
            case 'h':
                printf(HELP_MESSAGE);
                return 0;
            case 's': // Screensaver
                printf("STUB \n");
                break;
            case 'W': // Width
                printf("STUB %ld\n", strtol(optarg, NULL, 10));
                break;
            case 'H': // Height
                printf("STUB %ld\n", strtol(optarg, NULL, 10));
                break;
            case '?': // Unrecognised
                printf(HELP_MESSAGE);
                return 1;
        }
    }

    close_logger();
    return 0;
}
