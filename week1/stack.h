
struct node {
    int value;
    struct node * next;
};

struct stack {
    unsigned int size;
    struct node * head;
};

int peek(struct stack * st);

int push(struct stack * st, int data);

int pop(struct stack * st);

int empty(struct stack * st);

void display(struct stack * st);

int create(struct stack * st);

int stack_size(struct stack * st);
