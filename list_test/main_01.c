#define __KERNEL__
#include "list.h"
#include <malloc.h>

struct dummyStruct {
		int dummy_node;         // 结构体节点
		struct list_head list;  // 链表节点
};

struct dummyStruct static_node = {
		.dummy_node = 0,
		.list = LIST_HEAD_INIT(static_node.list),   // 静态初始化链表节点
    };

int main() {
    for (int i = 1; i < 10; i++) {
        struct dummyStruct* node = malloc(sizeof(struct dummyStruct));
        node->dummy_node = i;
        INIT_LIST_HEAD(&node->list);
        list_add(&node->list, &static_node.list);
    }
        printf("%d ", list_entry(&static_node.list, struct dummyStruct, list)->dummy_node);
    struct list_head* p;
    list_for_each(p, &static_node.list) {
        struct dummyStruct* node = list_entry(p, struct dummyStruct, list);
        printf("%d ", node->dummy_node);
    }
    printf("\n");

    struct dummyStruct* head2 = malloc(sizeof(struct dummyStruct));
    head2->dummy_node = 100;
    INIT_LIST_HEAD(&head2->list);
    for (int i = 200; i < 1000; i+=100) {
        struct dummyStruct* node = malloc(sizeof(struct dummyStruct));
        node->dummy_node = i;
        INIT_LIST_HEAD(&node->list);
        list_add(&node->list, &head2->list);
    }
    printf("%d ", list_entry(&head2->list, struct dummyStruct, list)->dummy_node);
    list_for_each(p, &head2->list) {
        struct dummyStruct* node = list_entry(p, struct dummyStruct, list);
        printf("%d ", node->dummy_node);
    }
    printf("\n");


    list_splice(static_node.list.prev, &head2->list);
    printf("%d ", list_entry(&head2->list, struct dummyStruct, list)->dummy_node);
    list_for_each(p, &head2->list) {
        struct dummyStruct* node = list_entry(p, struct dummyStruct, list);
        printf("%d ", node->dummy_node);
    }
    printf("\n");

}