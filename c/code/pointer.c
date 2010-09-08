#include <stdio.h>

int main()
{
    char *a[]  = {
        "Error",
        "Jan.",
        "Feb.",
        "Mar.",
        "Apr.",
        "May",
        "Jun."
        "Jul."
        "Aug.",
        "Sep.",
        "Oct.",
        "Nov.",
        "Dec."
    };
    char b[30] = "How are you today";
    char (*c)[30] ;
    c = b+1;
    printf("%s\n", a[0]);
    printf("%c\n", *c[0]);
    return 0;
}
