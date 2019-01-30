#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "stack.h"

int client(int fds[]);
int server(int fds[]);

int main() {
	int fds[2];
	pipe(fds);	
	pid_t f = fork();
	if(!f) {
		int r = server(fds);
		if( r < 0) {
			fprintf(stderr, "Error: %s\n", errno);
			return -1;
		}
	}else if(f > 0) {
		client(fds);
	}else {
		fprintf(stderr,"Error: %s\n", errno);	
	}
}


int client(int fds[]) {
	for(;;) {
		char buf[32];
		scanf(" %[^\t\n]s",buf);
		write(fds[1], buf, 32);
	}
	return 0;
}

int server(int fds[]) {
    struct stack * st = malloc(sizeof(struct stack));
    create(st);
	for(;;) {
		char * buf = malloc(32);
		read(fds[0], buf, 32);
		char* command = buf;
		char* arg = "";
		for(int i = 0; i < 32; i++) {
			if(buf[i] == ' ' || buf[i] == '\n') {
				buf[i] = '\0';
				arg = buf+i+1;
				break;
			}
		}
        if(strcmp(command, "peek") == 0) {
            int v = peek(st);
            printf("SERVER: peeked %d\n", v);
        } else if(strcmp(command, "push") == 0) {
            int argument = atoi(arg);
            push(st, argument);
            printf("SERVER: pushed\n");
        } else if(strcmp(command, "pop") == 0) {
            int v = pop(st);
            printf("SERVER: poped %d\n", v);
        } else if(strcmp(command, "empty") == 0) {
            printf("SERVER: empty %s\n", !empty(st) ? "true" : "false");
        } else if(strcmp(command, "display") == 0) {
            display(st);
            printf("SERVER: displayed\n");
        } else if(strcmp(command, "create") == 0) {
            create(st);
            printf("SERVER: create\n");
        } else if(strcmp(command, "stack_size") == 0) {
            int size = stack_size(st);
            printf("SERVER: stack_size %d\n", size);
        } else {
            printf("SERVER: undefined command\n");
        }
	}
	return 0;
}
