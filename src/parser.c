#include <parser.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void help(void);
int parse_number(int *number, const char *str);

int parse_arguments(CursesArt *art, int argc, char *argv[]) {
    int c, option_index;

    while (1) {
        static struct option long_options[] = {
            { "help",   no_argument,        0, 'H' },
            { "width",  required_argument,  0, 'w' },
            { "height", required_argument,  0, 'h' }
        };
        
        option_index = 0;

        c = getopt_long(argc, argv, "Hw:h:",
                long_options, &option_index);

        if (c == -1) break;

        switch (c) {
        case 0:
            /*
            if (long_options[option_index].flag != 0) break;
            */
            break;
        case 'H':
            help();
            return 0;

        case 'w': {
            int w;
            if (!parse_number(&w, optarg)) {
                printf("Wrong width value.\n");
                return 0;
            }

            art->sheet.width = w;

            break;

        }

        case 'h': {
            int h;
            if (!parse_number(&h, optarg)) {
                printf("Wrong height value.\n");
                return 0;
            }

            art->sheet.height = h;

            break;

        }

        case '?': return 0;
        
        default:
            return 0;
        }
    }

    if (optind == argc) {
        printf("Error: No files specified.\n");
        return 0;
    }

    if (optind != argc - 1) {
        printf("Error: Too many files specified.\n");
        return 0;
    }

    art->filename = malloc(strlen(argv[optind]) + 1);
    memcpy(art->filename, argv[optind], strlen(argv[optind]) + 1);

    return 1;
}

void help(void) {
    printf("Usage: cursesart [OPTION]... FILE\n");
    printf("The FILE filename is obligatory.\n\n");

    printf("Arguments:\n");
    printf("  %-30s%s", "-w VALUE, --width VALUE", "Sets the width of the sheet.\n");
    printf("  %-30s%s", "-h VALUE, --height VALUE", "Sets the height of the sheet.\n");
    printf("  %-30s%s", "-H, --help", "Show this help.\n");

}

int parse_number(int *number, const char *str) {
    int i;

    for (i = 0; i < strlen(str); i ++) {
        if (!isdigit(str[i])) return 0;
    }

    *number = atoi(str);

    return 1;
}
