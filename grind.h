#include "parser.h"
#define HASH_TABLE_SIZE 7

typedef enum GrindState {
    GRIND_SUCCESS,
    GRIND_BAD_FREE,
    GRIND_FAILURE
} grind_state_t;

struct grind_elem {
    unsigned index;
    unsigned ref_count;
    size_t size;
    struct grind_elem* next;
};

void grind_init();
grind_state_t grind(struct Parser* parser);
void print_grinder();