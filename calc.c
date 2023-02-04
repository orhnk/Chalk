/*
 * Doc: calc.c
 * Explanation: a real calculator engine depending on math rules (e.g first calc
 * powers) Author: KoBruhh Date: 29.01.2023 Extra: I am coding this from a
 * mobile phone so it is kinda wierd.
 * */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char symb_list[] = {'+', '-', '/', '*', '^', '(', ')'};

void get_input(char* buff);
double calc(char* eq);
double single(char* ex);

int main() {
  char eq[100] = {0};
  do {
    /* 3x(4+7-1)x2-2/2 */
    printf("Eq: ");
    get_input(eq);
    double res = calc(eq);
    printf("Result: %lf\n", res);
    // double sres = single("1234*5678");
  } while (1);
  return 0;
}

void parse(char* eq, char* res);
double calculate(char* eq);

double calc(char* eq) {
  /* this has to obey math rules
   * first calculate powers,
   * next parantheses,
   * then multiplication and division (right to left)
   * last addition and substraction (" ")
   * */
  //	char parsed[100] = { 0 };
  //	//parsed = parse(eq);
  //	parse(eq, parsed);
  //	printf("\nparsed: %s\n", eq);
  double res = calculate("3*5-2/2+1-3");  // 2 -> (1*2)-(3/3)+1
  printf("\ncalc in: %lf\n", res);
}

static int idx = 0;
void parse(char* eq, char* res) {
  // char buff[];
  //  1(2(3)4)5
  int brac = 0;
  int seg = 0;
  bool first = true;
  int len = strlen(eq);
  for (int i = 0; i < len; i++) {
    if (eq[i] == '(') {
      brac++;
      seg = i;	// index of our last opening brace
      printf("\nsegment: %i\n", seg);
    }

    // xxx(???
    //		if(brac >= 1 && first) // if in the first brace
    //		{
    //			for (int k = 0; k<i; k++){
    //				res[idx] =  eq[k];
    //				idx++;
    //			}
    //			first = false;
    //		}
    // some(another(stuff)here)now
    if (eq[i] == ')') {
      /* now we can say that from seg to i,
       * it was inside of braces*/
      brac--;
      for (int j = seg + 1; j < i; j++) {
	res[idx] = eq[j];
	eq[j - 1] = '_';
	idx++;
      }
      eq[i - 1] = '_';
      eq[i] = '_';  // getting rid of the "?)"

      double calc = calculate(res);
      printf("\ninner clac:%lf", calc);
      parse(eq, res);
      idx = 0;
      return;
      // return parse(res);
      // printf("\n");
    }
    //		if(!first && brac == 0) // this leads error in case of: ()()
    //			{
    //				for(int j=i+1;j<len;j++){
    //					printf("%c", eq[i]);
    //				}
    //			}
  }
  //	if(brac%2 != 0) {
  //		printf("please enter a valid equation!\n");
  //	}
  printf("\n%s", res);
  // return res;
}
char list[] = {'/', '*', '+', '-'};

double calculate(char* eq) {  // especially this fn dont have to parse braces
  /* 3*5-2/2+1-3 */
  // first check for multiplication and division
  // and addition substraction
  int len = strlen(eq);
  int last_symb = -1;  // no symbol by start so indx starts from 0
  int next = -1;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      // if any symbol it is next
      for (int k = 0; k < sizeof(list) / sizeof(char); k++) {
	if (eq[j] == list[k]) {
	  next = j;  // used to be i
	  goto evalmd;
	}
      }
    }
    next = -1;
  evalmd:  // mutliplication + division
    if (eq[i] == '/' || eq[i] == '*') {
      if (next != -1) {
	for (int j = last_symb + 1; j < next; j++) {
	  printf("%c", eq[j]);	//
	}
      } else {
	for (int j = last_symb + 1; j < len; j++) {
	  printf("%c", eq[j]);	//
	}
      }
      last_symb = i;
    }
    //		evalas://addition + substraction
    if (eq[i] == '+' || eq[i] == '-') {
      //				if(next != -1){
      //					for(int
      //j=last_symb+1;j<next;j++){ 						printf("%c", eq[j]);//
      //					}
      //				} else {
      //					for(int
      //j=last_symb+1;j<len;j++){ 						printf("%c", eq[j]);//
      //					}
      //				}
      last_symb = i;
    }
  }
}

double single(char* ex) {  // this represents a single expression. like 3*7 but
			   // it could be anything!
  char left[100] = {0}, right[100] = {0};
  char exp;
  int len = strlen(ex);
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < sizeof(symb_list) / sizeof(char); j++) {
      if (ex[i] == symb_list[j]) {
	for (int k = 0; k < i; k++) {
	  left[k] = ex[k];
	  printf("%c", ex[k]);
	  //					switch(symb_list[j]){
	  //						case '+':
	  //					}
	}
	printf(" ");
	for (int k = i + 1; k < len; k++) {
	  right[k - i - 1] = ex[k];
	  printf("%c", ex[k]);
	}
	exp = ex[i];
	goto casting;
      }
    }
  }
casting:
  printf("\nleft: %s\nright: %s\nexpression: %c\n", left, right, exp);
  int nleft = atoi(left);
  int nright = atoi(right);
  int result = 0;
  switch (exp) {
    case '+':
      result = nleft + nright;
      break;
    case '-':
      result = nleft - nright;
      break;
    case '*':
      result = nleft * nright;
      break;
    case '/':
      result = nleft / nright;
      break;
      //			case '+':
      //				result = nleft+nright;
      //				break;
  }
  printf("general result: %i\n", result);
  return 0;
}

void get_input(char* buff) {
  int len = strlen(buff);
  // fgets(buff,len,stdin);
  scanf("%s", buff);
  buff[strcspn(buff, "\n")] = '\0';
}
// karuso
// boh rap
// halelua
// still lovin yu
// traveller
// shine on you crazy diamond
// show must go on
