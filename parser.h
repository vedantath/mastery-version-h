#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

typedef enum ActionType {
    ACT_FREE,
    ACT_ALLOC,
    ACT_END //marks when the parser has reached EOF
} action_type_t;

struct Parser {
    FILE* file;
    size_t size;
    action_type_t action;
    unsigned index;
};


bool init_parser(struct Parser* parser, char* filename);
void parse_next(struct Parser* parser);