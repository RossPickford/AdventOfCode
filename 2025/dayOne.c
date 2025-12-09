#include <stdio.h>
#define STARTPOS 50
#define SETDIRECTION (((c - 'L') / ('R' - 'L')) * 2) - 1

int main(void)
{
    int password = 0;
    unsigned int dialPosition = STARTPOS, prevDial;
    char direction = 0;

    FILE *input = fopen("DayOne_Input.txt", "r");
    // FILE *input = fopen("test.txt", "r");

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
            // printf("%d : %d\n", direction, movement);
            prevDial = dialPosition;
            dialPosition += (direction * movement);

            if ((int)(prevDial - dialPosition) < 0 && direction == -1)
            {
                printf("%d\n", (int)(prevDial - dialPosition));
                dialPosition -= 96;
            }

            if (dialPosition > 99)
                dialPosition = dialPosition % 100;

            if (dialPosition == 0)
                password++;

            // printf("%d\n", dialPosition);
            movement = 0;
        }
    }

    // printf("%d : %d\n", direction, movement);
    prevDial = dialPosition;
    dialPosition += (direction * movement);

    if ((int)(prevDial - dialPosition) < 0 && direction == -1)
    {
        dialPosition -= 96;
    }

    if (dialPosition > 99)
        dialPosition = dialPosition % 100;

    if (dialPosition == 0)
        password++;

    movement = 0;

    printf("\n%d\n", password);

    return 0;
}
