#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "grind.h"

int main(int argc, char *argv[]) {
    char *input_file = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "t:")) != -1) {
        switch (opt) {
            case 't':
                input_file = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-t inputfile]\n", argv[0]);
                return 1;
        }
    }

    if (!input_file) {
        fprintf(stderr, "Error: -t flag requires a file.\n");
        return 1;
    }

    grind_init();
    struct Parser parser;
    init_parser(&parser, input_file);
    grind_state_t grind_out = grind(&parser);
    if (grind_out != GRIND_SUCCESS) {
        printf("grind failed\n");
    }
    print_grinder();
    return 0;
}