#include<stdio.h>
#include<stdlib.h>

int binary_search_recursive(int *a, int low, int high, int key)
{
    //递归的二分查找, 注意:low和high是前闭后开
    int mid;
    // 下面两种方式求取都是合适的,可以防止溢出
    //mid = low + (high - low)/2; // 为了防止整形溢出
    mid = ((unsigned int)low + (unsigned int)high) >> 1;

    if (low == high && a[mid] != key)
        return -1;
    if (a[mid] > key)   // 为了减少 三路比较中的平均比较次数,尽量将较大可能的比较置于前面
        return binary_search_recursive(a, low, mid, key);
    else if (a[mid] < key)
        return binary_search_recursive(a, mid+1, high, key);
    else
        return mid;
}

int binary_search_non_recursive(int *a, int low, int high, int key)
{
    //非递归的二分查找, 注意:low和high是前闭后开
    int mid;
    while(low < high)
    {
        mid = low + (high - low)/2; // 为了防止整形溢出
        if (a[mid] < key)    // 为了减少 三路比较中的平均比较次数,尽量将较大可能的比较置于前面
            low = mid + 1;
        else if (a[mid] > key)
            high = mid;
        else
            return mid;
    }
    if (low == high && a[low] == key)
        return low;
    return -1;
}

// 树的查找
// 二叉树

typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
}Tree;


void insertNode(Tree* root, int *a, int num)
{
    int i;
    for(i=0; i<num; i++)
    {
        Tree* node = (Tree*)malloc(sizeof(Tree));
        node->left = NULL;
        node->right = NULL;
        node->data = a[i];
        if (root->left == NULL)
            root->left = node;
        else
        {
            root->right = node;
            root = root->left;
        }
    }
}

Tree* createTree(int *a, int num)
{
    //  注意此处使用队列来辅助建立二叉树
    //  这点必须要掌握
    int i=0;
    Tree *queue[num];   //指针数组
    int head = 0;
    int tail = 0;

    Tree* root= (Tree*)malloc(sizeof(Tree));
    root->left = NULL;
    root->right = NULL;
    root->data = a[0];

    queue[tail++] = root;
    for(i=1; i<num; i++)
    {
        Tree *node= (Tree*)malloc(sizeof(Tree));
        node->data = a[i];
        root = queue[head];
        if (root->left == NULL)
        {
            root->left = node;
        }
        else 
        {
            root->right = node;
            head++;
        }
        queue[tail++] = node;
    }
    return queue[0];
}

void preOrderTraverse(Tree *root)
{
    // 也称作 Depth-First Traversal, 深度优先遍历
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrderTraverse(root->left);
    preOrderTraverse(root->right);
}
void preOrderTraverse_non_recursive(Tree *root)
{
    int num = 20; // 使用足够大的空间, 实际上, 只需要树的高度大小的队列即可
    Tree* stack[num];
    int top;
    top = 0;
    stack[top++] = root;
    while(top)
    {
        // 当前节点出栈的同时, 右节点和左节点同时进栈
        root = stack[--top];
        printf("%d ", root->data);
        if (root->right != NULL)
            stack[top++] = root->right;
        if (root->left != NULL)
            stack[top++] = root->left;
    }
}


void inOrderTraverse(Tree *root)
{
    if (root == NULL)
        return;
    inOrderTraverse(root->left);
    printf("%d ", root->data);
    inOrderTraverse(root->right);
}
void inOrderTraverse_non_recursive(Tree *root)
{
    // 下面的非递归的方法使用parent记录被访问者的父节点,并置相应的节点为NULL
    // 问题: 这样会更改树的结构
    // 是否可以采用记录访问过节点的方法?
    int num = 20; // 使用足够大的空间, 实际上, 只需要树的高度大小的队列即可
    Tree* stack[num];
    int top;
    top = 0;
    Tree *parent;
    stack[top++] = root;
    while(top)
    {
        root = stack[top-1];
        if (root->left == NULL)
            parent = stack[top-2];
        while(root->left)
        {
            stack[top++] = root->left;
            parent = root;
            root = root->left;
        }
        root = stack[--top];
        if (root->right)
            stack[top++] = root->right;
        printf("%d ", root->data);
        if (parent->left == root)
            parent->left = NULL;
        else if(parent->right == root)
            parent->right = NULL;
    }
}

void inOrderTraverse_non_recursive2(Tree *root)
{
    // 下面的非递归的方法,无须记录父节点, 也不更改树的结构

    int num = 20; // 使用足够大的空间, 实际上, 只需要树的高度大小的队列即可
    Tree* stack[num];
    int top;
    top = 0;
    Tree *p;
    p = root;
    while(p || top != 0)
    {
        while(p)
        {
            stack[top++] = p;
            p = p->left;
        }
        p = stack[--top];
        printf("%d ", p->data);
        p = p->right;
    }
}

void postOrderTraverse(Tree *root)
{
    if (root == NULL)
        return;
    postOrderTraverse(root->left);
    postOrderTraverse(root->right);
    printf("%d ", root->data);
}

void postOrderTraverse_non_recursive(Tree *root)
{
     // 下面的非递归的方法
    int num = 20; // 使用足够大的空间, 实际上, 只需要树的高度大小的队列即可
    Tree* stack[num];
    int top;
    top = 0;
    Tree *p;
    p = root;
    while(p || top)
    {
        if(p)
        {
            stack[top++] = p;
            p = p->left;
        }
        else
        {
            p = stack[top-1];
            if (p->right == NULL || p->right == root)   //如果右节点为空,或者已经访问过
            {
                printf("%d ", p->data);
                top -= 1;
                root = p;   //这是最关键的一步,使用root来记录已经访问过的当前节点
                p = NULL;
            }
            else
                p = p->right;
        }
    }
}
void broadFirstTraverse(Tree *root)
{
    // 广度优先遍历, 即按层进行遍历
    // 使用队列进行辅助
    int num = 20;   //取足够大的队列
    Tree *queue[num];
    int head, tail;
    head = tail = 0;
    queue[tail++] = root;
    while(head != tail) //队列不为空
    {
        root = queue[head++];
        printf("%d ", root->data);
        if (root->left != NULL)
            queue[tail++] = root->left;
        if (root->right != NULL)
            queue[tail++] = root->right;
    }

}

void print(int *a, int num)
{
    int i;
    for(i=0; i<num; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void freeTree(Tree *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main()
{
    int a[] = {0,2,5,6,7,45,123,256,456,457,458,459,500};
    int num = sizeof(a)/sizeof(int);
    printf("The original sequence:");
    print(a, num);
    int b = 1;
    printf("searching %d from the sequence=>got %d\n",b,  binary_search_recursive(a, 0, num, b));
    b = 500;
    printf("searching %d from the sequence=>got %d\n",b,  binary_search_non_recursive(a, 0, num, b));


    Tree *root = createTree(a, num);

    printf("Pre-order traverse recrusive:");
    preOrderTraverse(root);
    printf("\n");

    printf("Pre-order traverse non-recrusive:");
    preOrderTraverse_non_recursive(root);
    printf("\n");

    printf("In-order traverse recrusive:");
    inOrderTraverse(root);
    printf("\n");
#if 1
    printf("In-order traverse non-recrusive:");
    inOrderTraverse_non_recursive2(root);
    printf("\n");
#endif

    printf("Post-order traverse recrusive:");
    postOrderTraverse(root);
    printf("\n");

    printf("Post-order traverse non-recrusive:");
    postOrderTraverse_non_recursive(root);
    printf("\n");

    printf("Broad-First traverse:");
    broadFirstTraverse(root);
    printf("\n");

    freeTree(root);
    return 0;
}
