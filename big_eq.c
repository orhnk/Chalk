#include "calc.c"
#include <stdio.h>

#define loop for(;;)
double bigmd(char* eq, int start);

int main() {
  // With these, I have to construct a function that returns: 7*7/3-4/4*4*4/3 = 1
  loop { 
    char input_buff[10];
    printf(">> ");
    get_input(input_buff);
    double result = bigmd(input_buff, 0);
    printf("Result of a big equation is: %lf\n", result);
  }
}

double bigmd(char* eq, int start) { // This only calculates multiplication and division
  // This is the function that will be called by the main function
  // It will take in a string and return a double
  // It will be able to handle
  // 1. Multiplication
  // 2. Division
  // 3. Addition
  // 4. Subtraction

  // Plan: Use recursion to solve this problem
  // 1. Find the first operator
  // 2. Find the first number before the operator
  // 3. Find the first number after the operator
  // 4. Perform the operation
  // 5. Replace the first number before the operator with the result
  // 6. Remove the operator and the number after the operator
  // 7. Repeat until there are no more operators

  extern const char symb_list[];
  int search_from = start;
  int i, j = 0; // while's body. j is initialized because it is used in the do-while first
  int len = strlen(eq);
  char sin_buff[100]; // single equation buffer
  int single_result;
  char former;

  // we have a next function that will return the next operator from an index
  do {
    /*search_from = j; // we know that the next symbol will be at least 2 characters away <- that was leading to error (cuz I decided to use recursion after)*/
    
    if (search_from != 0) {
      i = find_next_symbol(search_from, eq);
    } else {
      i = start; // if we are at the start of the string, we dont need to search for the next symbol
    }
    printf("i: %d, ", i);
      // finding the second symbol
      j = find_next_symbol(find_next_symbol(0,eq) + 1 /*This was symbol. 
                                                        ( We don't want to overlap it so starting from 
                                                        the next index)*/, eq); 

    if (j == -1) { // if we hit the end of the string)
      j = len;
    }

    printf("j: %d\n", j);
    // we know that the next symbol will be at least 2 characters away 
    // _? -> _ stands for symbol, ? is the next number 
    // (if not equation is wrong) I dont to validation =)

    if (i != 0) {
      print(eq, i - 1, j); // comes from calc.c (prints string slice)
      copy(eq, i - 1, j, sin_buff); // comes from calc.c (copies string slice to sin_buff);
                                    // we use i - 1 because we want to include the number
    } else {
      print(eq, 0, j);
      copy(eq, 0, j, sin_buff);
    }
    printf("\nsingle_eq_buff %s\n", sin_buff);
    single_result = (double) single(sin_buff);

    // place equation with the single result (__*__ * 123 / 4 + 1 * 2)
    //                                        ^^^^^ -> replace it with its result

    // for now this works only for integers. (you can represent rational numbers as integers / integers)
    char single_res_buff[100];
    sprintf(single_res_buff, "%d", single_result); // convert integer to string
    printf("\nsingle result in string %s\n", single_res_buff);

    // copying the result back to the equation
    // THIS IS WHERE THE PROBLEM IS TODO

    int length = strlen(single_res_buff);
    printf("i: %d, j: %d, len: %d\n", i, j, length);
    clear_copy(single_res_buff, 0, length, i, j, eq);
    printf("\nnew eq %s\n", eq);
    strcpy(sin_buff, ""); // clear

    former = eq[find_former_symbol(j-1, eq)];

    printf("eq j_former symbol: %c\n", eq[former]);
  } while ((former != '+' || former != '-') && j < len); // till we hit a secondary operator. do multiplication and division
  printf("YOU ARE OUT OF THE LOOP\n");


  search_from = 0; // resetting because we are going to use it again

  if (j < len) { // if we have any addition or subtraction
    return bigmd(eq, find_former_symbol(j-1, eq));
  } else { // if we dont have only addition or subtraction
    return single_result;
  }

}
