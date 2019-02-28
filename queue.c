/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        list_ele_t *current = q->head;
        list_ele_t *next = NULL;
        for (; current != NULL; current = next) {
            if (current->value) {
                free(current->value);
                current->value = NULL;
            }
            next = current->next;
            // current -> next = NULL;
            free(current);
        }
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        free(q);
        q = NULL;
    }
    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    /* What if either call to malloc returns NULL? */
    if (!(newh->value)) {
        free(newh);
        newh = NULL;
        return false;
    }
    strcpy(newh->value, s);
    ++(q->size);
    // Insert to head
    newh->next = q->head;
    q->head = newh;
    // Check tail availability
    if (!(q->tail))
        q->tail = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    // Check NULL for q
    if (!q)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->value = malloc((strlen(s) + 1) * sizeof(char));
    if (!(newt->value)) {
        free(newt);
        newt = NULL;
        return false;
    }
    strcpy(newt->value, s);
    newt->next = NULL;
    ++(q->size);
    // Insert to tail
    if (q->tail)
        q->tail->next = newt;
    else  // No elements in q
        q->head = newt;
    q->tail = newt;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    // Check q and q -> head availability
    if (!q || !(q->head))
        return false;
    list_ele_t *temp = q->head;
    // Check sp and bufsize availability
    if (!sp && (temp->value) && bufsize) {
        strncpy(sp, temp->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
        // Release value memory
        free(temp->value);
        temp->value = NULL;
    }
    // Remove head
    q->head = q->head->next;
    // temp -> next = NULL;
    free(temp);
    temp = NULL;
    // Check if list is empty
    if (!(--(q->size)))
        q->tail = NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->size;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    // Check q availability
    if (!q || (q->size) <= 1)
        return;
    list_ele_t *prev = NULL;
    list_ele_t *current = q->tail = q->head;
    list_ele_t *next = current->next;
    for (; next != NULL; prev = current, current = next, next = current->next) {
        current->next = prev;
    }
    current->next = prev;
    q->head = current;
    return;
}
