//ex4_5.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

double showLastElement(void);
void dublicateLast(void);
void skipLine(void);
void swap(void);
void cleanStack(void);
void stats(void);

int num_counter = 0;
int sp = 0;

int main(void) {

	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				printf("in NUMBER\n");
				push(atof(s));
				num_counter++;
				break;
			case '+':
				push(pop() + pop());
				--num_counter;
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				--num_counter;
				printf("sp == %d\n", sp);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("[INFO]: error: divide by zero\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0)
					push((int)pop() % (int)op2);
				else
					printf("[INFO]: error: divide by zero\n");
				break;
			case '\n':
				printf("in \\n\n");
				printf("\t%.8g\n", showLastElement());
				printf("------------------------\n");
				break;
			case 'l':
				printf("Last element is %.8g\n"
				"------------------------\n", showLastElement());
				skipLine();
				break;
			case 'd': 
				dublicateLast();
				num_counter++;
				break;
			case 's': //Swaps last two elements
				swap();
				break;
			case 'c': 
				cleanStack();
				break;
			case 't':
				stats();
				break;
			case 'n':
				push(sin(pop()));
				break;
			case 'p':
				op2 = pop();
				push(pow(pop(),op2));
				break;
			case 'e': 
				push(exp(pop()));
				break;
			default:
				printf("[INFO]: error: unknown operation %s\n", s);
		}
	}
	return 0;
}

#define MAXVAL 100

//int sp = 0;
double val[MAXVAL]; //Stack

void push(double f) {
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		printf("[INFO]: error: stack is full, %g does not fit\n", f);
}

double pop(void) {
	if(sp > 0)
		return val[--sp];
	else {
		printf("[INFO]: error: stack is empty\n");
		return 0.0;
	}
}

int getop(char s[]) {
	int i, c;
	i = 0;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.' && c != '-') {
		return c; //should be an operator or \n
	}
	if(c == '-') {
		if(num_counter != 0 && num_counter % 2 == 0)
			return c;
	}
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	printf("in ungetch\n");
	if(bufp >= BUFSIZE)
		printf("[INFO]: ungetch: too many characters\n");
	else 
		buf[bufp++] = c;
}

double showLastElement(void) {
	int last = sp-1;
	if(sp > 0) {
		return val[last];
	}
	else {
		printf("\n[INFO]: There`s no last element because "
			"Stack is empty\n");
		return 0.0;
	}
}

void dublicateLast(void) {
	if(sp < 1) printf("Cannot dublicate last element\n"
				"The stack is empty\n");
	else if(sp == MAXVAL) 
		printf("Cannot dublicate last element\n"
			"The stack is full\n");
	else {
		val[sp] = val[sp-1];
		sp++;
	}
}

void swap(void) {
	double temp;
	if(sp < 2) printf("Not enough elements to swap\n");
	temp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = temp;
}

void skipLine(void) {
	while(getchar() != '\n') continue;
}

void cleanStack(void) {
	sp = 0;
}

void stats(void) {
	printf("num_counter == %d\n"
			"sp == %d\n"
			"bufp == %d\n",num_counter,sp,bufp);
}