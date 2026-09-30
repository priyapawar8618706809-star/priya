#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Push an element into stack */
void push(char ch)
{
    if (top < MAX - 1)
    {
        stack[++top] = ch;
    }
}

/* Pop an element from stack */
char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

/* Return precedence of operator */
int precedence(char ch)
{
    switch (ch)
    {
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

/* Reverse a string */
void reverse(char str[])
{
    int i, j;
    char temp;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

/* Convert infix to prefix */
void infixToPrefix(char infix[], char prefix[])
{
    char reversed[MAX];
    int i, j = 0;
    char ch;

    strcpy(reversed, infix);

    /* Reverse the infix expression */
    reverse(reversed);

    /* Change '(' to ')' and ')' to '(' */
    for (i = 0; reversed[i] != '\0'; i++)
    {
        if (reversed[i] == '(')
            reversed[i] = ')';

        else if (reversed[i] == ')')
            reversed[i] = '(';
    }

    top = -1;

    /* Convert reversed expression to postfix */
    for (i = 0; reversed[i] != '\0'; i++)
    {
        ch = reversed[i];

        /* If operand, add to output */
        if (isalnum(ch))
        {
            prefix[j++] = ch;
        }

        /* If opening parenthesis */
        else if (ch == '(')
        {
            push(ch);
        }

        /* If closing parenthesis */
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                prefix[j++] = pop();
            }

            if (top != -1)
                pop();
        }

        /* If operator */
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) > precedence(ch))
            {
                prefix[j++] = pop();
            }

            push(ch);
        }
    }

    /* Pop remaining operators */
    while (top != -1)
    {
        prefix[j++] = pop();
    }

    prefix[j] = '\0';

    /* Reverse postfix to get prefix */
    reverse(prefix);
}

int main()
{
    char infix[MAX];
    char prefix[MAX];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);

    printf("Prefix expression: %s\n", prefix);

    return 0;
}