#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>


char *vstrcat(const char *first, ...);  // 可变参数的函数

int main()
{
    double a;
    double b;
    int c = 10;
    double epsilon;

    a = 10.;
    b = 10.0;

    printf("a:%8lf  b:%8lf\n", a, b);
    if (c == b) //对于浮点型的变量,通常不能这样比较大小,因为在计算机内部,浮点数并不是精确表示的, 在实际中可能会依赖于实现
        printf("Equal!");
    else
        printf("Unequal!");
    printf("\n");
    // 浮点数的比较通常可以这样
    epsilon = 0.00001;  //epsilon用来控制接近程度
    if (fabs(a-b) <= epsilon*fabs(a))   //如果满足则认为相等,否则不等
        printf("Equal!");
    else
        printf("Unequal!");
    printf("\n");

    char* str = vstrcat("Hello, ", "World", "!", (char*)NULL);
    printf("%s\n", str);
    free(str);  //注意即使是在函数中动态分配的内存,也必须要显式地释放,否则会造成内在泄漏

    int x = 1;
    if(*(char *)&x == 1)    //用来判断是高字节在先,还是低字节在先
        printf("little-endian\n");
        else
            printf("big-endian\n");
    return 0;
}

char *vstrcat(const char *first, ...)
{
    size_t len;
    char *retbuf;
    va_list argp;
    char *p;
    if(first == NULL)
        return NULL;
    len = strlen(first);
    va_start(argp, first);
    while((p = va_arg(argp, char *)) != NULL)
        len += strlen(p);
    va_end(argp);
    retbuf = malloc(len + 1); /* +1 包含终止符\0 */
    if(retbuf == NULL)
        return NULL; /* 出错*/
    (void)strcpy(retbuf, first);
    va_start(argp, first); /* 重新开始扫描*/
    while((p = va_arg(argp, char *)) != NULL)
        (void)strcat(retbuf, p);
    va_end(argp);
    return retbuf;
}
