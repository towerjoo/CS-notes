#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int oc;
    char *b_opt_arg;

    while((oc=getopt(argc,argv,"ngl:")) != -1)
    {
        switch(oc)
        {
            case 'n':
                printf("My name is Tower Joo\n");
                break;
            case 'g':
                printf("Her name is ZYY\n");
                break;
            case 'l':
                b_opt_arg = optarg;
                printf("Our love is %s\n", optarg);
                break;
            default:
                break;
        }
    }
    return 0;
}

