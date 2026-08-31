#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int values[MAX];
char operators[MAX];
int vtop=-1, otop=-1;

int precedence(char op){
    if (op=='*' || op=='/')
        return 2;
    if (op=='+' || op=='-')
        return 1;
    return 0;
}

void applyOperator(){
    int b=values[vtop--];
    int a=values[vtop--];
    char op=operators[otop--];

    int result;

    switch (op){
        case '+':
            result=a+b;
            break;
        case '-':
            result=a-b;
            break;
        case '*':
            result=a*b;
            break;
        case '/':
            result=a/b;
            break;
    }

    values[++vtop]=result;
}

int evaluate(char *expr){
    int i=0;
    while (expr[i] != '\0'){
        if (isspace(expr[i])){
            i++;
            continue;
        }

        if (isdigit(expr[i])){
            int num=0;
            while (isdigit(expr[i])){
                num=num*10+(expr[i]-'0');
                i++;
            }

            values[++vtop]=num;
        }

        else if (expr[i]=='('){
            operators[++otop]=expr[i];
            i++;
        }

        else if (expr[i]==')'){
            while (otop>=0 && operators[otop]!='(')
                applyOperator();
            otop--;  
            i++;
        }

        else if (expr[i]=='+' || expr[i]=='-' || expr[i]=='*' || expr[i]=='/'){
            while (otop>=0 &&
                   operators[otop]!='(' &&
                   precedence(operators[otop])>=precedence(expr[i])){
                applyOperator();
            }
            operators[++otop]=expr[i];
            i++;
        }
        else{
            printf("Invalid character: %c\n", expr[i]);
            exit(1);
        }
    }

    while (otop >= 0)
        applyOperator();
    return values[vtop];
}

int main(){
    char expression[MAX];
    printf("$ ");
    fgets(expression,MAX,stdin);
    int result=evaluate(expression);
    printf("%d\n", result);
    return 0;
}