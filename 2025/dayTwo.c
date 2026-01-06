#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

uint64_t partOne(uint64_t *ans);
uint64_t partTwo(uint64_t *input);
uint16_t getDigitCount(uint32_t num);
uint16_t **getDivisionList(uint16_t inDigiCount_1, uint16_t inDigiCount_2);
uint16_t *removeDividends(uint16_t *divPtr, uint16_t index, uint16_t *size);

int main(void)
{
    uint64_t ans = 0;

    FILE *input = fopen("DayTwo_TestInput.txt", "r");
    // FILE *input = fopen("DayTwo_Input.txt", "r");

    int8_t c;
    uint64_t range[2];
    uint64_t val = 0;

    /*
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
            ans += partTwo(range);
        }
    }

    range[1] = val;
    // ans += partOne(range);
    ans += partTwo(range);

    printf("\n%llu\n", ans); */

    uint16_t **test = getDivisionList(8, 14);

    for (uint16_t i = 0; *(test + i) != NULL; i++)
    {
        for (uint16_t j = 0; *(test[i] + j) != 0; j++)
        {
            printf("%u ", *(test[i] + j));
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

uint16_t **getDivisionList(uint16_t inDigiCount_1, uint16_t inDigiCount_2) // First row is the digit length, the rest are the divisors associated with that length in the same collumn
{
    uint16_t **list = (uint16_t **)malloc(sizeof(uint16_t *) * (inDigiCount_2 - inDigiCount_1 + 1)); // dynamic 2D array. Pointer to pointers

    if (list == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }

    uint16_t i = 0;
    for (; inDigiCount_1 <= inDigiCount_2; inDigiCount_1++)
    {
        // Creating an array of divisors and storing the first value as the relevant digit length
        uint16_t size = 2;
        uint16_t *divPtr = (uint16_t *)malloc(sizeof(uint16_t) * size);

        if (divPtr == NULL)
        {
            printf("Failed to allocate memory\n");
            exit(0);
        }

        *divPtr = inDigiCount_1;

        uint16_t divIndex = 1;
        for (uint16_t div = inDigiCount_1 / 2; div >= 2; div--)
        {
            // Store divisor if successful
            if (inDigiCount_1 % div == 0)
            {
                divPtr = (uint16_t *)realloc(divPtr, ++size);
                *(divPtr + divIndex++) = div;
            }
        }

        uint16_t divSize = divIndex + 1;
        divPtr = removeDividends(divPtr, 1, &divSize);

        *(divPtr + divIndex) = 0; // Signals the end of the divisor list

        *(list + i++) = divPtr; // Add the list to the main 2D array
    }

    *(list + i) = NULL; // Signals end of the rows
    return list;
}

uint16_t *removeDividends(uint16_t *divPtr, uint16_t index, uint16_t *size)
{
    if (index >= *size - 1)
        return divPtr;

    uint16_t tempSize = index + 2; // The extra two is to convert an index to a size (+1) and then an extra space for the empty end slot
    uint16_t *divPtrTemp = (uint16_t *)malloc(sizeof(uint16_t) * tempSize);

    if (divPtrTemp == NULL)
    {
        printf("Failed To allocate Memory\n");
        exit(0);
    }

    for (uint16_t i = 0; i <= index; i++) // Fill new array with values already checked.
        *(divPtrTemp + i) = *(divPtr + i);

    for (uint16_t i = index + 1; i < *size - 1; i++) // the arrays include an empty slot at the end, hence size - 1
    {
        if (*(divPtr + index) % *(divPtr + i) != 0)
        {
            divPtrTemp = (uint16_t *)realloc(divPtrTemp, tempSize + 1);

            if (divPtrTemp == NULL)
            {
                printf("Failed To reallocate Memory\n");
                exit(0);
            }

            *(divPtrTemp + tempSize++ - 1) = *(divPtr + i); // add the successful value to the end of the array
        }
    }

    free(divPtr);

    if (tempSize == *size)
        return divPtrTemp;

    *size = tempSize;
    return removeDividends(divPtrTemp, ++index, size);
}

// TODO
// Get the maximum digit count of a uint64 - 20 digits
// Remove divisors that can fit in other divisors (such as 2 and 4 - would remove 2 as to avoid repeated values)
// A little fun side project would be to have the array of pointers to remove any digit length that has no divisors.
