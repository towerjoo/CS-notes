#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MaxVertexNum 20

typedef struct node
{//边表结点
    int adjvex; //邻接点域
    struct node *next; //链域
    //若要表示边上的权，则应增加一个数据域
}EdgeNode;
typedef struct vnode
{ //顶点表结点
    int vertex; //顶点域
    EdgeNode *firstedge;//边表头指针
}VertexNode;
typedef VertexNode AdjList[MaxVertexNum];//AdjList是邻接表类型
//typedef VertexNode *AdjList;//AdjList是邻接表类型
typedef struct
{
    AdjList adjlist;//邻接表
    int n,e; //图中当前顶点数和边数 
}ALGraph; //对于简单的应用，无须定义此类型，可直接使用AdjList类型。

void initGraph(AdjList graph)
{
    int i;
   for(i=0; i<MaxVertexNum; i++)
   {
       graph[i].vertex = 0;
       graph[i].firstedge = NULL;
   }
}

// 从邻接矩阵形式得到邻接表表示
void createGraph(AdjList graph, int **a, int m, int n)
{
    int i, j;
    for(i=0; i<m; i++)
    {
        graph[i].vertex = i;
        for(j=0; j<n; j++)
        {
            if (a[i][j] == 1)
            {
                EdgeNode *tmp = graph[i].firstedge;
                if (tmp == NULL)
                {
                    tmp = (EdgeNode*)malloc(sizeof(EdgeNode));
                    tmp->next = NULL;
                    tmp->adjvex = i;
                    graph[i].firstedge = tmp;
                }

                while(tmp && tmp->next)
                    tmp = tmp->next;
                EdgeNode *node = (EdgeNode*)malloc(sizeof(EdgeNode));
                node->adjvex = j;
                node->next = NULL;
                tmp->next = node;
            }
        }
    }
}

void DepthFirstTraverse(AdjList, int m)
{
    // 深度优先遍历
    int *visited = (int *)malloc(sizeof(int)*m);
    int i;
    for(i=0; i<m; i++)
        visited[i] = 0;


}

void BroadthFirstTraverse(AdjList, int m)
{
    // 广度优先遍历

}

void freeGraph(AdjList graph, int m)
{
    int i;
    for(i=0; i<m; i++)
    {
        EdgeNode *p = graph[i].firstedge;
        EdgeNode *q;
        while(p)
        {
            q = p;
            p = p->next;
            free(q);
        }
    }
}

int main()
{
    int **matrix;
    int m = 5;
    int n = 5;
    matrix = (int **)malloc(sizeof(int*)*m);
    int i, j;
    for(i=0; i<m; i++)
        *(matrix+i) = (int *)malloc(sizeof(int)*n);
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            matrix[i][j] = j % 2;
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    AdjList graph;
    initGraph(graph); 
    createGraph(graph, matrix, m, n);
    for(i=0; i<m; i++)
    {
        printf("%d:", graph[i].vertex);
        EdgeNode *p = graph[i].firstedge;
        while (p != NULL)
        {
            printf("%d==>", p->adjvex);
            p = p->next;
        }
        printf("NULL  ");
    }

    printf("\n");

    for(i=0; i<m; i++)
        free(matrix[i]);
    free(matrix);

    freeGraph(graph, m);

    return 0;
}
