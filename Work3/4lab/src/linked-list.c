#include <stddef.h>
#include <stdlib.h>
#define LIST_TYPE double
#include "../include/linked-list.h"

LinkedList create_list(void) {
    LinkedList list = {
        .head = NULL,
        .tail = NULL,
        .size = 0,
    };

    return list;
}

void push_front_list(LinkedList* list, LIST_TYPE value) {
    if (!list)
        return;

    Node* node = create_node(value);
    if (!node)
        return;

    if (list->head) {
        node->next = list->head;
    }

    list->head = node;

    ++list->size;
    return;
}

void push_back_list(LinkedList* list, LIST_TYPE value) {
    if (!list)
        return;

    Node* node = create_node(value);
    if (!node)
        return;

    if (list->tail) {
        node->prev = list->tail;
    }

    list->tail = node;

    ++list->size;
    return;
}

void erase_list(LinkedList* list) {
    if (!list)
        return;

    for (size_t i = 0; i < list->size; ++i) {
        Node* tmpHeadNext = list->head->next;
        delete_node(list->head);
        list->head = tmpHeadNext;
    }

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

void delete_list(LinkedList* list) {
    if (!list)
        return;
    erase_list(list);
    free(list);
}

LIST_TYPE pop_front_list(LinkedList* list) {
    if (!list || list->size < 1)
        return (LIST_TYPE)0;

    Node* res = list->head;


    list->head = res->next;
    --list->size;

    return res->data;
}

LIST_TYPE pop_back_list(LinkedList* list) {
    if (!list || list->size < 1)
        return (LIST_TYPE)0;

    Node* res = list->tail;


    list->tail = res->prev;
    --list->size;


    return res->data;
}

void insert_at_list(LinkedList* list, size_t index, LIST_TYPE value) {
    if (!list || index < 0 || index > list->size - 1) {
        return;
    }

    Node* insertNode = create_node(value);
    Node* curNode = list->head;

    /* edge cases */
    if (index == 0) {
        push_front_list(list, value);
        return;
    } else if (index == list->size - 1) {
        push_back_list(list, value);
        return;
    }
    /* head -> 0 - 1 - 2 */
    /*         ^ мы будем здесь (index 1) привяжем prev1 (next0 prev) к nextVal, next0 к Val */
    for (size_t i = 0; i < index; ++i) {
        curNode = curNode->next;
    }
    /* связь между новой и след после нее */
    curNode->next->prev = insertNode;
    insertNode->next = curNode->next;


    /* ... до нее */
    curNode->next = insertNode;
    insertNode->prev = curNode;

    ++list->size;
}

void delete_at_list(LinkedList* list, size_t index) {
    if (!list || index < 0 || index > list->size - 1) {
        return;
    }

    if (index == 0) {
        pop_front_list(list);
        return;
    } else if (index == list->size - 1) {
        pop_back_list(list);
        return;
    }

    Node* curNode = list->head;
    for (size_t i = 0; i < index; ++i) {
        curNode = curNode->next;
    }

    curNode->prev->next = curNode->next;
    curNode->next->prev = curNode->prev;

    delete_node(curNode);
    --list->size;
    return;
}

LIST_TYPE get_at_list(const LinkedList* list, size_t index) {
    if (!list || index < 0 || index > list->size - 1) {
        return (LIST_TYPE)0;
    }

    Node* curNode = list->head;

    for (size_t i = 0; i < index; ++i) {
        curNode = curNode->next;
    }

    return curNode->data;
}

int is_equal_list(const LinkedList* l1, const LinkedList* l2) {
    if (!l1 || !l2)
        return -2;

    size_t minSz = l1->size > l2->size ? l2->size : l1->size;

    Node* curL1 = l1->head;
    Node* curL2 = l2->head;
    for (size_t i = 0; i < minSz; ++i) {
        if (curL1->data > curL2->data) {
            return 1;
        } else if (curL1->data < curL2->data) {
            return -1;
        }
    }

    return (l1->size > l2->size) - (l1->size < l2->size);
}