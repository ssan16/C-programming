/*Samnang San 00291786
Project 1
The most useful machine is a machine that gives users option on what they can let the machine do.
a menu gives users selections from 1-9. users are prompted for information and results are displayed.*/




#include <stdio.h>
#include <math.h>

// Prototype of the various functions
int AsciiToInt(char c);
int IsNotLetter(char c);
int IsEven(int num);
int Round(double num);
int MaxOfThree(int num1, int num2, int num3);
double Average5(int num1, int num2, int num3, int num4, int num5);
int CloseEnough(double num1, double num2);
int PowPow(int num1, int num2, int num3);
void getAnswer(int ans);

int main(void) {
  int option, num;//declaration of variables
  char c;
  int ans;
  printf("Welcome to the Most useful machine\n");
  printf("1. Convert Ascii to integer\n");
  printf("2. Check character is a letter\n");
  printf("3. Check number is even\n");
  printf("4. Round the double number\n");
  printf("5. Max of three number\n");
  printf("6. Average of 5 number\n");
  printf("7. Close enough\n");
  printf("8. Calculate pow pow\n");
  printf("9. Quit\n");
  printf("Select option (1-9): ");//prompt user to pick an option
  scanf("%d", &option);
  getchar();  // Remove new line, was stuck on this part, new line kept print with selection. will have sources in readme.
  switch (option) {//used the switch option for the menu selection. Check cases until it matches case number and it continues until it hits a break.
    case 1:
    {
      printf("Enter an Ascii character: ");
      scanf("%c",&c);
      ans = AsciiToInt(c);//Option functions gets called and returns an integer.
      printf("Number of Ascii character %c: %d\n",c, ans);
      break;
    }
    case 2:
    {
      printf("Enter an Ascii character: ");
      scanf("%c",&c);
      ans = IsNotLetter(c);//Option function check to see if it is a letter.  Had some issues with this one.  Same output for both letter or number.
      getAnswer(ans);
      break;
    }
    case 3:
    {

      printf("Enter a number: ");
      scanf("%d", &num);
      ans = IsEven(num);//Option function to see if it the input is an even number.
      getAnswer(ans);
      break;
    }
    case 4:
    {
      double number;
      printf("Enter a number: ");
      scanf("%lf", &number);
      ans = Round(number);//function call
      printf("Integer (round) value: %d\n", ans);
      break;
    }
    case 5:
    {
      int num1, num2, num3;
      printf("Enter 3 number: ");
      scanf("%d%d%d", &num1, &num2, &num3);
      ans = MaxOfThree(num1, num2, num3);
      printf("Maximum of 3 numbers: %d\n", ans);
      break;
    }
    case 6:
    {
      int num1, num2, num3, num4, num5;
      printf("Enter 5 numbers: ");
      scanf("%d%d%d%d%d", &num1, &num2, &num3, &num4, &num5);
      ans = Average5(num1, num2, num3, num4, num5);
      printf("Average of 5 numbers: %d\n", ans);
      break;
    }
    case 7:
    {
      double value1, value2;
      printf("Enter 2 double numbers: ");
      scanf("%lf%lf", &value1, &value2);
      ans = CloseEnough(value1, value2);
      getAnswer(ans);
      break;
    }
    case 8:
    {
      int num1, num2, num3;
      printf("Enter 3 number: ");
      scanf("%d%d%d", &num1, &num2, &num3);
      ans = PowPow(num1, num2, num3);//function to be called
      printf("Calculate PowPow value: %d\n", ans);
      break;
    }
    case 9:
    {
      printf("Thank you. Quitting \n");
      break;
    }
    default: printf("Invalid option. Quitting \n");
  }
  return 0;
}

int AsciiToInt(char c) {
  return (int)c; // Casting the variable from Char to Int
}
int IsNotLetter(char c) { // Return 1 if c is a letter
  if ((c>='a' && c <= 'c') || (c >= 'A' && c <= 'Z')) {
    return 0;
  } else {
    return 1;
  }
}

int IsEven(int num) {
  // Return 1 if number is even
  if (num % 2 == 0) {
    return 1;
  } else { // Otherwise 0
    return 0;
  }
}

int MaxOfThree(int num1, int num2, int num3) {//funcion compares the 3 input numbers and gives the maximum out of the 3
  if (num1 >= num2 && num1 >= num3) {
    return num1;
  } else if (num2 >= num1 && num2 >= num3) {
    return num2;
  } else {
    return num3;
  }
}

double Average5(int num1, int num2, int num3, int num4, int num5) {//function finds the average of 5 numbers
  int sum = num1 + num2 + num3 + num4 + num5;
  return (double)sum / 5;
}

int Round(double num) {//this function calculates the remainder in order to figure out the closest integer.  If the remainder is greater 5, you would add 1 else it stays that number.
  int i = num * 10;
  int remainder = i % 10;
  int number = i / 10;
  if (remainder > 5) {
    return number +1;
  } else {
    return number;
  }
}

int CloseEnough(double num1, double num2) {
  // Take the difference between 2 double value and result is an absolute value
  double diff = fabs(num1-num2);
  // Return 1 if difference less than tolerance
  if (diff < 0.0001) {
    return 1;
  } {
    return 0;
  }

}

int PowPow(int num1, int num2, int num3) {//Takes the power of the first number raised to the next number
  int result = pow(num1, num2);
  return pow(result, num3);
}

void getAnswer(int ans) { ////function to display if the condition is true or false base on user input.
  // Print True if ans = 1, Otherwise print False
  if (ans == 1)
    printf("True\n");
  else
    printf("False\n");
  printf("Thank you\n");
}