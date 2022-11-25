#include "list.h"
/**
 * @brief 链表初始化
 * @param list 链表对象的地址
 */
void List_Init(List *list)
{
	list->tail.next = NULL;
	list->head.next= &(list->tail);
}
/**
 * @brief 向指定链表中插入节点
 * @param node 待插入的节点
 * @param list 链表
 */
void List_Insert(Node *node,List *list)
{
    if(list->head.next == &list->tail)
    {
        list->head.next = node;
        node->next = &list->tail;
        return;
    }
    Node *n;
    for(n = list->head.next;n->next != &list->tail;n = n->next);
    n->next = node;
    node->next = &list->tail;
}