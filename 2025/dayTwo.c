#include <stdio.h>
#include <math.h>

unsigned int partOne(unsigned int *ans);
int getDigitCount(unsigned int num);

int main(void)
{
    unsigned int ans = 0;

    FILE *input = fopen("DayTwo_TestInput.txt", "r");

    char c;
    unsigned int range[2];
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
        }
    }

    printf("\n%u\n", ans);

    return 0;
}

unsigned int partOne(unsigned int *input)
{
    printf("%u, %u\n", *input, *(input + 1));

    int inDigCount_1 = getDigitCount(*input);
    int inDigCount_2 = getDigitCount(*(input + 1));

    if (inDigCount_1 % 2 != 0 && inDigCount_2 % 2 != 0)
        return 0;

    if (inDigCount_1 % 2 != 0)
        inDigCount_1 = pow(10, inDigCount_1 + 1);
    else if (inDigCount_2 % 2 != 0)
        inDigCount_2 = pow(10, inDigCount_2 - 1);

    inDigCount_1 /= 2;
    inDigCount_2 /= 2;

    unsigned int total = 0;

    int inFirstSeg_1, inFirstSeg_2, inSecSeg_1, inSecSeg_2;
    inFirstSeg_1 = *input / (pow(10, inDigCount_1));
    inFirstSeg_2 = *(input + 1) / (pow(10, inDigCount_2));
    inSecSeg_1 = *input - (inFirstSeg_1 * pow(10, inDigCount_1));
    inSecSeg_2 = *(input + 1) - (inFirstSeg_2 * pow(10, inDigCount_2));

    printf("%u, %u, %u, %u\n", inFirstSeg_1, inSecSeg_1, inFirstSeg_2, inSecSeg_2);

    for (; inFirstSeg_1 <= inFirstSeg_2; inFirstSeg_1++)
    {
        if (inFirstSeg_1 <= inSecSeg_2 && inFirstSeg_1 >= inSecSeg_1)
        {
            unsigned int test = inFirstSeg_1 + (inFirstSeg_1 * pow(10, getDigitCount(inFirstSeg_1)));
            total += test;
            printf("%u\n", test);
        }
    }

    return total;
}

int getDigitCount(unsigned int num)
{
    int total;
    for (total = 0; (num /= 10) != 0; ++total)
        ;

    return ++total;
}