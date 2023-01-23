#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //User input
    string myname = get_string("Please enter your name: ");
    printf("hello, %s \n ", myname);
}
