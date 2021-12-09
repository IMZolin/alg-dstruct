#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUM_OPERATIONS 4
#define NUM_STR 30

typedef enum
{
	PLUS,
	MINUS, 
	MULTIPLY,
	DIVIDE
}opertions;
void PrintAnswer(char* str, char operator, int num);
int FindString(char* str, int result, int cur, int prev, int first_flag, char* answ);
void Result(int num1, int num2, char* answ);

int main() {
	FILE* f_input = fopen("input.txt", "r");
	FILE* f_output = fopen("output.txt", "w");
	char ans[60] = { 0 };
	int num1, num2;

	fscanf(f_input, "%d %d", &num1, &num2);
	Result(num1, num2, ans);
	fprintf(f_output, "%s", ans);
	return 0;
}

void PrintAnswer(char* str, char operator, int num) {
	char answ[NUM_STR] = { 0 };
	sprintf(answ, "%c%i", operator, num);
	char* ans_tmp = answ;
	for (; *ans_tmp != '\0'; *str++ = *ans_tmp++);
}
int FindString(char* str, int result, int cur, int prev, int first_flag, char* answ) {
	if (strlen(str) == 0)
		return cur + prev;

	for (int i = 1 + ((first_flag && *str == '-') ? 1 : 0); i <= strlen(str); i++) {
		int num;
		char buf[NUM_STR] = { 0 };
		char* p_str1 = buf;
		char* p_str2 = str;

		for (int k = 0; k < i; k++)
			*p_str1++ = *p_str2++;

		sscanf(buf, "%i", &num);


		for (int k = 0; k < NUM_OPERATIONS; k++) {
			int operator = k;
			if (first_flag) {
				operator = 0;
			}

			switch (operator) {
			case PLUS:
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

			case MULTIPLY:
				if (FindString(str + i, result, cur, prev * num, 0, answ + i + 1) == result) {
					PrintAnswer(answ, '*', num);
					return result;
				}
				break;

			case DIVIDE:
				if ((prev % num == 0) && (FindString(str + i, result, cur, prev / num, 0, answ + i + 1) == result)) {
					PrintAnswer(answ, '/', num);
					return result;
				}
				break;
			}
		}
	}
	return 0;
}



void Result(int num1, int num2, char* answ) {
	char data[NUM_STR] = { 0 };
	sprintf(data, "%d", num1);
	if (FindString(data, num2, 0, 0, 1, answ) == num2)
		memcpy(answ, answ + 1, strlen(answ));
	else
		sprintf(answ, "%d", 0);
}

