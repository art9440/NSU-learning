#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"
#include <math.h>

#define MAX_SIZE 1001

int isoperand(char sym){
    char operation[6] = "+-/*";
    if (strchr(operation, sym) == NULL)
        return 0;
    return 1;
}


int priority(char sym){
    switch (sym) {
        case '+':
        case '-':
            return 3;
        case '*':
        case '/':
            return 4;
        case '(':
            return 1;
        case ')':
            return 2;
        default:
            return 0;
    }
}


char* PostFixPolka(char *calc_str, STACK * calculator){  //from infix
    char *post_calc_str;                                 //to postfix record
    int calc_len = strlen(calc_str);
    post_calc_str = (char *) malloc((calc_len+1) * sizeof(char));
    int k_num = 0;
    char symbol;

    if (isoperand(calc_str[0]))
        return "syntax error";

    int bracket_lf = 0;
    int bracket_rg = 0;

    for (int i = 0; i < calc_len; i++) {

        if (isdigit(calc_str[i])) {
            post_calc_str[k_num++] = calc_str[i];
            post_calc_str = (char *)realloc(post_calc_str,
                                            (strlen(post_calc_str) +1)
                                            * sizeof(char));
        }

        else if (isoperand(calc_str[i]) || calc_str[i] == '('
                 || calc_str[i] == ')') {
            if (calc_str[i] == '(')
                bracket_lf++;

            if (calc_str[i] == ')')
                bracket_rg++;

            if (bracket_rg > bracket_lf)
                return "syntax error";
            if (calc_str[i - 1] == '(' && calc_str[i] == ')')
                return "syntax error";
            if (isoperand(calc_str[i -1]) && isoperand(calc_str[i]))
                return "syntax error";
            if (isoperand(calc_str[i]) && calc_str[i+1] == '\0')
                return "syntax error";

            if (i != 0 && post_calc_str[k_num-1] != ' ') {
                post_calc_str[k_num++] = ' ';
                post_calc_str = (char *)realloc(post_calc_str,
                                                (strlen(post_calc_str) +1)
                                                * sizeof(char));
            }

            if (empty(calculator))
                push(calculator, create(calc_str[i]));

            else
            {
                if (calc_str[i] == '(')
                    push(calculator, create(calc_str[i]));


                else if (calc_str[i] == ')') {
                    symbol = (char) pop(calculator);

                    while (symbol != '(') {
                        post_calc_str[k_num++] = symbol;
                        post_calc_str =(char*)realloc(post_calc_str,
                                                      (strlen(post_calc_str)+1)
                                                      * sizeof(char));
                        symbol = (char) pop(calculator);
                    }
                }

                else if(priority(calc_str[i]) >priority((char)get(calculator)))
                    push(calculator, create(calc_str[i]));

                else {
                    while (priority(calc_str[i]) <=
                           priority((char) get(calculator))){
                        post_calc_str[k_num++] = (char) pop(calculator);
                        post_calc_str =(char*)realloc(post_calc_str,
                                                      (strlen(post_calc_str)+1)
                                                      * sizeof(char));
                    }
                    push(calculator, create(calc_str[i]));
                }
            }
        }
        else
            return "syntax error";
    }

    while (!empty(calculator)) {
        post_calc_str[k_num++] = (char) pop(calculator);
        post_calc_str = (char*)realloc(post_calc_str,
                                       (strlen(post_calc_str)+1)
                                       * sizeof(char));
    }

    if (strlen(post_calc_str) == 0)
        return "syntax error";
    if (bracket_lf != bracket_rg)
        return "syntax error";


    post_calc_str[k_num] = '\0';
    return post_calc_str;
}


void calculating(char*post_calc_str, STACK * calculator){ //calculating
    int post_calc_len = strlen(post_calc_str);        //postfix record
    char *number = (char*)malloc( sizeof (char));
    int num_len = 0;
    for (int i = 0;i < post_calc_len;i++){
        if (isdigit(post_calc_str[i])) {
            number[num_len++] = post_calc_str[i];
            number[num_len] = '\0';
        }

        if (num_len == post_calc_len) {
            printf("%s", number);
            exit(0);
        }

        if (isoperand(post_calc_str[i]) || post_calc_str[i] == ' '){
            int putin = 0;
            int raz = 0;
            for (int j = num_len - 1; j > -1;j--){
                int cur = (number[j]) - '0';
                putin += cur * pow(10, raz);
                raz++;
            }
            if (num_len != 0) {

                push(calculator, create(putin));

                for (int k = 0; k < num_len; k++)
                    number[k] = '\0';
                num_len = 0;
            }

            if (isoperand(post_calc_str[i])){
                int total;
                if (post_calc_str[i] == '+') {
                    total = pop(calculator) + pop(calculator);
                    push(calculator, create(total));
                }
                if(post_calc_str[i] == '-') {
                    int second = pop(calculator);
                    int first = pop(calculator);

                    total = first - second;
                    push(calculator, create(total));
                }
                if(post_calc_str[i] == '*'){
                    total = pop(calculator) * pop(calculator);
                    push(calculator, create(total));
                }
                if(post_calc_str[i] == '/'){
                    int second = pop(calculator);
                    int first = pop(calculator);
                    if (second == 0){
                        printf("%s", "division by zero");
                        return;
                    }
                    total = first / second;
                    push(calculator, create(total));
                }
            }
        }
    }
    printf("%d\n", pop(calculator));
}


int checkForError(char* calc_str){       //checking for existing of numbers
    for (int i = 0;i < strlen(calc_str); i++){
        if (isdigit(calc_str[i]))
            return 1;
    }
    return 0;
}


int main(){
    char *calc_str;
    STACK * calculator;
    calculator = create(0);
    calc_str = (char*)malloc(MAX_SIZE * sizeof(char));
    gets(calc_str);

    if (checkForError(calc_str) == 0){
        printf("%s", "syntax error");
        return 0;
    }

    char* post_calc_str = PostFixPolka(calc_str, calculator);
    if (strcmp(post_calc_str, "syntax error") == 0){
        printf("%s", "syntax error");
        return 0;
    }

    calculating(post_calc_str, calculator);

    free(post_calc_str);
    free(calc_str);

    return 0;
}
