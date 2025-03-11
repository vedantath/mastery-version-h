#include "grind.h"
#include "stdbool.h"


struct grind_elem* allocs[HASH_TABLE_SIZE];

static bool print_and_free_list(struct grind_elem* head);
static unsigned hash(unsigned idx);
static void free_grind_elem(struct grind_elem** ge);

void grind_init() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        allocs[i] = NULL;
    }
}

grind_state_t grind(struct Parser* parser) {
    grind_state_t res = GRIND_SUCCESS;
    parse_next(parser);
    while (parser->action != ACT_END) {
        if (parser->action == ACT_ALLOC) {
            struct grind_elem* new_elem = malloc(sizeof(struct grind_elem));
            if (!new_elem) {
                return GRIND_FAILURE;
            }
            new_elem->next = allocs[hash(parser->index)];
            new_elem->index = parser->index;
            new_elem->size = parser->size;
            allocs[hash(parser->index)] = new_elem;
        } else {
            struct grind_elem* itr = allocs[hash(parser->index)];
            struct grind_elem* prev = NULL;
            bool freed = false;
            while (itr != NULL && !freed) {
                if (itr->index == parser->index) {
                    if (prev == NULL) {
                        allocs[hash(parser->index)] = itr->next;
                    } else {
                        prev->next = itr->next;
                    }
                    free_grind_elem(&itr);
                    freed = true;
                }
                prev = itr;
            }
            if (!freed) {
                return GRIND_BAD_FREE;
            }
        }
        parse_next(parser);
    }
    return res;
}

void print_grinder() {
    bool leaks = false;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        leaks |= print_and_free_list(allocs[i]);
    }
    if (!leaks) {
        printf("No leaks; congrats!\n");
    }
}

static bool print_and_free_list(struct grind_elem* head) {
    struct grind_elem* itr = head;
    if (head == NULL) {
        return false;
    }
    while (itr != NULL) {
        struct grind_elem* next = itr->next;
        printf("Uh Oh! %ld Bytes Leaked From Line: %d\n", itr->size, itr->index);
        free_grind_elem(&itr);
        itr = next;
    }
    return true;
}

static unsigned hash(unsigned idx) {
    return idx % HASH_TABLE_SIZE;
}

static void free_grind_elem(struct grind_elem** ge) {
    free(*ge);
    *ge = NULL;
}
