#include <cs50.h>
#include <stdio.h>

void build_block(int height);

int main(void)
{
    //User input
    int height = get_int("Please enter the pyramid height value: ");
    //User input condition respect?
    if (height < 1 || height > 8)
    {
        printf("Please enter a value between or equal to 1 or 8 \n");
        height = get_int("Please enter the pyramid height value: ");
    }
    //Pyramid building function
    build_block(height);

}
//Pyramid building function
void build_block(height)
{
    //Line building
    for (int i = 1; i <= height; i++)
    {
        //dot number determination
        if (height - i != 0)
        {
            printf("%*s", height - i, " ");
        }
        //Block building
        for (int j = 0; j < i ; j++)
        {
            printf("#");
        }
        //Building space between pyramids
        printf("  ");

        //Building right side of the piramid
        for (int j = 0; j < i ; j++)
        {
            printf("#");
        }
        printf("\n");
    }

}