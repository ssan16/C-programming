/*Samnang San
CIS-154-01A
Project 2: Mini Yahtzee game
The mini Yahtzee game is a game that allows you to roll five dices to get multiple combinations and get as many points as possible.*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5
#define SCORECARD_SIZE 13

/*declaring the functions for the various prototypes*/
void getFrequency(int dice_array[] , int frequency_array[] );
void printScoreCard(int scorecard[] );
int roll();
void reRoll(int dice_array[] , int keepArray[] );
void printHand(int dice_array[] );
int getChanceScore(int dice_array[] );
int sumOfNum(int dice_array[] , int num);
int getThreeOfKindScore(int dice_array[] );
int getFourOfKindScore(int dice_array[] );
int getSmallStraightScore(int dice_array[] );
int getLargeStraightScore(int dice_array[] );
int getFullHouseScore(int dice_array[] );
int getYahtzeeScore(int dice_array[] );

int main() {

    /*
     dice in hand array are your dice to play
      dice to roll is a parallel array used to
     mark which dice in hand to roll and which keep.
     In the dice to roll array, a 1 means roll the parallel die
      if it is a 0 then do not roll that die and keep its value
     */
    int dice_in_hand[HAND_SIZE] = {0};
    int dice_to_roll[HAND_SIZE] = {0};
    int frequency_roll[HAND_SIZE+1] = {0};/*this is an empty frequency array which fills frequency array with the dice roll counts for the various categories*/

    /*
     Ã Score card array keeps the score for each category
      works with the enum above to use words instead of index numbers
     */
    int scorecard[SCORECARD_SIZE] = {0};
    /*random number generator*/
    srand(time(NULL));
    reRoll(dice_in_hand, dice_to_roll);
    for (int i =0 ; i < 2; i++) {
       /*Reroll 2 times*/
       printHand(dice_in_hand);/*prints the dice that has been randomly generated*/
       printf("For each value, place a 1 to keep that value, place a 0 to reroll\n");/*user is prompted to replace or reroll for the ones that don't have the numbers the user is trying to get*/
       for (int j = 0; j < HAND_SIZE; j++) {
	/*Reroll the dice that you do not want to keep in hand*/
           scanf("%d", &dice_to_roll[j]);
       }
       reRoll(dice_in_hand, dice_to_roll);
    }
    printHand(dice_in_hand);

    /* Calculate the frequency of the items in the array*/
    getFrequency(dice_in_hand, frequency_roll);
    for(int i = 0; i < HAND_SIZE+1; i++) {
      scorecard[i] = (i+1) * frequency_roll[i];
    }
    /*scorecard array calls the categories functions and keeps the categories scores total*/
    scorecard[6] = getChanceScore(dice_in_hand);
    scorecard[7] = getThreeOfKindScore(dice_in_hand);
    scorecard[8] = getFourOfKindScore(dice_in_hand);
    scorecard[9] = getFullHouseScore(dice_in_hand);
    scorecard[10] = getSmallStraightScore(dice_in_hand);
    scorecard[11] = getLargeStraightScore(dice_in_hand);
    scorecard[12] = getYahtzeeScore(dice_in_hand);

    printScoreCard(scorecard);
    return 0;
}
/*function takes in the parameters of an array of dice values and an empty frequency array.  Frequency array are filled with dice roll counts*/
void getFrequency(int dice_array[] , int frequency_array[] ) {
  for(int i = 0; i< HAND_SIZE; i++) {
     int num = dice_array[i];
     frequency_array[num-1] += 1;
  }
}
/*functions that generates a random number from 1-6*/
int roll() {
  return rand() % 6 + 1;
}

/*function that takes the input parameters of the dice array and keep array.  Uses keep array to reroll for values indicated by the keep and update the dice array with the updated values.*/
void reRoll(int dice_array[] , int keepArray[] ) {
 for (int i = 0; i < HAND_SIZE; i++) {
   if (keepArray[i] == 0) {
      dice_array[i] = roll();
   }
 }
}
/*prints the score card with the categories and scores.*/
void printScoreCard(int scorecard[] ) {
  printf("1s : %d\n", scorecard[0]);
  printf("2s : %d\n", scorecard[1]);
  printf("3s : %d\n", scorecard[2]);
  printf("4s : %d\n", scorecard[3]);
  printf("5s : %d\n", scorecard[4]);
  printf("6s : %d\n", scorecard[5]);
  printf("chance : %d\n", scorecard[6]);
  printf("3 of a kind : %d\n", scorecard[7]);
  printf("4 of a kind : %d\n", scorecard[8]);
  printf("full house : %d\n", scorecard[9]);
  printf("small straight : %d\n", scorecard[10]);
  printf("large straight : %d\n", scorecard[11]);
  printf("Yahtzee : %d\n", scorecard[12]);

/*calculates the scorecard to get the maximum value by category*/
  int max = scorecard[0];
  for (int i = 0 ; i < SCORECARD_SIZE; i++) {
    if (scorecard[i] > max)
       max = scorecard[i];
  }
  printf("Highest : %d\n", max);/*prints maximum possible score*/
}


/*function that prints the dice values*/
void printHand(int dice_array[] ) {
 printf("Your hand\n");
 printf("[ ");
 for (int i = 0; i < HAND_SIZE; i++) {
   printf("%d ",dice_array[i]);
 }
 printf("]\n");
}

/*function with input parameters of the dice array and an integer from 1 to 6 that returns teh sum off the dice matching the specified number*/
int sumOfNum(int dice_array[] , int num) {
  int sum = 0;
  for (int i = 0; i < HAND_SIZE; i++) {
    if (dice_array[i] == num) {
      sum  = sum + num;
    }
  }
  return sum;
}
/*function with input parameters of the dice array and returns the sum off all of the dice value*/
int getChanceScore(int dice_array[]) {
  int sum = 0;
  for (int i = 0; i < HAND_SIZE; i++) {
      sum  = sum + dice_array[i];
  }
  return sum;
}

/*function that checks the input parameters to see if there is 4 dice with the same number.*/
int getFourOfKindScore(int dice_array[] ) {
   /*checks the condition to rule out if it is not a yahtzee*/
   if (getYahtzeeScore(dice_array)) {
    return 0;
   }
   /* if not Yahtzee, then will call the getfrequencey function to check if it meets the 4 of a kind condition. Returns the score 40*/
   int frequency_array[HAND_SIZE+1] = {0};

   getFrequency(dice_array, frequency_array);
   for (int i = 0; i < HAND_SIZE+1; i++) {
     if (frequency_array[i] == 4)
      return 40;
   }
   return 0;

}
/*functions checks to see if there is dice values are all the same 5 times*/
int getYahtzeeScore(int dice_array[] ) {
  int i;
  for (i = 0; i < HAND_SIZE-1; i++) {
    if (dice_array[i] != dice_array[i+1]) {
      return 0;
    }
  }
  return 50;
}
/*functions that checks to see if there are 5 sequential dice*/
int getLargeStraightScore(int dice_array[] ) {
  /* Sort the dice_array*/
  int copy_arr[HAND_SIZE];
  for (int i = 0; i < HAND_SIZE; i++)
    copy_arr[i] = dice_array[i];
  for (int i = 0; i < HAND_SIZE - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < HAND_SIZE; j++) {
      if (copy_arr[j] < copy_arr[min_idx])
        min_idx = j;
    }
    /* Swap the array*/
    int temp = copy_arr[i];
    copy_arr[i] = copy_arr[min_idx];
    copy_arr[min_idx] = temp;

  }

  for (int i = 0; i < HAND_SIZE -1; i++) {
   if (copy_arr[i+1] - copy_arr[i] != 1)
      return 0;
  }
  return 40;
}
/*function to get 4 sequential dice*/
int getSmallStraightScore(int dice_array[] ) {
  if (getLargeStraightScore(dice_array))
     return 0;

    /*Sort the dice_array*/
  int copy_arr[HAND_SIZE];
  for (int i = 0; i < HAND_SIZE; i++)
    copy_arr[i] = dice_array[i];
  for (int i = 0; i < HAND_SIZE - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < HAND_SIZE; j++) {
      if (copy_arr[j] < copy_arr[min_idx])
        min_idx = j;
    }
    /*Swap the array*/
    int temp = copy_arr[i];
    copy_arr[i] = copy_arr[min_idx];
    copy_arr[min_idx] = temp;

  }

  int count = 0;
  for (int i = 0; i < HAND_SIZE-1; i++) {
    if (copy_arr[i+1] - copy_arr[i] == 1)
      count++;
  }

  if (count == 3)
    return 30;

  return 0;
}
/*function to get 3 of the same dice value and a pair of the same dice value*/
int getFullHouseScore(int dice_array[] ) {
/*checks to see if the condition is not a Yahtzee*/
  if (getYahtzeeScore(dice_array))
    return 0;
  int count3 = 0, count2 = 0;
  int frequency_array[HAND_SIZE+1] = {0};
  getFrequency(dice_array, frequency_array);
  for (int i = 0; i < HAND_SIZE+1;i++) {
    if (frequency_array[i] == 3) {
      count3 = count3 + 1;
    }
    if (frequency_array[i] == 2) {
      count2 = count2 + 1;
    }
  }
  /* Full house needs to require count3 = 1, and count2 =1*/
  if (count3 == 1 && count2 == 1) {
    return 25;
  }
  return 0;

}

/*function to figure out if there are 3 dice with the same value and no pair*/

int getThreeOfKindScore(int dice_array[] ) {

/*checks the condition of the dice values don't neet the below categories*/
    if (getYahtzeeScore(dice_array))
       return 0;
    if (getFullHouseScore(dice_array))
       return 0;
    if (getFourOfKindScore(dice_array))
       return 0;
    int frequency_array[HAND_SIZE+1] = {0};
/*calls the frequence function to check if there are 3 of the same dice values are in the dice array*/
    getFrequency(dice_array, frequency_array);
    for (int i = 0; i < HAND_SIZE+1; i++) {
      if (frequency_array[i] == 3) {
        return getChanceScore(dice_array);/*sums up the dice values same as the Chance category*/
      }
    }
    return 0;
}