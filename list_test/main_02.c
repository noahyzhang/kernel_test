#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

#define __KERNEL__
#include "list.h"

struct BizStu {
    int id;
    struct list_head list;
};

// 遍历
void for_each_list(struct BizStu* obj) {
    struct list_head* pos = NULL;
    printf("%d ", list_entry(&obj->list, struct BizStu, list)->id);
    list_for_each(pos, &obj->list) {
        struct BizStu* node = list_entry(pos, struct BizStu, list);
        printf("%d ", node->id);
    }
    printf("\n");
}

int main() {
    // 创建结构体，并初始化链表
    struct BizStu* head1 = malloc(sizeof(struct BizStu));
    head1->id = 0;
    INIT_LIST_HEAD(&head1->list);

    // 添加结构体节点
    for (int i = 1; i < 10; i++) {
        struct BizStu* tmp_node = malloc(sizeof(struct BizStu));
        tmp_node->id = i;
        INIT_LIST_HEAD(&tmp_node->list);
        list_add(&tmp_node->list, &head1->list);
    }
    // 打印链表
    for_each_list(head1);  // 0 9 8 7 6 5 4 3 2 1

    // 从链表中删除节点
    list_del(head1->list.next); // 删除 9 这个节点
    // 打印链表
    for_each_list(head1);  // 0 8 7 6 5 4 3 2 1
    
    struct BizStu* head2 = malloc(sizeof(struct BizStu));
    head2->id = 100;
    INIT_LIST_HEAD(&head2->list);
    for (int i = 200; i < 500; i += 100) {
        struct BizStu* tmp_node = malloc(sizeof(struct BizStu));
        tmp_node->id = i;
        INIT_LIST_HEAD(&tmp_node->list);
        list_add(&tmp_node->list, &head2->list);
    }
    for_each_list(head2);  // 100 400 300 200
    // 移动链表节点
    list_move(head2->list.next, &head1->list);  // 将 400 从 head2 链表中移动到 head1 链表中
    for_each_list(head1);  // 0 400 8 7 6 5 4 3 2 1
    for_each_list(head2);  // 100 300 200

    // 合并链表
    list_splice_init(&head2->list, &head1->list); // 将 head2 链表合并到 head1 中来
    for_each_list(head1);  // 0 300 200 400 8 7 6 5 4 3 2 1
    for_each_list(head2);  // 100

    // 边遍历边删除
    int count = 0;
    struct BizStu *pos = NULL, *next = NULL;
    printf("%d ", head1->id);
    list_for_each_entry_safe(pos, next, &head1->list, list) {
        if (count > 2) {
            list_del(&pos->list);
        }
        printf("%d ", pos->id);
        count++;
    }
    printf("\n");  // 0 300 200 400 8 7 6 5 4 3 2 1
    
    // 上面已经删除完了，再来遍历一次看效果
    for_each_list(head1);  // 0 300 200 400
    return 0;
}