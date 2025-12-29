#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

uint64_t partOne(uint64_t *ans);
uint64_t partTwo(uint64_t *input);
uint16_t getDigitCount(uint32_t num);
uint16_t **getDivisionList(uint16_t inDigiCount_1, uint16_t inDigiCount_2);

int main(void)
{
    uint64_t ans = 0;

    FILE *input = fopen("DayTwo_TestInput.txt", "r");
    // FILE *input = fopen("DayTwo_Input.txt", "r");

    int8_t c;
    uint64_t range[2];
    uint64_t val = 0;

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

            // ans += partOne(range);
            // ans += partTwo(range);
        }
    }

    range[1] = val;
    // ans += partOne(range);
    // ans += partTwo(range);

    // printf("\n%llu\n", ans);

    uint16_t **test = getDivisionList(4, 6);

    for (uint16_t i = 0; *(test + i) != NULL; i++)
    {
        for (uint16_t j = 0; *(*(test + i) + j) != NULL; j++)
        {
            printf("%u ", *(*(test + i) + j));
        }

        printf("\n");
    }

    for (uint16_t i = 0; *(test + i) != NULL; i++)
        free(*(test + i));

    free(test);

    return 0;
}

uint64_t partOne(uint64_t *input)
{
    uint64_t *test = input + 1;

    uint16_t inDigCount_1 = getDigitCount(*input);
    uint16_t inDigCount_2 = getDigitCount(*(input + 1));

    if (inDigCount_1 % 2 != 0)
        *input = pow(10, inDigCount_1++);
    else if (inDigCount_2 % 2 != 0)
        *(input + 1) = pow(10, --inDigCount_2) - 1;

    printf("%llu, %llu\n", *input, *(input + 1));

    uint64_t total = 0;

    uint32_t inFirstSeg_1 = *input / (pow(10, inDigCount_1 / 2));
    uint32_t inFirstSeg_2 = *(input + 1) / (pow(10, inDigCount_2 / 2));

    printf("segments: %u, %u\n", inFirstSeg_1, inFirstSeg_2);

    for (; inFirstSeg_1 <= inFirstSeg_2; inFirstSeg_1++)
    {
        uint64_t val = inFirstSeg_1 + (inFirstSeg_1 * pow(10, getDigitCount(inFirstSeg_1)));

        if (val >= *input && val <= *(input + 1))
        {
            total += val;
            printf("%llu\n", val);
        }
    }

    return total;
}

uint64_t partTwo(uint64_t *input)
{
    uint64_t *test = input + 1;

    uint16_t inDigCount_1 = getDigitCount(*input);
    uint16_t inDigCount_2 = getDigitCount(*(input + 1));

    if (inDigCount_1 % 2 != 0)
        *input = pow(10, inDigCount_1++);
    else if (inDigCount_2 % 2 != 0)
        *(input + 1) = pow(10, --inDigCount_2) - 1;

    printf("%llu, %llu\n", *input, *(input + 1));

    uint64_t total = 0;

    uint32_t inFirstSeg_1 = *input / (pow(10, inDigCount_1 / 2));
    uint32_t inFirstSeg_2 = *(input + 1) / (pow(10, inDigCount_2 / 2));

    printf("segments: %u, %u\n", inFirstSeg_1, inFirstSeg_2);

    for (; inFirstSeg_1 <= inFirstSeg_2; inFirstSeg_1++)
    {
        uint64_t val = inFirstSeg_1 + (inFirstSeg_1 * pow(10, getDigitCount(inFirstSeg_1)));

        if (val >= *input && val <= *(input + 1))
        {
            total += val;
            printf("%llu\n", val);
        }
    }

    return total;
}

uint16_t getDigitCount(uint32_t num)
{
    uint16_t total;
    for (total = 0; (num /= 10) != 0; ++total)
        ;

    return ++total;
}

uint16_t **getDivisionList(uint16_t inDigiCount_1, uint16_t inDigiCount_2)
{
    uint16_t **list = (uint16_t **)malloc(sizeof(uint16_t *) * (inDigiCount_2 - inDigiCount_1 + 1)); // dynamic 2D array. Pointer to pointers

    uint16_t i = 0;
    while (inDigiCount_1++ <= inDigiCount_2)
    {
        u_int8_t size = 2;
        uint16_t *divPtr = (uint16_t *)malloc(sizeof(uint16_t) * size);
        *divPtr = inDigiCount_1;

        uint16_t div = 2, j = 1;
        while (div++ != inDigiCount_1 / 2)
        {
            if (inDigiCount_1 % div == 0)
            {
                divPtr = (u_int16_t *)realloc(divPtr, ++size);
                *(divPtr + j++) = div;
            }
        }

        *(divPtr + j) = NULL;

        *(list + i++) = divPtr;
    }

    *(list + i) = NULL;
    return list;

    // TODO
    //  give input values for the 2D array, and then output their values to see if the function works correctly.
    //  If so, continue with then going through each division, and then calculating which values match the conditions.
}