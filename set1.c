#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Operator stack for infix to postfix
char opStack[1000];
int topOp = -1;

// Push operator
void pushOp(char c) {
    opStack[++topOp] = c;
}

// Pop operator
char popOp() {
    return opStack[topOp--];
}

// Precedence function
int precedence(char c) {
    if (c == '^') return 3;
    else if (c == '*' || c == '/') return 2;
    else if (c == '+' || c == '-') return 1;
    return -1;
}

// Operand stack for postfix evaluation
int valStack[1000];
int topVal = -1;

void pushVal(int n) {
    valStack[++topVal] = n;
}

int popVal() {
    return valStack[topVal--];
}

// Evaluate postfix expression
int postfixcalc(char postfix[]) {
    int i = 0, calc;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            pushVal(postfix[i++] - '0');   // store as integer
        } else {
            int op2 = popVal();
            int op1 = popVal();
            switch (postfix[i++]) {
                case '+': calc = op1 + op2; break;
                case '-': calc = op1 - op2; break;
                case '*': calc = op1 * op2; break;
                case '/': calc = op1 / op2; break;
                case '^': calc = pow(op1, op2); break;
                default: 
                    printf("\nInvalid operator\n");
                    return -1;
            }
            pushVal(calc);
        }
    }
    return popVal();
}

int main() {
    char infix[1000], postfix[1000];
    int i = 0, j = 0;

    printf("Enter the INFIX Expression: ");
    scanf("%s", infix);

    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i++];
        } else {
            if (topOp == -1) {
                pushOp(infix[i++]);
            } else if (precedence(opStack[topOp]) < precedence(infix[i])) {
                pushOp(infix[i++]);
            } else {
                while (topOp != -1 && precedence(opStack[topOp]) >= precedence(infix[i])) {
                    postfix[j++] = popOp();
                }
                pushOp(infix[i++]);
            }
        }
    }

    while (topOp != -1) {
        postfix[j++] = popOp();
    }
    postfix[j] = '\0';

    printf("The postfix of the given infix is : %s\n", postfix);
    int result = postfixcalc(postfix);
    printf("The result of POSTFIX expression is : %d\n", result);

    return 0;
}
