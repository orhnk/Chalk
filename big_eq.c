#include "calc.c"
#include <stdio.h>

#define loop for(;;)
double big(char* eq);

int main() {
  // With these, I have to construct a function that returns: 7*7/3-4/4*4*4/3 = 1
  loop { 
    char input_buff[10];
    printf(">> ");
    get_input(input_buff);
    double result = big(input_buff);
    printf("Result of a big equation is: %lf\n", result);
  }
}

double big(char* eq) {
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
  int search_from = 0;
  int i, j = 0; // while's body. j is initialized because it is used in the do-while first
  int len = strlen(eq);
  char sin_buff[100]; // single equation buffer

  // we have a next function that will return the next operator from an index
  do {
    search_from = j; // we know that the next symbol will be at least 2 characters away
    if (search_from != 0) {
      i = find_next_symbol(search_from, eq);
    } else {
      i = 0; // if we are at the start of the string, we dont need to search for the next symbol
    }
    printf("i: %d, ", i);
    if (i == 0) { // This leads ERROR: with 2+ symbols TODO
      // finding the second symbol
      j = find_next_symbol(find_next_symbol(0,eq) + 1 /*This was symbol. 
                                                        ( We don't want to overlap it so starting from 
                                                        the next index)*/, eq); 
    } else {
      j = find_next_symbol(i+2, eq); // 2 is an optimization:
    }

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
      print(eq, i, j);
      copy(eq, i, j, sin_buff);
    }
    printf("\nsingle_eq_buff %s\n", sin_buff);
    int single_result = (int) single(sin_buff);

    // place equation with the single result (__*__ * 123 / 4 + 1 * 2)
    //                                        ^^^^^ -> replace it with its result

    // for now this works only for integers. (you can represent rational numbers as integers / integers)
    sprintf(sin_buff, "%d", single_result); // convert integer to string
    printf("\nsingle result in string %s\n", sin_buff);

    // copying the result back to the equation
    // NOT TESTED! TODO
    if (i != 0) {
      copy(sin_buff, 0, strlen(sin_buff), eq + i - 1);
    } else {
      copy(sin_buff, 0, strlen(sin_buff), eq + i);
    }
    printf("\nnew eq %s\n", eq);
    strcpy(sin_buff, ""); // clear
    


  } while ((eq[i] != '+' || eq[i] != '-') && j < len); // till we hit a secondary operator. do multiplication and division
  search_from = 0; // resetting because we are going to use it again
}
