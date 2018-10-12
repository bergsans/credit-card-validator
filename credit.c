// libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

// task specific functions
int check_validity_of_number(unsigned long long int n);
int card_type(unsigned long long int n);

// main gets a number from the user and checks it's validity and if it is a AMEX, VISA or Mastercard
int main(void)
{
    unsigned long long int userNumber = get_long_long("Number: ");

    int validCard = check_validity_of_number(userNumber);

    if (validCard == 1 && userNumber > 99999999999)
    {
        int firstNumber = card_type(userNumber);

        if(firstNumber == 34 || firstNumber == 37)
        {
            printf("AMEX\n");
        }
        else if(firstNumber >= 40 && firstNumber <= 49)
        {
            printf("VISA\n");
        }
        else if(firstNumber >= 51 && firstNumber <= 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

// is the number valid according to the procedure of Luhn?
int check_validity_of_number(unsigned long long int n)
{

    char stringifiedVersion[17];
    sprintf(stringifiedVersion, "%llu", n);
    int len = strlen(stringifiedVersion);

    int oddTempCounter = 0;
    int evenTempCounter = 0;
    int oddNumbers[8] = {0,0,0,0,0,0,0,0};
    int evenNumbers[8] = {0,0,0,0,0,0,0,0};
    int totalEvenSum = 0;
    int totalOddSum = 0;
    int totalSum = 0;

    for (int i = len-2; i >= 0; i -= 2)
    {
        oddNumbers[oddTempCounter] = (stringifiedVersion[i] - 48) * 2;
        oddTempCounter++;
    }

    for (int j = 0; j < 8; j++)
    {
        char tempOddNumber[3];
        sprintf(tempOddNumber, "%i", oddNumbers[j]);

        for (int k = 0; k < strlen(tempOddNumber); k++)
        {
            int tempOdd = tempOddNumber[k] - 48;
            totalOddSum += tempOdd;
        }
    }

    for(int x = len-1; x >=0; x-=2)
    {
        evenNumbers[evenTempCounter] = (stringifiedVersion[x] - 48);
        totalEvenSum += evenNumbers[evenTempCounter];
        evenTempCounter++;
    }

    totalSum = totalEvenSum + totalOddSum;

    char result[3];
    sprintf(result, "%d", totalSum);
    int index = strlen(result)-1;

    int endingInt = result[index] - 48;

    if (endingInt == 0)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

// what card type is the valid card?
int card_type(unsigned long long int n)
{
    char numb[17];
    sprintf(numb, "%llu", n);

    int firstTwoNumbers = ((numb[0] - 48) * 10) + (numb[1] - 48);
  //  printf("%s %d",numb,firstTwoNumbers);

    return firstTwoNumbers;
}