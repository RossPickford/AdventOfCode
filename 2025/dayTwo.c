#include <stdio.h>
#include <limits.h>
#include <math.h>

unsigned long long partOne(unsigned long long *ans);
int getDigitCount(unsigned int num);
unsigned long long powll(unsigned int x, unsigned int y);

int main(void)
{
    unsigned long long ans = 0;

    FILE *input = fopen("DayTwo_TestInput.txt", "r");
    // FILE *input = fopen("DayTwo_Input.txt", "r");

    char c;
    unsigned long long range[2];
    unsigned int val = 0;

    while ((c = fgetc(input)) != EOF)
    {
        if (c != '-' && c != ',' && c != '\n')
        {
            val = (val * 10) + (c - '0');
        }
        else if (c == '-')
        {
            range[0] = val;
            val = 0;
        }
        else if (c == ',')
        {
            range[1] = val;
            val = 0;

            ans += partOne(range);
            // printf("Total: %llu\n", ans);
        }
    }

    range[1] = val;
    ans += partOne(range);

    printf ("\n%llu\n", ans);

    return 0;
}

unsigned long long partOne(unsigned long long *input)
{
    
    int inDigCount_1 = getDigitCount(*input);
    int inDigCount_2 = getDigitCount(*(input + 1));
    
    // if (inDigCount_1 % 2 != 0 && inDigCount_2 % 2 != 0)
    //     return 0;
    
    if (inDigCount_1 % 2 != 0)
    *input = pow(10, ++inDigCount_1);
    else if (inDigCount_2 % 2 != 0)
    *(input + 1) = powll(10, inDigCount_2--) - 1;
    
    printf("%llu, %llu\n", *input, *(input + 1));

    inDigCount_1 /= 2;
    inDigCount_2 /= 2;
    
    unsigned long long total = 0;

    unsigned int inFirstSeg_1 = *input / (pow(10, inDigCount_1));
    unsigned int inFirstSeg_2 = *(input + 1) / (pow(10, inDigCount_2));

    printf("segments: %u, %u\n", inFirstSeg_1, inFirstSeg_2);

    for (; inFirstSeg_1 <= inFirstSeg_2; inFirstSeg_1++)
    {
        unsigned long long val = inFirstSeg_1 + (inFirstSeg_1 * pow(10, getDigitCount(inFirstSeg_1)));

        if (val >= *input && val <= *(input + 1))
        {
            total += val;
            printf("%llu\n", val);
        }
    }
    // printf("%u\n", total);
    return total;
}

int getDigitCount(unsigned int num)
{
    int total;
    for (total = 0; (num /= 10) != 0; ++total)
        ;

    return ++total;
}

unsigned long long powll(unsigned int x, unsigned int y)
{
    unsigned long ans = x;
    for(int i = 1; i < y; i++)
    ans *= x;

    return ans;
}
