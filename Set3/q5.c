//Stack using 2 queue-> push costly
#include <stdio.h>

#define MAX 100

int q1[MAX], q2[MAX];
int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

void enqueue1(int x) {
    q1[++rear1] = x;
}

int dequeue1() {
    return q1[front1++];
}

void enqueue2(int x) {
    q2[++rear2] = x;
}

int dequeue2() {
    return q2[front2++];
}

void push(int x) {
    while (front1 <= rear1)
        enqueue2(dequeue1());

    enqueue1(x);

    while (front2 <= rear2)
        enqueue1(dequeue2());

    front2 = 0;
    rear2 = -1;

    printf("%d pushed\n", x);
}

void pop() {
    if (front1 > rear1) {
        printf("Stack Underflow\n");
        return;
    }

    printf("%d popped\n", dequeue1());
}

void display() {
    int i;

    if (front1 > rear1) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");

    for (i = front1; i <= rear1; i++)
        printf("%d ", q1[i]);

    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}