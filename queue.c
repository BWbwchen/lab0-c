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
    q->head = NULL;
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
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
        q->size = 1;
    } else {
        newh->next = q->head;
        q->head = newh;
        q->size++;
    }

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
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
