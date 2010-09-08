#include<stdio.h>

void print(int *a);
void test(char *a);

int main()
{
    int a[3] = {1,2,3};
    int i=0;
    void (*fp)();
    int num;
    for(i=0; i<3; i++)
        printf("%d ", a[i]);
    printf("\n");
    i = 0;
    while(1)
    {
        //a[i] = i++;
        a[i++] = i;
        if (i==3)
            break;
    }
    for(i=0; i<3; i++)
        printf("%d ", a[i]);
    printf("\n");
    print((int[]){5});  //c99 支持的复合传值
    //(*fp)() = print;
    fp = print;
    (*fp)((int[]){5});
    test(0);
    test((char*)0);     // 0和NULL的作用在指针的上下文中是完全相同的
    test((char[]){6});
    printf("%c\n", 5["abcdef"]);   //这是合法的,因为[]简单地被解释为指针的加法,即*(5+("abcdef"))
    //scanf("%d", &num);
    num = 5;
    int vla[num];       // c99 支持变长数组,但是只能局限于block,而不能用于global, static等
    int ii;
    for(ii=0; ii<num; ii++)
        vla[ii] = ii;
    for(ii=0; ii<num; ii++)
        printf("%d ", vla[ii]);
    printf("\n");
    printf("%d %d\n", sizeof(char), sizeof('a'));   
    //这个会输出,1 4, 当然后者可能会在不同的机器上得到不同,值得注意的是 sizeof('a')就等价于 sizeof(int)
    // c中字符常数是int型, 与c++不同(c++中二者都是1)

    double f;
    //scanf("%lf", &f);   // 对于double双精度的输入,必须使用lf这样的格式,使用f是不行的
    f = 123.2658;
    printf("%*f", 8, f);    //而这种输出方式,可以动态地指定输出的宽度
    printf("\n");

    char ab[50];
    scanf("%s\n", ab);
    printf("ab:%s\n", ab);

    char cd[50];
    scanf("%s\n", cd);
    printf("cd:%s\n", cd);


    return 0;
}
void print(int *a)
{
    printf("%d\n", *a);
}

void test(char *a)
{
    if (a == 0)
        printf("NUll pointer\n");
    else
        printf("%d\n", *a);
}
