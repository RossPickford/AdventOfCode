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
    password += dialCheck(&dialPosition, direction);

    printf("\n%d\n", password);

    return 0;
}

int dialCheck(unsigned int *dialPos, int direction)
{
    int passes = 0, test = prevDial;

    if (*dialPos > DIALMAX && direction == LEFT)
    {
        unsigned int diff = UINT_MAX - *dialPos; // This is only when the dialPos loops back to the high end of an unsigned int
        *dialPos = diff - (2 * (diff % 100)) + DIALMAX; // This adjusts the dialPos

        if ( *dialPos % 100 == 0) *dialPos += 100; // if dialPos is 0, then it would have done a minimum of 1 rotation
        
        if (prevDial != 0)
            *dialPos += 100;
    }

    passes += *dialPos / 100;

    if (prevDial != 0) passes += (*dialPos == 0); 

    *dialPos = *dialPos % 100;

    return passes;
}

// going R to 100 means +1
// going L from 0 to another 0 means only +1
// going R from non-zero to 0 over several iterations
// going L from non-zero to 0 over several iterations

