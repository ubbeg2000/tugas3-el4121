#include <stdio.h>
#include <stdlib.h>
#include "slide_fsm.h"

int main()
{
    FILE *f = fopen("slide_fsm_simulation.csv", "w");
    int state = 1, input_left = 0, input_right = 0, output = 1;

    fprintf(f, "input_left,input_right,output\n");

    for (int i = 0; i < 20; i++)
    {
        input_left = i < 10 ? 1 : 0;
        input_right = i >= 10 ? 1 : 0;
        slide_fsm(&state, input_left, input_right);
        fprintf(f, "%d,%d,%d\n", input_left, input_right, state);
    }
    return 0;
}