#include <stdio.h>

int main()
{
    unsigned int haz, oth;

    while(scanf("%u", &haz) != EOF)
    {
        scanf("%u", &oth);
        if(oth > haz)
            printf("%u\n", oth - haz);
        else
            printf("%u\n", haz - oth);
    }
    printf("\n");
    return 0;
}
