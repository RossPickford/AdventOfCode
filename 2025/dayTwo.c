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
void intToString(uint64_t val, char s_val[], uint16_t length);
void freeDouble(uint16_t **dbPtr);

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
            ans += partTwo(range);
        }
    }

    range[1] = val;
    // ans += partOne(range);
    ans += partTwo(range);

    printf("\n%llu\n", ans);

    // uint64_t test[2] = {95, 115};
    // uint64_t result = partTwo(test);

    return 0;
}

uint64_t partOne(uint64_t *input)
{
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
    uint64_t total = 0;

    uint16_t inDigCount_1 = getDigitCount(*input);
    uint16_t inDigCount_2 = getDigitCount(*(input + 1));

    printf("inputs: %llu, %llu\n", *input, *(input + 1));

    uint16_t **divList = getDivisionList(inDigCount_1, inDigCount_2);

    if (divList == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(0);
    }

    for (uint16_t i = 0; *(divList + i) != NULL; i++)
    {
        printf("digit and divisor: ");
        for (uint16_t j = 0; *(divList[i] + j) != 0; j++)
        {
            printf("%u ", *(divList[i] + j));
        }

        printf("\n");
    }

    uint16_t *l;
    for (uint16_t i = 0; (l = *(divList + i)) != NULL; i++)
    {
        uint64_t val = i == 0 ? *input : pow(10, *l - 1);
        uint64_t max = *(divList + i + 1) != NULL ? pow(10, *l) - 1 : *(input + 1);

        for (; val <= max; val++) // Iterate through every possible value that is of the *l digits long
        {
            char s_val[*l];
            intToString(val, s_val, *l);

            uint16_t d;
            for (uint16_t j = 1; (d = *(l + j)) != 0; j++) // Go through each digit lengths divisors in divList
            {
                char divCheck[d]; // array used to store div length;

                uint16_t k;
                for (k = 0; k < d; k++) // storing the initial digits from the value.
                    divCheck[k] = s_val[k];

                for (uint16_t t = 0; k < *l; k++)
                {
                    if (s_val[k] != divCheck[t++]) // break if the values do not match
                        break;

                    if (t >= d)
                        t = 0;
                }

                if (k >= *l) // If k is greater than *l - the value is succesful
                    break;
            }

            if (d != 0) // This double checks the values success, and then will add to the total if so.
            {
                total += val;
                printf("%llu\n", val);
            }
        }
    }

    freeDouble(divList);

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
        for (uint16_t div = inDigiCount_1 / 2; div >= 1; div--)
        {
            // Store divisor if successful
            if (inDigiCount_1 % div == 0)
            {
                divPtr = (uint16_t *)realloc(divPtr, ++size);

                if (divPtr == NULL)
                {
                    printf("Failed To reallocate Memory\n");
                    exit(0);
                }

                *(divPtr + divIndex++) = div;
            }
        }

        // uint16_t divSize = divIndex + 1;
        // divPtr = removeDividends(divPtr, 1, &divSize);

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

void intToString(uint64_t val, char s_val[], uint16_t length)
{
    for (int16_t i = length - 1; i >= 0; i--)
    {
        uint64_t tempVal = val;
        tempVal /= 10;
        tempVal *= 10;

        s_val[i] = (val - tempVal) + '0';
        val /= 10;
    }
}

void freeDouble(uint16_t **dbPtr)
{
    // uint16_t size = sizeof(dbPtr) / sizeof(dbPtr[0]);

    uint16_t i;
    for (i = 0; *(dbPtr + i) != NULL; i++)
        free(dbPtr[i]);

    free(dbPtr[i]);
    free(dbPtr);
}

// TODO
// Get the maximum digit count of a uint64 - 20 digits
// there seems to be an issue with memory. Need to debug why the first digit count and it's divisor is not saved (such as for 95, 115)
// BUT ONLY when reading from the file, not giving the values individually.
