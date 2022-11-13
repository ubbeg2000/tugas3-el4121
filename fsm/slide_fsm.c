#include "slide_fsm.h"

void slide_fsm(int *state, int input_left, int input_right)
{
    if (input_right == 1)
    {
        if (*state == 1)
        {
            *state = 8;
        }
        else
        {
            *state = *state >> 1;
        }
    }
    else if (input_left == 1)
    {
        if (*state == 8)
        {
            *state = 1;
        }
        else
        {
            *state = *state << 1;
        }
    }
}