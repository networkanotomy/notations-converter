#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

int isOperand(char ch) {
    return isalnum(ch);
}

int isOperator(char ch) {
    switch(ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return 1;
        default:
            return 0;
    }
}

int precedence(char ch) {
    switch(ch) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void reverseString(char *str) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    char temp[MAX_LENGTH];
    int i, j = 0, top = -1;

    for (i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            temp[++top] = infix[i];
        }
        else if (isOperator(infix[i])) {
            while (top != -1 && temp[top] != '(' && precedence(temp[top]) >= precedence(infix[i])) {
                postfix[j++] = temp[top--];
            }
            temp[++top] = infix[i];
        }
        else if (infix[i] == ')') {
            while (top != -1 && temp[top] != '(') {
                postfix[j++] = temp[top--];
            }
            top--;
        }
    }

    while (top != -1 && temp[top] != '(') {
        postfix[j++] = temp[top--];
    }
    postfix[j] = '\0';
}

void infixToPrefix(char *infix, char *prefix) {
    char temp[MAX_LENGTH];
    int i, j = 0, top = -1;
    reverseString(infix);

    for (i = 0; infix[i] != '\0'; i++) {
        if (isOperand(infix[i])) {
            prefix[j++] = infix[i];
        }
        else if (infix[i] == ')') {
            temp[++top] = infix[i];
        }
        else if (isOperator(infix[i])) {
            while (top != -1 && precedence(temp[top]) >= precedence(infix[i])) {
                prefix[j++] = temp[top--];
            }
            temp[++top] = infix[i];
        }
        else if (infix[i] == '(') {
            while (temp[top] != ')') {
                prefix[j++] = temp[top--];
            }
            top--;
        }
    }

    while (top != -1) {
        prefix[j++] = temp[top--];
    }
    prefix[j] = '\0';
    reverseString(prefix);
}
int main() {
    char infix[MAX_LENGTH], postfix[MAX_LENGTH], prefix[MAX_LENGTH];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);
    return 0;
}
  
 

