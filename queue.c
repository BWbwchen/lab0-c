#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }

    strncpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = '\0';

    if (q->head == NULL) {
        q->tail = newh;
    }

    newh->next = q->head;
    q->head = newh;
    q->size++;


    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL)
        return false;

    list_ele_t *tmp;
    tmp = malloc(sizeof(list_ele_t));
    if (tmp == NULL)
        return false;

    tmp->next = NULL;
    tmp->value = malloc((strlen(s) + 1) * sizeof(char));
    if (tmp->value == NULL && strlen(s) != 0) {
        free(tmp);
        return false;
    }

    strncpy(tmp->value, s, strlen(s));
    tmp->value[strlen(s)] = '\0';

    if (q->tail == NULL) {
        q->head = tmp;
        q->tail = tmp;
        q->size = 1;
    } else {
        q->tail->next = tmp;
        q->tail = tmp;
        q->size++;
    }

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
        return false;

    if (sp != NULL) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    if (q->head->next == NULL) {
        free(q->head->value);
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return true;
    }

    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;
    q->size--;

    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return !q ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->size == 1)
        return;

    list_ele_t *pre = NULL, *now = q->head, *after = q->head->next;
    q->tail = q->head;

    while (after) {
        now->next = pre;
        pre = now;
        now = after;
        after = after->next;
    }

    now->next = pre;
    q->head = now;
}

list_ele_t *merge_list(list_ele_t *left, list_ele_t *right)
{
    // Merge
    list_ele_t *start = NULL;
    for (list_ele_t *merge = NULL; left || right;) {
        if (!right || (left && strcmp(left->value, right->value) < 0)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
    return start;
}

list_ele_t *get_mid(list_ele_t *start)
{
    if (start == NULL)
        return start;

    list_ele_t *slow = start, *fast = start;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

list_ele_t *merge_sort(list_ele_t *start)
{
    if (start == NULL || start->next == NULL)
        return start;

    list_ele_t *mid;
    mid = get_mid(start);
    list_ele_t *right = mid->next;
    mid->next = NULL;

    return merge_list(merge_sort(start), merge_sort(right));
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;

    q->head = merge_sort(q->head);
}
