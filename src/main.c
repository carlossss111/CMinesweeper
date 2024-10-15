#include "main.h"
#include "graphics.h"

int main(int argc, char** argv) {
    int c;

    // Command line args
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

    // test code
    graphics_init();
    Position pos;
    pos.x = 10;
    pos.y = 0;
    draw_cell(1, pos);
    pos.y++;
    draw_cell(2, pos);
    pos.y++;
    draw_cell(3, pos);
    pos.y++;
    draw_cell(4, pos);
    pos.y++;
    draw_cell(5, pos);
    pos.y++;
    draw_cell(6, pos);
    pos.y++;
    draw_cell(7, pos);
    pos.y++;
    draw_cell(8, pos);
    refresh();
    for(;;);
    graphics_finish();
    return 0;
}

