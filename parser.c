#include "parser.h"


bool init_parser(struct Parser* parser, char* filename) {
    parser->file = fopen(filename, "r");
    if (!parser->file) {
        printf("no file\n");
        return false;
    }
    return true;
}


void parse_next(struct Parser* parser) {
    char line[256];
    if (fgets(line, sizeof(line), parser->file)) {
        //we will assume no bad inputs, allocates will be 'a' with an alloc number and a size
        //free will be f with an alloc number, just like mm lab
        char* saveptr;
        char* tok = strtok_r(line, " ", &saveptr);
        if (tok != NULL) {
            if (tok[0] == 'a') {
                parser->action = ACT_ALLOC;
                tok = strtok_r(NULL, " ", &saveptr);
                parser->index = atoi(tok);
                tok = strtok_r(NULL, " ", &saveptr);
                parser->size = atoi(tok);
            } else if (tok[0] == 'f') {
                parser->action = ACT_FREE;
                tok = strtok_r(NULL, " ", &saveptr);
                parser->index = atoi(tok);
            } else {
                parser->action = ACT_END;
            }
        } else {
            parser->action = ACT_END;
        }
    } else {
        parser->action = ACT_END;
    }
}