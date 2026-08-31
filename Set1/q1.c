#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top=-1;

void push(char c){
    stack[++top]=c;
}

char pop(){
    return stack[top--];
}

char peek(){
    return stack[top];
}

int precedence(char op){
    if (op=='/' || op=='*')
        return 2;
    if (op=='+' || op=='-')
        return 1;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]){
    int i=0, j=0;
    char ch;

    while (infix[i]!='\0'){
        ch=infix[i];
        if (isdigit(ch)){
            postfix[j++]=ch;
        }

        else if (ch=='('){
            push(ch);
        }

        else if (ch==')'){
            while (top!=-1 && peek()!='('){
                postfix[j++]=pop();
            }
            pop();  
        }

        else if (ch=='+' || ch=='-' || ch=='*' || ch=='/'){

            while (top!=-1 &&
                   peek()!='(' &&
                   precedence(peek())>=precedence(ch)){
                postfix[j++]=pop();
            }

            push(ch);
        }

        i++;
    }

    while (top!=-1){
        postfix[j++]=pop();
    }

    postfix[j]='\0';
}

int main(){
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix,postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}