// Stack Frame
// Calling convention
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct node_tag node;
struct node_tag {
    node *next;
    int value1;
    int value2;
};

typedef struct list_tag list;
struct list_tag {
    node *head;
    node **tail;
    int len;
};

list *g_list;
int value1[0x20] = {22, 104, 19, 88, 123, 75, 67, 27, 0, 79, 104, 16, 17, 20, 57, 76, 107, 17, 4, 26, 23, 109, 110, 71, 109, 84, 29, 22, 85, 27, 5, 94};
int value2[0x20] = {175, 219, 173, 224, 255, 213, 208, 151, 143, 212, 251, 159, 223, 217, 170, 213, 248, 143, 136, 149, 132, 249, 231, 136, 171, 153, 209, 130, 204, 212, 203, 220};
// FLAG{alspdlp12lflasplkv0923kf01}

void init()
{
    g_list = malloc(sizeof(list));
    g_list->head = NULL;
    g_list->tail = &(g_list->head);
    g_list->len = 0;

    for (int i = 0; i < 0x20; ++i) {
        node *n = *(g_list->tail) = malloc(sizeof(node));
        n->next = NULL;
        n->value1 = value1[i] ^ 0x5a;
        n->value2 = value2[i] ^ 0xa5;
        
        g_list->tail = &(n->next);
        g_list->len += 1;
    }
}

int main()
{
    init();
    printf("I haven't finished writing the code\n");
    printf("TODO: Xor node->value1 and node->value2\n");
}
