#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>

#ifndef LIST_TYPE
#error "LIST_TYPE must be defined before including linked-list.h. Example: #define LIST_TYPE int"
#endif

#define LINKED_LIST(LIST_TYPE)                                                                      \
    typedef struct Node {                                                                           \
        LIST_TYPE data;                                                                             \
        struct Node* prev;                                                                          \
        struct Node* next;                                                                          \
    } Node;                                                                                         \
                                                                                                    \
    typedef struct {                                                                                \
        Node* head;                                                                                 \
        Node* tail;                                                                                 \
        size_t size;                                                                                \
    } LinkedList;                                                                                   \
                                                                                                    \
    static inline Node* create_node(LIST_TYPE val) {                                                \
        Node* node = (Node*)malloc(sizeof(Node));                                                   \
        if (!node)                                                                                  \
            return NULL;                                                                            \
                                                                                                    \
        node->data = val;                                                                           \
        node->prev = NULL;                                                                          \
        node->next = NULL;                                                                          \
        return node;                                                                                \
    }                                                                                               \
                                                                                                    \
    static inline void delete_node(Node* node) {                                                    \
        if (!node)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        free(node);                                                                                 \
    }                                                                                               \
                                                                                                    \
    LinkedList create_list(void) {                                                                  \
        LinkedList list = {                                                                         \
            .head = NULL,                                                                           \
            .tail = NULL,                                                                           \
            .size = 0,                                                                              \
        };                                                                                          \
                                                                                                    \
        return list;                                                                                \
    }                                                                                               \
                                                                                                    \
    void push_front_list(LinkedList* list, LIST_TYPE value) {                                       \
        if (!list)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        Node* node = create_node(value);                                                            \
        if (!node)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        node->next = list->head;                                                                    \
        node->prev = NULL;                                                                          \
                                                                                                    \
        if (list->head) {                                                                           \
            list->head->prev = node;                                                                \
        } else {                                                                                    \
            list->tail = node;                                                                      \
        }                                                                                           \
                                                                                                    \
        list->head = node;                                                                          \
        ++list->size;                                                                               \
    }                                                                                               \
                                                                                                    \
    void push_back_list(LinkedList* list, LIST_TYPE value) {                                        \
        if (!list)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        Node* node = create_node(value);                                                            \
        if (!node)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        node->next = NULL;                                                                          \
        node->prev = list->tail;                                                                    \
                                                                                                    \
        if (list->tail) {                                                                           \
            list->tail->next = node;                                                                \
        } else {                                                                                    \
            list->head = node;                                                                      \
        }                                                                                           \
                                                                                                    \
        list->tail = node;                                                                          \
        ++list->size;                                                                               \
    }                                                                                               \
                                                                                                    \
    void erase_list(LinkedList* list) {                                                             \
        if (!list)                                                                                  \
            return;                                                                                 \
                                                                                                    \
        Node* current = list->head;                                                                 \
        while (current) {                                                                           \
            Node* next = current->next;                                                             \
            delete_node(current);                                                                   \
            current = next;                                                                         \
        }                                                                                           \
                                                                                                    \
        list->size = 0;                                                                             \
        list->head = NULL;                                                                          \
        list->tail = NULL;                                                                          \
    }                                                                                               \
                                                                                                    \
    void delete_list(LinkedList* list) {                                                            \
        if (!list)                                                                                  \
            return;                                                                                 \
        erase_list(list);                                                                           \
        free(list);                                                                                 \
    }                                                                                               \
                                                                                                    \
    LIST_TYPE pop_front_list(LinkedList* list) {                                                    \
        if (!list || list->size < 1)                                                                \
            return (LIST_TYPE)0;                                                                    \
                                                                                                    \
        Node* res = list->head;                                                                     \
        LIST_TYPE data = res->data;                                                                 \
                                                                                                    \
        list->head = res->next;                                                                     \
        if (list->head) {                                                                           \
            list->head->prev = NULL;                                                                \
        } else {                                                                                    \
            list->tail = NULL;                                                                      \
        }                                                                                           \
                                                                                                    \
        delete_node(res);                                                                           \
        --list->size;                                                                               \
                                                                                                    \
        return data;                                                                                \
    }                                                                                               \
                                                                                                    \
    LIST_TYPE pop_back_list(LinkedList* list) {                                                     \
        if (!list || list->size < 1)                                                                \
            return (LIST_TYPE)0;                                                                    \
                                                                                                    \
        Node* res = list->tail;                                                                     \
        LIST_TYPE data = res->data;                                                                 \
                                                                                                    \
        list->tail = res->prev;                                                                     \
        if (list->tail) {                                                                           \
            list->tail->next = NULL;                                                                \
        } else {                                                                                    \
            list->head = NULL;                                                                      \
        }                                                                                           \
                                                                                                    \
        delete_node(res);                                                                           \
        --list->size;                                                                               \
                                                                                                    \
        return data;                                                                                \
    }                                                                                               \
                                                                                                    \
    void insert_at_list(LinkedList* list, size_t index, LIST_TYPE value) {                          \
        if (!list || index > list->size) {                                                          \
            return;                                                                                 \
        }                                                                                           \
                                                                                                    \
        if (index == 0) {                                                                           \
            push_front_list(list, value);                                                           \
            return;                                                                                 \
        } else if (index == list->size) {                                                           \
            push_back_list(list, value);                                                            \
            return;                                                                                 \
        }                                                                                           \
                                                                                                    \
        Node* insertNode = create_node(value);                                                      \
        if (!insertNode)                                                                            \
            return;                                                                                 \
                                                                                                    \
        Node* curNode = list->head;                                                                 \
        for (size_t i = 0; i < index; ++i) {                                                        \
            curNode = curNode->next;                                                                \
        }                                                                                           \
                                                                                                    \
        insertNode->next = curNode;                                                                 \
        insertNode->prev = curNode->prev;                                                           \
                                                                                                    \
        if (curNode->prev) {                                                                        \
            curNode->prev->next = insertNode;                                                       \
        }                                                                                           \
        curNode->prev = insertNode;                                                                 \
                                                                                                    \
        ++list->size;                                                                               \
    }                                                                                               \
                                                                                                    \
    void delete_at_list(LinkedList* list, size_t index) {                                           \
        if (!list || index >= list->size) {                                                         \
            return;                                                                                 \
        }                                                                                           \
                                                                                                    \
        if (index == 0) {                                                                           \
            pop_front_list(list);                                                                   \
            return;                                                                                 \
        } else if (index == list->size - 1) {                                                       \
            pop_back_list(list);                                                                    \
            return;                                                                                 \
        }                                                                                           \
                                                                                                    \
        Node* curNode = list->head;                                                                 \
        for (size_t i = 0; i < index; ++i) {                                                        \
            curNode = curNode->next;                                                                \
        }                                                                                           \
                                                                                                    \
        curNode->prev->next = curNode->next;                                                        \
        curNode->next->prev = curNode->prev;                                                        \
                                                                                                    \
        delete_node(curNode);                                                                       \
        --list->size;                                                                               \
    }                                                                                               \
                                                                                                    \
    LIST_TYPE get_at_list(const LinkedList* list, size_t index) {                                   \
        if (!list || index >= list->size) {                                                         \
            return (LIST_TYPE)0;                                                                    \
        }                                                                                           \
                                                                                                    \
        Node* curNode = list->head;                                                                 \
                                                                                                    \
        for (size_t i = 0; i < index; ++i) {                                                        \
            curNode = curNode->next;                                                                \
        }                                                                                           \
                                                                                                    \
        return curNode->data;                                                                       \
    }                                                                                               \
                                                                                                    \
    int is_equal_list(const LinkedList* l1, const LinkedList* l2) {                                 \
        if (!l1 || !l2)                                                                             \
            return -2;                                                                              \
                                                                                                    \
        size_t minSz = l1->size > l2->size ? l2->size : l1->size;                                   \
                                                                                                    \
        Node* curL1 = l1->head;                                                                     \
        Node* curL2 = l2->head;                                                                     \
        for (size_t i = 0; i < minSz; ++i) {                                                        \
            if (curL1->data > curL2->data) {                                                        \
                return 1;                                                                           \
            } else if (curL1->data < curL2->data) {                                                 \
                return -1;                                                                          \
            }                                                                                       \
            curL1 = curL1->next;                                                                    \
            curL2 = curL2->next;                                                                    \
        }                                                                                           \
                                                                                                    \
        return (l1->size > l2->size) - (l1->size < l2->size);                                       \
    }                                                                                               \
                                                                                                    \
    static inline void push_stack(LinkedList* stack, LIST_TYPE value) {                             \
        push_front_list(stack, value);                                                              \
    }                                                                                               \
    static inline LIST_TYPE pop_stack(LinkedList* stack) {                                          \
        return pop_front_list(stack);                                                               \
    }                                                                                               \
                                                                                                    \
    static inline LIST_TYPE peek_stack(const LinkedList* stack) {                                   \
        return get_at_list(stack, 0);                                                               \
    }                                                                                               \
                                                                                                    \
                                                                                                    \
    static inline void enqueue(LinkedList* queue, LIST_TYPE value) {                                \
        push_front_list(queue, value);                                                              \
    }                                                                                               \
    static inline LIST_TYPE dequeue(LinkedList* queue) {                                            \
        return pop_back_list(queue);                                                                \
    }                                                                                               \
    static inline LIST_TYPE peek_queue(const LinkedList* queue) {                                   \
        return get_at_list(queue, queue->size - 1);                                                 \
    }

#endif