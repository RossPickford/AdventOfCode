#include <stdio.h>
#include <limits.h>
#define STARTPOS 50
#define LEFT -1
#define DIALMAX 99
#define DIAL_NEGATIVE_SHIFT 96
#define SETDIRECTION (((c - 'L') / ('R' - 'L')) * 2) - 1

void dialCheck(unsigned int* dialPos, int direction);

int main(void)
{
    int password = 0;
    unsigned int dialPosition = STARTPOS;
    char direction = 0;

    FILE *input = fopen("DayOne_Input.txt", "r");

    char c;
    int movement = 0;
    while ((c = fgetc(input)) != EOF)
    {
        if (c == 'L' || c == 'R')
        {
            direction = SETDIRECTION;
        }
        else if (c != '\n')
        {
            movement = (10 * movement) + (c - '0');
        }
        else
        {
            dialPosition += (direction * movement);
            dialCheck(&dialPosition, direction);

            if (dialPosition == 0)
                password++;

            movement = 0;
        }
    }

    dialPosition += (direction * movement);

    dialCheck(&dialPosition, direction);

    if (dialPosition == 0)
        password++;

    movement = 0;

    printf("\n%d\n", password);

    return 0;
}

void dialCheck(unsigned int* dialPos, int direction)
{
    if (*dialPos > DIALMAX && direction == LEFT)
    {
        unsigned int diff = UINT_MAX - *dialPos;
        *dialPos = DIALMAX - (diff % 100) + diff;
    }

    if (*dialPos > 99)
    {
        *dialPos = *dialPos % 100;
    }
}