//queue using 2 stacks -> dequeue costly
#include <stdio.h>

#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

void push1(int x) {
    stack1[++top1] = x;
}

int pop1() {
    return stack1[top1--];
}

void push2(int x) {
    stack2[++top2] = x;
}

int pop2() {
    return stack2[top2--];
}

void enqueue(int x) {
    push1(x);
    printf("%d inserted\n", x);
}

void dequeue() {
    int x;

    if (top1 == -1) {
        printf("Queue Underflow\n");
        return;
    }

    while (top1 != -1)
        push2(pop1());

    x = pop2();

    while (top2 != -1)
        push1(pop2());

    printf("%d deleted\n", x);
}

void display() {
    int i;

    if (top1 == -1) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    for (i = 0; i <= top1; i++)
        printf("%d ", stack1[i]);

    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
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