#include <stdio.h>

int main(void)
{
    long long number;
    printf("Number: ");
    scanf("%lld", &number);


    int sum = 0, count = 0;
    long long temp = number;

  
    while (temp > 0)
    {
        int digit = temp % 10;

        if (count % 2 == 1) 
        {
            int d = digit * 2;
            sum += d / 10 + d % 10; 
        }
        else
        {
            sum += digit;
        }

        temp /= 10;
        count++;
    }

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    long long start = number;
    while (start >= 100)
    {
        start /= 10;
    }

    if ((start == 34 || start == 37) && count == 15)
        printf("AMEX\n");
    else if ((start >= 51 && start <= 55) && count == 16)
        printf("MASTERCARD\n");
    else if ((start / 10 == 4) && (count == 13 || count == 16))
        printf("VISA\n");
    else
        printf("INVALID\n");

    return 0;
}
