#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void bubbleSort(int *a, int n)
{
    //每次将最小的浮到最左  这个其实不是冒泡排序
    int i, j;
    int tmp;
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++)
            if (a[i] > a[j])
                swap(a+i, a+j);
}
void bubbleSort2(int *a, int n)
{
    int swapped = 1;
    int i;
    int bound = n;
    while(swapped)
    {
        bound--;    //因为每次pass后,最大的元素总是位于最末的位置,所以无需对所有的元素进行比较,可以提高性能
        swapped = 0;
        for(i=0; i<bound; i++)
            if (a[i] > a[i+1])
            {
                swap(a+i, a+i+1);
                swapped = 1;
            }
    }
}

void selectSort(int *a, int n)
{
    //每次先找到最小的元素的下标,然后与当前的元素交换即可
    int i, j;
    int tmp;
    int cur;
    for(i=0; i<n; i++)
        {
            cur = i;
            for(j=i+1; j<n; j++)
                if(a[cur] > a[j])
                    cur = j;
            swap(a+i, a+cur);
        }
}

void insertSort(int *a, int n)
{
    // 将新的元素插入到有序序列的合适位置,直至所有的元素有序

    int tmp;
    int i, j;
    int key;

    for(i=1; i<n; i++)
    {
        key = a[i];
        j = i-1;
        while(j>=0 && key < a[j])
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void shellSort(int *a, int n)
{
    //希尔排序:基于插入排序,但是每次会调整多个元素

    int inc = n/2;
    int i, j;
    while(inc > 0)
    {
        for(i=inc; i<n; i++)
        {
            int temp = a[i];
            j = i;
            while (j>=inc && a[j-inc] > temp)
            {
                a[j] = a[j-inc];
                j -= inc;
            }
            a[j] = temp;
        }
        if (inc == 1)
            break;
        else
        {
            inc = (int)(inc/2.2);
            inc = (inc==0)?1:inc;
        }
    }
}

void oneQuickSort(int *a, int left, int right)
{
    int i, j;
    int k=left;
    i = left-1;
    if (left == right)
        return;
    while(k<right-1)
    {
        if (a[k] < a[right-1])
        {
            swap(a+k, a+i+1);
            i++;
        }
        k++;
    }
    swap(a+i+1, a+right-1);
    oneQuickSort(a, left, i+1);
    oneQuickSort(a, i+2, right);
}
void quickSort(int *a, int n)
{
    oneQuickSort(a, 0, n);
}

void merge(int *a, int *b, int num1, int num2)
{
    // 合并两个有序列表
    int *tmp = (int *)malloc(sizeof(int)*(num1+num2));
    int i, j, k;
    i = j = k = 0;
    while(i<num1 && j<num2)
    {
        while(b[j] < a[i] && j < num2)
            tmp[k++] = b[j++];
        while(b[j] >= a[i] && i < num1)
            tmp[k++] = a[i++];
    }
    // 下面两个while循环与更下面的两个memcpy语句等价
    /*
    while(i<num1)
        tmp[k++] = a[i++];
    while(j<num2)
        tmp[k++] = b[j++];
    */
    memcpy(tmp+k, a+i, (num1-i)*sizeof(int));
    memcpy(tmp+k+num1-i, b+j,  (num2-j)*sizeof(int));

    memcpy(a, tmp, num1*sizeof(int));
    memcpy(b, tmp+num1, num2*sizeof(int)); 
    free(tmp);
}

void mergeSort(int *a, int num)
{
    //合并排序
    if(num!=1)
    {
        mergeSort(a, num/2);
        mergeSort(a+num/2, num-num/2);
        merge(a, a+num/2, num/2, num-num/2);
    }
}

// 堆排序, 采用大顶堆

void heapify(int *a, int num, int pos)
{
    int left, right;
    int i=pos;
    while(i<num)
    {
        if (2*pos+1<num && a[pos] < a[2*pos+1] || 2*pos+2 < num && a[pos] < a[2*pos+2])
        {
            if (2*pos+2 < num && a[2*pos+1]<a[2*pos+2])
            {
                swap(a+pos, a+2*pos+2);
                i = 2*pos+2;
                pos = i;
            }
            else
            {
                swap(a+pos, a+2*pos+1);
                i = 2*pos+1;
                pos = i;
            }
        }
        else
            break;
    }
}

void createHeap(int *a, int num)
{
    int i;
    for(i=num/2-1; i>=0; i--)
        heapify(a, num, i);
}

void heapSort(int *a, int num)
{
    createHeap(a, num);
    int i;
    for(i=num-1; i>=0; i--)
    {
        swap(a+i, a);
        heapify(a, i, 0);
    }
}


void print(int a[], int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%d ", *(a+i));
    printf("\n");
}

// 二叉搜索树进行排序
typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
}Tree;

void insert(Tree* root, Tree *node)
{
    if (root == NULL)
        return;
    if (node->data < root->data)
    {
    if (root->left == NULL)
        root->left = node;
    else
        insert(root->left, node);
    }
    else
    {
    if (root->right == NULL)
        root->right = node;
    else
        insert(root->right, node);
    }
}
 

Tree* create(int a[], int n)
{
    if (n < 1)
        return NULL;

    Tree *root = (Tree*)malloc(sizeof(Tree));
    //Tree *node;
    root->data = a[0];
    root->left = NULL;
    root->right = NULL;
    int i;
    for(i=1; i<n; i++)
    {
        Tree* node = (Tree *)malloc(sizeof(Tree));
        node->data = a[i];
        node->left = NULL;
        node->right = NULL;
        insert(root, node);
    }
    return root;
}

void printTree(Tree* root)
{
    //对于二叉搜索树,中序遍历的结果即为升序
    if(root != NULL)
    {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}

void freeTree(Tree *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    if (root->left == NULL && root->right == NULL)
        free(root);
}

// 堆排序


int main()
{
    //本例中所有的排序都是升序
    int a[] = {10, 2, 3,56, 25, 1, 1, 45, 45, 78, 10};
    int b[] = {2, 3, 5, 6};
    printf("The orginal sequence:\n");
    int num = sizeof(a)/sizeof(int);
    print(a, num);

#if 0   // for bubble sort
    printf("The ordered sequence by bubbleSort:\n");
    bubbleSort2(a, num);
    print(a, num);

#endif

#if 0   // for select sort

    printf("The ordered sequence by insertSort:\n");
    selectSort(a, num);
    print(a, num);

#endif

#if 0   // for insert sort

    printf("The ordered sequence by insertSort:\n");
    insertSort(a, num);
    print(a, num);

#endif

#if 0   // for shell sort

    printf("The ordered sequence by shellSort:\n");
    shellSort(a, num);
    print(a, num);

#endif



#if 0   // for quick sort

    printf("The ordered sequence by quickSort:\n");
    quickSort(a, num);
    print(a, num);

#endif

#if 0   // for binary searh tree sort

    Tree *root = create(a, num);
    printf("The ordered sequence by binary search tree:\n");
    printTree(root);
    printf("\n");
    freeTree(root); //函数中申请的动态内存,也需要显式地释放

#endif

#if 0   // for merge sort

    printf("The ordered sequence by mergeSort:\n");
    mergeSort(a, num);
    print(a, num);

#endif

#if 1   // for heap sort

    printf("The ordered sequence by heapSort:\n");
    heapSort(a, num);
    print(a, num);

#endif


   


    return 0;
}


