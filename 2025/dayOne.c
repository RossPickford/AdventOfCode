#include <stdio.h>
#include <limits.h>
#define STARTPOS 50
#define LEFT -1
#define DIALMAX 99
#define DIAL_NEGATIVE_SHIFT 96
#define SETDIRECTION (((c - 'L') / ('R' - 'L')) * 2) - 1

int dialCheck(unsigned int *dialPos, int direction);

unsigned int prevDial = 0;

int main(void)
{
    int password = 0;
    unsigned int dialPosition = STARTPOS;
    char direction = 0;

    FILE *input = fopen("DayOne_Input.txt", "r");
    // FILE *input = fopen("dayOne_ExampleInput.txt", "r");
    // FILE *input = fopen("dayOne_TestInput.txt", "r");

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
            prevDial = dialPosition;
            dialPosition += (direction * movement);
            password += dialCheck(&dialPosition, direction);

            movement = 0;
        }
    }

    prevDial = dialPosition;
    dialPosition += (direction * movement);
    password += dialCheck(&dialPosition, direction) + (dialPosition == 0);

    printf("\n%d\n", password);

    return 0;
}

int dialCheck(unsigned int *dialPos, int direction)
{
    unsigned int passes = 0, test = prevDial;
    if (*dialPos > DIALMAX && direction == LEFT)
    {
        unsigned int diff = UINT_MAX - *dialPos;        // this is only when the dialPos loops back to the high end of an unsigned int
        *dialPos = diff - (2 * (diff % 100)) + DIALMAX; // This adjusts the dialPos

        if (prevDial != 0)
            passes++;
    }

    passes += *dialPos / 100;

    if (*dialPos % 100 == 0)
        passes--;

    *dialPos = *dialPos % 100;

    passes += (*dialPos == 0);
    return passes;
}