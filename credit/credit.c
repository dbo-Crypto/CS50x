#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

string card_type(long int number, int nDigits);
bool algo_luhn(long int number, int nDigits);


int main(void)
{
    long int number = get_long("Please insert card number : \n");
    int nDigits = floor(log10(labs(number))) + 1;
    string type;
    bool algo;


    type = card_type(number, nDigits);
    algo = algo_luhn(number, nDigits);

    if (algo == 1)
    {
        printf("%s", type);
    }
    else
    {
        printf("INVALID\n");
    }



}

// Function to determine the card type
string card_type(long int number, int nDigits)
{
    long int first = number;
    long int first2 = number;
    // Get the 2 first aand first digit
    while (first2 >= 100)
    {
        first2 =  first2 / 10;
    }
    while (first >= 10)
    {
        first =  first2 / 10;
    }
    if (nDigits == 15 && (first2 == 34 || first2 == 37))
    {
        printf("It's an American express card \n");
        return "AMEX\n";
    }
    else if (nDigits == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55))
    {
        printf("It's a Master Card card \n");
        return "MASTERCARD\n";
    }
    else if ((nDigits == 13 || nDigits == 16) && first == 4)
    {
        printf("It's a Visa card \n");
        return "VISA\n";
    }
    else
    {
        return "INVALID\n";
    }
}

// Luhn function to determine validity
bool algo_luhn(long int number, int nDigits)
{
    // Variable definition
    int len_arr;
    int arr[100] = { 0 };
    int arr2[20] = { 0 };
    int arr3[20] = { 0 };
    int arr4[20] = { 0 };
    int i, j, sum, temp, count, lenght, count2, checksum;

    // initial array for number size
    for (i = 0; i < nDigits; i++)
    {
        arr[i] = i + 1;
    }
    // Append all the digits in array
    for (i = 0; i < nDigits; i++)
    {
        int test = number % 10;
        arr[i] = test;
        arr2[i] = test;
        number = number / 10;
    }

    // Print only digits to multiply by 2
    printf("arr : \n");
    for (i = 1; i < nDigits; i += 2)
    {
        printf("%i \t", arr[i]);
    }
    printf("\n");


    // Print other digits
    printf("arr2 : \n");
    for (i = 0; i < nDigits; i += 2)
    {
        printf("%i \t", arr2[i]);
    }
    printf("\n");


    //multiply the digits by 2
    for (i = 1; i < nDigits; i += 2)
    {
        if (arr[i] != 0)
        {
            arr3[i] = arr[i] * 2;
        }
        else
        {
            arr[i] = arr[i];
        }
    }

    // Print array with multiplied digits
    printf("arr3 : \n");
    for (i = 0; i < nDigits; i++)
    {
        printf("%i \t", arr3[i]);
    }
    printf("\n");



    // Count sum multiplied digits
    for (i = 1; i < nDigits; i += 2)
    {
        if (arr3[i] < 10)
        {
            sum = sum + arr3[i];
            printf("sum is : %i \t", sum);
        }
        else if (arr3[i] >= 10)
        {
            while (arr3[i] > 0)
            {
                temp = arr3[i] % 10;
                arr3[i] = arr3[i] / 10;
                count = count + temp;
                printf("count is : %i \t", count);
            }
        }
    }
    // Calculation count
    count = count + sum;
    printf("%d\n", count);

    // Calculation count2
    for (i = 0; i < nDigits; i += 2)
    {
        count2 = arr2[i] + count2;
    }
    // Checksum calculation
    checksum = count + count2;
    printf("checksum is : %i\n", checksum);


    // Return of Luhn algo result
    if (checksum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }


}

