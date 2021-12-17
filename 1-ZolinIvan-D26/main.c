#pragma warning(disable: 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"
#include "math.h"

#define NUM_OPERATIONS 4
#define CHAR_SIZE 300

// 0='+' 1='-' 2='*' 3='/'

enum
{
    SUM,
    MINUS,
    MUL,
    DIV
}operations;


void PrintAnswer(char* str, char operator, long long num) {
    char answ[CHAR_SIZE] = { 0 };
    sprintf(answ, "%c%i", operator, num);
    char* answ_tmp = answ;
    for (; *answ_tmp != '\0'; *str++ = *answ_tmp++);
}
static int FindString(char* str, long long result, long long cur, long long prev, int first_flag, char* answ) {
    if (strlen(str) == 0)
        return cur + prev;

    for (long long i = 1 + ((first_flag && *str == '-') ? 1 : 0); i <= strlen(str); i++) {
        long long num;
        char buf[CHAR_SIZE] = { 0 };
        char* p_str1 = buf;
        char* p_str2 = str;

        for (int k = 0; k < i; k++)
            *p_str1++ = *p_str2++;

        sscanf(buf, "%ld", &num);


        for (int k = 0; k < NUM_OPERATIONS; k++) {
            int operator = k;
            if (first_flag) {
                operator = 0;
            }

            switch (operator) {
            case SUM:
                if (FindString(str + i, result, cur + prev, num, 0, answ + i + 1) == result) {
                    PrintAnswer(answ, '+', num);
                    return result;
                }
                break;

            case MINUS:
                if (FindString(str + i, result, cur + prev, -num, 0, answ + i + 1) == result) {
                    PrintAnswer(answ, '-', num);
                    return result;
                }
                break;

            case MUL:
                if (FindString(str + i, result, cur, prev * num, 0, answ + i + 1) == result) {
                    PrintAnswer(answ, '*', num);
                    return result;
                }
                break;

            case DIV:
                if (num != 0) {
                    if ((prev % num == 0) && (FindString(str + i, result, cur, prev / num, 0, answ + i + 1) == result)) {
                        PrintAnswer(answ, '/', num);
                        return result;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}



void Result(long long input, long long result, char* answ) {
    char data[CHAR_SIZE] = { 0 };
    sprintf(data, "%lld", input);
    if (FindString(data, result, 0, 0, 1, answ) == result)
        memcpy(answ, answ + 1, strlen(answ));
    else
        sprintf(answ, "%d", 0);
}

int main() {
    FILE* f_input = fopen("input.txt", "r");
    FILE* f_output = fopen("output.txt", "w");
    char ans[600] = { 0 };
    long long num1, num2;

    fscanf(f_input, "%lld %lld", &num1, &num2);
    Result(num1, num2, ans);
    fprintf(f_output, "%s", ans);
    return 0;
}
