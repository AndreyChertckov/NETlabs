#include "stack.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int peek(struct stack * st) {
    if(st->head != NULL) {
        return st->head->value;
    } else {
        return -1;
    }
}

int push(struct stack * st, int data) {
    struct node *new = malloc(sizeof(struct node));
    new->value = data;
    new->next = st->head;
    st->head = new;
    st->size++;
    return 0;
}

int pop(struct stack * st) {
    if(st->head !=NULL) {
        struct node * temp = st->head;
        int value = temp->value;
        st->head = temp->next;
        free(temp);
        st->size--;
        return value;
    } else {
        return -1;
    }
}

int empty(struct stack * st) {
    return st->size;
}

void display(struct stack * st) {
    struct node * temp = st->head;
    while(temp != NULL) {
        printf("%d>", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int create(struct stack * st) {
    st->head = NULL;
    st->size = 0;
    return 0;
}

int stack_size(struct stack * st) {
    return st->size;
}
