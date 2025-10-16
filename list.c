// parta.c
#include <stdlib.h>
#include <stdio.h>

struct ll_node {
    int data;
    struct ll_node *next;
};

/* ========= Part 1 ========= */
struct ll_node *ll_head(struct ll_node *head) {
    return head;
}

struct ll_node *ll_tail(struct ll_node *head) {
    if (!head) return NULL;
    while (head->next) head = head->next;
    return head;
}

int ll_size(struct ll_node *head) {
    int n = 0;
    for (; head; head = head->next) n++;
    return n;
}

/* ========= Part 2 ========= */
struct ll_node *ll_find(struct ll_node *head, int value) {
    for (; head; head = head->next) {
        if (head->data == value) return head;
    }
    return NULL;
}

/* ========= Part 3 ========= */
int *ll_toarray(struct ll_node *head) {
    int n = ll_size(head);
    if (n == 0) return NULL;
    int *arr = (int*)malloc(sizeof(int) * n);
    if (!arr) return NULL;  // allocation failure: let tests handle NULL
    for (int i = 0; i < n; i++, head = head->next) {
        arr[i] = head->data;
    }
    return arr; // caller (tests) will free()
}

/* ========= Part 4 ========= */
struct ll_node *ll_create(int data) {
    struct ll_node *node = (struct ll_node*)malloc(sizeof(struct ll_node));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

void ll_destroy(struct ll_node *head) {
    while (head) {
        struct ll_node *next = head->next;
        free(head);
        head = next;
    }
}

/* ========= Part 5 ========= */
void ll_append(struct ll_node *head, int data) {
    if (!head) return; // spec says append to existing list; no-op if NULL
    struct ll_node *tail = head;
    while (tail->next) tail = tail->next;

    struct ll_node *node = ll_create(data);
    if (!node) return; // allocation failure → leave list unchanged
    tail->next = node;
}

/* ========= Part 6 ========= */
struct ll_node *ll_fromarray(int *data, int len) {
    if (!data || len <= 0) return NULL;

    struct ll_node *head = ll_create(data[0]);
    if (!head) return NULL;

    struct ll_node *tail = head;
    for (int i = 1; i < len; i++) {
        struct ll_node *node = ll_create(data[i]);
        if (!node) {
            ll_destroy(head);  // clean up on partial allocation failure
            return NULL;
        }
        tail->next = node;
        tail = node;
    }
    return head;
}

/* ========= Part 7 ========= */
struct ll_node *ll_remove(struct ll_node *head, int value) {
    if (!head) return NULL;

    // If the head is the node to remove
    if (head->data == value) {
        struct ll_node *new_head = head->next;
        free(head);
        return new_head;
    }

    // Otherwise, find the node before the one to remove
    struct ll_node *prev = head;
    struct ll_node *curr = head->next;
    while (curr) {
        if (curr->data == value) {
            prev->next = curr->next;
            free(curr);
            return head; // head unchanged
        }
        prev = curr;
        curr = curr->next;
    }
    // Not found → return original head
    return head;
}
