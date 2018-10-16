题意：
给一个节点N，给一个有向的弧times[i] = (u, v, w)，问到达所有结点的的时间是多少？
法一：Dijkstra算法
T(n) = O(n^2);
思路：
1.本题利用图，实际上是求单源到所有结点最短路径的最大值
2.首先构造出图中必备的存储结构：
#需要一个矩阵来存点边的关系和权重。vector<vector<int>> value(101,vector<int>(101,-1));是一个101行，vector<int>(101,-1)列，初始化为-1的n*n矩阵
注意矩阵大小和结点个数相关。后遍历times把有权重的边对应到矩阵中
#用queue来找从k开始的所有结点 queue<int> q{{K}};不可写成queue<int> q{K}！
#用vector来存储从K到各个结点的最小路径，vector<int> shortest(N+1,INT_MAX);注意初始化，K的位置为0
3.当栈不为空的时候，取出栈顶元素（q.front()方法),从列上开始循环，在矩阵中比较对应的位置与前一位加上到该位置距离的大小，每次得到最小的值，贪心的策略。
4.如果有更小的，那么放到vector中，注意还需要设置一个unordered_set（无序）,如果没有遍历过当前点，那么push到队列中
5.循环vector，返回最大的元素
6.最后还需要判断是否等于INT_MAX，如果等于返回-1，不等返回ret
注意：
因为结点没有序号为0，所有循环都是从1开始的，边界等于结点数
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<int>> value(101,vector<int>(101,-1));
        for(auto &e : times) value[e[0]][e[1]] = e[2];
        queue<int> q{{K}};
        int ret = 0;
        vector<int> shortest(N+1,INT_MAX);
        shortest[K] = 0;
        while(!q.empty()){
            unordered_set<int> visited;
            for(int i = q.size();i > 0; --i){
                int u = q.front();
                q.pop();
                for(int v = 1; v <= 100; ++v){
                    if(value[u][v] != -1 && shortest[v] > value[u][v]+shortest[u]){
                        if(!visited.count(v)){
                            visited.insert(v);
                            q.push(v);
                        }
                        shortest[v] = value[u][v]+shortest[u];
                    } 
                }
            }
        }
        for(int i = 1; i <= N;++i){
            ret = max(shortest[i],ret);
        }
        return ret == INT_MAX ? -1 :ret;
    }
};
法二：Bellman-Ford算法
T(n) = O(nE);n为结点个数，E为边数
注意因为没有第0个结点因此要从N+1开始，或者也可以把初始值设置为shortest[K-1]
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<int> shortest(N+1,INT_MAX);
        shortest[K] = 0;
        int res = 0;
        for(int i = 0; i< N;++i){
            for(auto &e: times){
                if(shortest[e[0]] != INT_MAX && shortest[e[1]] > shortest[e[0]] + e[2]){
                    shortest[e[1]] = shortest[e[0]] + e[2];
                }
            }
        }
        for(int i = 1; i <= N; ++i){
            res = max(res,shortest[i]);
        }
        return res == INT_MAX? -1: res;
    }
};
知识补充：
1.图的概述：
图分为有向图和无向图两种。
在有向图中，每个节点叫做顶点，每条带箭头的边叫做弧。一个顶点的入度等于指向它的箭头书，出度等于该节点射出的箭头数。
无向图中有边连结的相邻的两个顶点叫做邻接点。与顶点相连的边的数目称为顶点的度。
有时图中的边或者弧具有与它有关的数，这种与边或者弧有关的数叫做权，带权的图通常叫做网。

无向图中，任意两个顶点之间都有边连结的图叫完全图，边数 = n(n-1)/2;具有n(n-1)条弧的有向图称为有向完全图。
无向图中，任意两个顶点都可以连通的图叫做连通图，包括间接的或直接的连通。连通分量是无向图中的极大连通子图。
有向图中，如果从vi -> vj, vj -> vi都存在路径，那么图G为强连通图。
具有最少边数的可以使各个顶点连通的图叫做生成树，边数 = n-1;

2.图的存储结构：
图的存储结构没有顺序结构，都是链式结构。通常包括了顶点的集合和弧的集合。
-------------------------------------------------------------
#####数组表示法，邻接矩阵（有向图&无向图）
图的邻接矩阵（Adjacency Matrix)存储方式是用两个数组来表示图。一个一维的数组存储图中顶点信息，一个二维数组（称为邻接矩阵）存储图中的边或弧的信息。
###针对无向图：
设图G有n个顶点，则邻接矩阵是一个n*n的方阵
定义为：arc[i][j] = 1,若(vi,vj)属于E。
       arc[i][j] = 0,若(vi,vj)不属于E。
在无向图中，因为没有方向，所以矩阵的主对角线两边是对称的，左为v1的行表示v1结点连接的点，如果存在，对应列为1，不存在，为0.
这样每一行为1的值的和，表示该行的结点的度。
###针对有向图：
和无向图类似，只是弧的方法唯一，因此矩阵不对称。那么针对某一个结点比如v1来说，v1一行表示v1的出度，v1一列表示v1的入度。
###针对网：
定义为：arc[i][j] = W,若(vi,vj)属于E。
       arc[i][j] = 0,若i=j。
       arc[i][j] = ∞,若(vi,vj)不属于E。
代码示例（无向网图）：
#include<iostream>
using namespace std;

#define MAXVEX 100/* 最大顶点数，自定义*/
#define INFINITY  65535 /* 表示权值的无穷*/

typedef int EdgeType;/* 边上的权值类型，自定义 */
typedef char VertexType;/* 顶点类型，自定义*/

typedef struct
{
    VertexType vexs[MAXVEX];/* 顶点表 内放顶点的信息*／
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表，二维数组，大小是n*n*/
    int numNodes, numEdges;/* 图中当前的顶点数和边数  */
} MGraph;

/* 建立无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *Gp)//定义一个图指针为Gp
{
    int i, j, k, w;
    cout << "请输入顶点数和边数（空格分隔）：" << endl;
    cin >> Gp->numNodes >> Gp->numEdges;//表示图的结点数和边数
    cout << "请输入顶点信息（空格分隔）：" << endl;
    for (i = 0; i < Gp->numNodes; i++)
        cin >> Gp->vexs[i];//将结点依次放到结点矩阵中
    for (i = 0; i < Gp->numNodes; i++)
    {
        for (j = 0; j < Gp->numNodes; j++)//对邻接矩阵初始化，对角线上的点为0，其余为∞
        {
            if (i == j)
                Gp->arc[i][j] = 0;/* 顶点没有到自己的边*/
            else
                Gp->arc[i][j] = INFINITY;/* 邻接矩阵初始化 */
        }
    }

    for (k = 0; k < Gp->numEdges; k++)
    {
        cout << "请输入边（vi, vj)的上标i，下标j和权值w（空格分隔）:" << endl;
        cin >> i >> j >> w;
        Gp->arc[i][j] = w;//将图的权值放到对应的矩阵汇总
        Gp->arc[j][i] = Gp->arc[i][j];/* 因为是无向图，矩阵对称 */
    }
}

int main(void)
{
    MGraph MG;//创建一个图结构
    CreateMGraph(&MG);//创建图

    return 0;
}
---------------------------------------
代码示例（有向图）：
#include<stdio.h>
#define  MAX_VERTEX  4
typedef char DataType;                 //图中元素的目标数据类型 
typedef struct    
{                  
    DataType vertexArr[MAX_VERTEX];        //顶点元素数组 
    int arcArr[MAX_VERTEX][MAX_VERTEX];   //弧矩阵二维数组 
}ArrayGraph;
 
void ArrayGraph_init(ArrayGraph *pGraph);
void ArrayGraph_create(ArrayGraph *pGraph);
void ArrayGraph_show(ArrayGraph *pGraph);

int main()
{
    ArrayGraph g;//图结构，是一个图指针
    ArrayGraph_init(&g);//引用这个图指针
    ArrayGraph_create(&g);
    ArrayGraph_show(&g);
    return 0;
}
//初始化为一个无圈图 ，也就是弧矩阵中，主对角线元素都是0 
void ArrayGraph_init(ArrayGraph *pGraph)
{ 
    for (int i = 0; i < MAX_VERTEX; i++)
        pGraph->arcArr[i][i] = 0;
}
void ArrayGraph_create(ArrayGraph *pGraph)
{
    for (int i = 0; i < MAX_VERTEX; ++i)  //填充顶点数组
    {
        printf("输入第%d个顶点值\n",i+1);
        scanf(" %c",&(pGraph->vertexArr[i])); 
    }
    for (int j = 0; j <MAX_VERTEX; ++j)   //填充边关系 
    {
        for (int i = j+1; i < MAX_VERTEX; ++i)
        {
            printf("若元素%c有指向%c的弧，则输入1，否则输入0\t",pGraph->vertexArr[i],pGraph->vertexArr[j]);
            scanf("%d",&( pGraph->arcArr[j][i]));
            
            printf("若元素%c有指向%c的弧，则输入1，否则输入0\t",pGraph->vertexArr[j],pGraph->vertexArr[i]);
            scanf("%d",&( pGraph->arcArr[i][j]));
        }
    }
}
void ArrayGraph_show(ArrayGraph *pGraph)
{
    printf("\n\n顶点元素如下\n");
    for (int i = 0; i < MAX_VERTEX; ++i)
    {
        printf("%-5c", pGraph->vertexArr[i]);
    }
    printf("\n\n");

    puts("弧矩阵如下\n\n"); 
    printf("%-2c",' ');
    for(int i=0;i<MAX_VERTEX;++i)
      printf("%-5c",pGraph->vertexArr[i]);
    putchar('\n');  
    
    for (int j = 0; j <MAX_VERTEX; ++j)
    {
        printf("%-2c",pGraph->vertexArr[j]);
        for (int i = 0; i < MAX_VERTEX; ++i)
        {
            printf("%-5d",pGraph->arcArr[i][j]);
 
        }
        putchar('\n');
    }
    putchar('\n');  
}
-------------------------------------------------------------
#####邻接表（有向图&无向图）
所有的顶点用一个一维数组存储，同时对于顶点数组中，每个数据元素还需要存储指向第一个邻接点的指针，以便于查找该顶点的边信息。
头结点：数据域data+链域firstarc
图中每个顶点vi的所有邻接点构成一个线性表，由于邻接点的个数不定，所以用单链表存储，无向图称为顶点vi的边表，有向图称为顶点vi作为弧尾的出边表。
表结点：邻接点域adjvex+链域nextarc+数据域info
在无向图中，顶点i的度为第i个链表中的结点数。
在有向图中，顶点i的出度为第i个链表中的结点数。
在有向图中，如果顶点为弧头的表容易得到顶点的入度，即逆邻接表。即表头结点连接的是指向该结点的结点。
代码示例（无向图）
#include<iostream>
using namespace std;

#define MAXVEX 100 /* 最大顶点数,自定义 */
typedef char VertexType; /* 顶点类型，自定义 */
typedef int EdgeType; /* 边上的权值类型，自定义 */

typedef struct EdgeNode/* 边表结点  */
{
    int adjvex;/* 邻接点域,存储顶点位置*/
    EdgeType weight;/* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
} EdgeNode;

typedef struct VextexNode/* 顶点表结点 */
{
    VertexType data;/* 顶点域,存储顶点信息 */
    EdgeNode *firstedge;/* 边表头指针 */
} VextexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;//图中的邻接表
    int numNodes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;//建立图结构

void CreateALGraph(GraphAdjList *Gp)
{
    int i, j, k;
    EdgeNode *pe;//表结点指针
    cout << "输入顶点数和边数(空格分隔）:" << endl;
    cin >> Gp->numNodes >> Gp->numEdges;//输入结点数和边数

    for (i = 0 ; i < Gp->numNodes; i++)
    {
        cout << "输入顶点信息：" << endl;
        cin >> Gp->adjList[i].data;//第i个顶点的邻接表属性中的第一个值
        Gp->adjList[i].firstedge = NULL;/* 将每一个结点的边表置为空表 */
    }

    for (k = 0; k <  Gp->numEdges; k++)/* 建立边表 */
    {
        cout << "输入边(vi,vj)的顶点序号i,j（空格分隔）:" << endl;
        cin >> i >> j;
        pe = (EdgeNode *)malloc(sizeof(EdgeNode));//malloc 向系统申请分配指定size个字节的内存空间。返回类型是 EdgeNode * 类型。
        pe->adjvex = j;/* 邻接序号为j */
        /* 将pe的指针指向当前顶点上指向的结点 */
        pe->next = Gp->adjList[i].firstedge;
        Gp->adjList[i].firstedge = pe;/* 将当前顶点的指针指向pe */

        pe = (EdgeNode *)malloc(sizeof(EdgeNode));
        pe->adjvex = i;
        pe->next = Gp->adjList[j].firstedge;
        Gp->adjList[j].firstedge = pe;

    }
}
int main(void)
{
    GraphAdjList GL;//建立图结构
    CreateALGraph(&GL);//初始化图

    return 0;
}
-------------------------------------------------------------
#####十字链表（有向图）
为了弥补在邻接表中只能找到弧的出度，在逆邻接表中只能找到弧的入度的问题。是邻接表和逆邻接表的结合。
顶点结点：数据域+firstin(逆邻接表）+firstout（邻接表）
弧结点（每个域表示一条弧）：弧尾，弧头，逆邻接表，邻接表，数据域
顶点结构：[data | firstin | firstout ]
其中firstin表示入边表头指针，指向该顶点的入边表中的第一个结点firstout表示出边表头指针，指向该顶点的出边表中的第一个结点。
弧结构：[tailvex | headvex | headlink | taillink]
其中tailevex是指弧起点在顶点表中的下标，headvex类似。headlink是指入边表指针域，指向终点相同的下一条边，taillink类似。如果是网，可再增加一个权值域。
画图的时候首先以每个结点为起点，先找邻接表。邻接表指向弧的弧尾。最后标记为空。
再以每个结点为起点，找逆邻接表。逆邻接表指向弧头。最后标记为空。
代码示例：包括十字链表的创建，初始化，查找度，DFS和BFS
#include <iostream>
#include <string>
#include <queue>
using namespace std;
 
#define MAXVEXSIZE 10
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status;
int visited[MAXVEXSIZE];  //指示顶点是否被访问
 
 
typedef string VertexType;  //顶点类型
typedef struct ArcType  
{
	int tailvex; //弧头下标
	int headvex;  //弧尾下标
	int weight;  //权值
	ArcType* headlink;  //指向下一个同一弧头的弧
	ArcType* taillink; //指向下一个同一弧尾的弧
}ArcType;
typedef struct  
{
	VertexType data;
	ArcType* firstin; //指向第一条入弧
	ArcType* firstout; //指向第一条出弧
 
}VertexNode;
typedef VertexNode CrossList[MAXVEXSIZE];
 
typedef struct  
{
	CrossList crossList; //十字链表
	int iVexNum;
	int iArcNum;  
}CrossGraph;
 
 
//由顶点值得到顶点索引
int GetIndexByVertexVal( const CrossGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.crossList[i].data )
			return i;
	}
	return -1;
}
//创建有向图
Status CreateCrossGraph( CrossGraph& G )
{
	cout << "输入顶点个数以及边数：";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "请输入" << G.iVexNum << "个顶点:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.crossList[i].data;
		G.crossList[i].firstin = NULL;
		G.crossList[i].firstout = NULL;
	}
 
	cout << "请输入由两点构成的边(" << G.iArcNum << "条):";
	for ( int i = 0; i < G.iArcNum; ++i )
	{
		VertexType first;
		VertexType second;
		cin >> first >> second;
		int m = GetIndexByVertexVal( G, first );
		int n = GetIndexByVertexVal( G, second ); 
		if ( m == -1 || n == -1 )
			return UNSUCCESS;
 
		ArcType* pArc = new ArcType;
		memset( pArc, 0, sizeof(ArcType) );
		pArc->headvex = m;
		pArc->tailvex = n;
		pArc->weight = 0;  //权值暂时不用
 
		pArc->taillink = G.crossList[m].firstout;//表头插入法
		G.crossList[m].firstout = pArc;
 
		pArc->headlink = G.crossList[n].firstin;//表头插入法
		G.crossList[n].firstin = pArc;
	}
	return SUCCESS;
}
//求顶点的度，在十字链表中还是挺方便的，因为其是邻接表与逆邻接表的结合体
int GetVertexDegree( const CrossGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //得到顶点的在顶点表中的索引
	if ( -1 == m )
		return -1;
	
	int TD = 0;
	//先求出度
	ArcType* pArcOut = G.crossList[m].firstout;
	while ( pArcOut )
	{
		++TD;
		pArcOut = pArcOut->taillink;
	}
 
	//再累加入度
	ArcType* pArcIn = G.crossList[m].firstin;
	while( pArcIn )
	{
		++TD;
		pArcIn = pArcIn->headlink;
	}
	return TD;
}
//深度优先遍历
void DFS( const CrossGraph& G, int i )
{
	cout << G.crossList[i].data << " ";
	visited[i] = true;
 
	ArcType* pArc = G.crossList[i].firstout;
	while( pArc )
	{
		int iVex = pArc->tailvex;
		if ( !visited[iVex] )
		{
			DFS( G, iVex );
		}
		pArc = pArc->taillink;
	}
}
void DFSTraverse( const CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}
 
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			DFS( G, i );
		}
	}
}
//广度优先遍历
void BFSTraverse( const CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}
 
	queue<int> Q;
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			cout << G.crossList[i].data << " ";
			visited[i] = true;
			Q.push( i );
			 
			while ( !Q.empty() )
			{
				int iVex = Q.front();
				Q.pop();
 
				ArcType* pArc = G.crossList[iVex].firstout;
				while ( pArc )
				{
					int j = pArc->tailvex;
					if ( !visited[j] )
					{
						cout << G.crossList[j].data << " ";
						visited[j] = true;
						Q.push(j);
					}
					pArc = pArc->taillink;
				}
			}
		}
	}
}
//销毁图
void DestroyGraph( CrossGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		ArcType* pArc = G.crossList[i].firstout;
		while( pArc )
		{
			ArcType* q = pArc;
			pArc = pArc->taillink;
			delete q;
		}
		G.crossList[i].firstout = NULL;
		G.crossList[i].firstin = NULL;
	}
	G.iVexNum = 0;
	G.iArcNum = 0;
}
int main()
{
	//创建有向图
	CrossGraph G;
	CreateCrossGraph( G );
 
	//深度优先遍历图
	cout << "深度优先遍历:" << endl;
	DFSTraverse( G );
	cout << endl << endl;
 
	//广度优先遍历图
	cout << "广度优先遍历:" << endl;
	BFSTraverse( G );
	cout << endl << endl;
 
	//结点的度
	cout << "输入求度的结点:";
	VertexType v;
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;
 
	//销毁有向图
	DestroyGraph( G );
	return 0;
}
-------------------------------------------------------------
#####邻接多重表（无向图）
邻接表从图的每个顶点出发，表示所有与结点相连的结点，为一个结点的度，但是无法表示边的关系
邻接多重表和十字链表类似，从结点出发，链表中的结点表示边。

如果我们在无向图的应用中，关注的重点是顶点，那么邻接表是不错的选择，但如果我们更关注边的操作，比如对已访问过的边做标记，删除某一条边等操作，那就意味着，需要找到这条边的两个边表结点进行操作，这其实还是比较麻烦的。因此，我们也依照十字链表的方式，对表结点进行一下改造：
[ mark | ivex | ilink | jvex | jlink | info]
其中ivex和jvex是与某条边依附的两个顶点在顶点表中下标。ilink指向依附点ivex的下一条边（邻接表）,jlink指向依附点jvex的下一条边（逆邻接表），这就是邻接多重表结构。
mark表示是否被搜索过。

代码部分：
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAXVEXSIZE 10
#define SUCCESS 1
#define UNSUCCESS 0
typedef int Status;
int visited[MAXVEXSIZE];  //指示顶点是否被访问


typedef string VertexType;  //顶点类型
typedef struct ArcType//邻接表结构
{
	int ivex; //该弧依附的两点的位置
	int jvex; 
	int weight;  //权值
	ArcType* ilink;  //分别指向依附该弧的下一条弧
	ArcType* jlink; 
}ArcType;

typedef struct//头结点结构
{
	VertexType data;
	ArcType* firstArc; //指向第一条弧

}VertexNode;

typedef VertexNode MulAdjList[MAXVEXSIZE];
typedef struct//图的结构
{
	MulAdjList mulAdjList; //多重邻接表
	int iVexNum;//顶点个数
	int iArcNum;//边数 
}MulAdjGraph;


//由顶点值得到顶点索引
int GetIndexByVertexVal( const MulAdjGraph& G, VertexType val )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( val == G.mulAdjList[i].data )
			return i;
	}
	return -1;
}

//创建无向图
Status CreateCrossGraph( MulAdjGraph& G )
{
	cout << "输入顶点个数以及边数：";
	cin >> G.iVexNum >> G.iArcNum;
	cout << "请输入" << G.iVexNum << "个顶点:";
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		cin >> G.mulAdjList[i].data;
		G.mulAdjList[i].firstArc = NULL;
	}

	cout << "请输入由两点构成的边(" << G.iArcNum << "条):";
	for ( int i = 0; i < G.iArcNum; ++i )
	{
		VertexType first;
		VertexType second;
		cin >> first >> second;
		int m = GetIndexByVertexVal( G, first );
		int n = GetIndexByVertexVal( G, second ); 
		if ( m == -1 || n == -1 )
			return UNSUCCESS;

		ArcType* pArc = new ArcType;
		memset( pArc, 0, sizeof(ArcType) );
		pArc->ivex = m;
		pArc->jvex = n;
		pArc->weight = 0;  //权值暂时不用

		pArc->ilink = G.mulAdjList[m].firstArc;//表头插入法
		G.mulAdjList[m].firstArc = pArc;

		pArc->jlink = G.mulAdjList[n].firstArc;//表头插入法
		G.mulAdjList[n].firstArc = pArc;

	}
	return SUCCESS;
}


//求顶点的度
int GetVertexDegree( const MulAdjGraph& G, VertexType val )
{
	int m = GetIndexByVertexVal( G, val );  //得到顶点的在顶点表中的索引
	if ( -1 == m )
		return -1;

	int TD = 0;
	ArcType* pArc = G.mulAdjList[m].firstArc;
	while ( pArc )
	{
		++TD;
		if ( m == pArc->ivex )
			pArc = pArc->ilink;
		else
			pArc = pArc->jlink;
	}
	return TD;
}


//深度优先遍历
void DFS( const MulAdjGraph& G, int i )
{
	cout << G.mulAdjList[i].data << " ";
	visited[i] = true;

	ArcType* pArc = G.mulAdjList[i].firstArc;
	while( pArc )
	{
		int iVex = pArc->jvex;
		if ( !visited[iVex] )
		{
			DFS( G, iVex );
		}
		pArc = pArc->ilink;
	}
}
void DFSTraverse( const MulAdjGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}

	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			DFS( G, i );
		}
	}
}

//广度优先遍历
void BFSTraverse( const MulAdjGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		visited[i] = false;
	}

	queue<int> Q;
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		if ( !visited[i] )
		{
			cout << G.mulAdjList[i].data << " ";
			visited[i] = true;
			Q.push( i );

			while ( !Q.empty() )
			{
				int iVex = Q.front();
				Q.pop();

				ArcType* pArc = G.mulAdjList[iVex].firstArc;
				while ( pArc )
				{
					int j = pArc->jvex;
					if ( !visited[j] )
					{
						cout << G.mulAdjList[j].data << " ";
						visited[j] = true;
						Q.push( j );
					}
					pArc = pArc->ilink;
				}
			}

		}
	}
}


//销毁图
void DestroyGraph( MulAdjGraph& G )
{
	for ( int i = 0; i < G.iVexNum; ++i )
	{
		ArcType* pArc = G.mulAdjList[i].firstArc;
		while( pArc )
		{
			ArcType* q = pArc;
			pArc = pArc->ilink;

			int m = q->ivex;
			//在m号顶点下找当前边的前一条边
			ArcType* pmArc = G.mulAdjList[m].firstArc;
			ArcType* pmPreArc = NULL;
			while ( pmArc != q )
			{
				pmPreArc = pmArc;
				if ( m == pmArc->ivex )
				{
					pmArc = pmArc->ilink;
				}
				else 
				{
					pmArc = pmArc->jlink;
				}
			}
			if ( !pmPreArc )
			{
				G.mulAdjList[m].firstArc = q->ilink;
			}
			else
			{
				if ( m == pmPreArc->ivex )
				{
					pmPreArc->ilink = q->ilink;
				}
				else 
				{
					 pmPreArc->jlink = q->ilink;
				}
			}


			int n = q->jvex;
			//在n号顶点下找当前边的前一条边
			ArcType* pnArc = G.mulAdjList[n].firstArc;
			ArcType* pnPreArc = NULL;
			while ( pnArc != q )
			{
				pnPreArc = pnArc;
				if ( n == pnArc->ivex )
				{
					pnArc = pnArc->ilink;
				}
				else 
				{
					pnArc = pnArc->jlink;
				}
			}
			if ( !pnPreArc )
			{
				G.mulAdjList[n].firstArc = q->jlink;
			}
			else
			{
				if ( n == pnPreArc->ivex )
				{
					pnPreArc->ilink = q->jlink;
				}
				else 
				{
					pnPreArc->jlink = q->jlink;
				}
			}
			delete q;
		}
	}
	G.iVexNum = 0;
	G.iArcNum = 0;
}


int main()
{
	//创建无向图
	MulAdjGraph G;
	CreateCrossGraph( G );

	//深度优先遍历图
	cout << "深度优先遍历:" << endl;
	DFSTraverse( G );
	cout << endl << endl;

	//广度优先遍历图
	cout << "广度优先遍历:" << endl;
	BFSTraverse( G );
	cout << endl << endl;

	//结点的度
	cout << "输入求度的结点:";
	VertexType v;
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;

	cout << "再输入求度的结点:";
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;

	cout << "再输入求度的结点:";
	cin >> v;
	cout << "度为：" << GetVertexDegree( G, v ) << endl;

	//销毁无向图
	DestroyGraph( G );
	return 0;
}
3.图的遍历
-------------------------------------------------------------
DFS：
邻接矩阵：
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

#define MAXSIZE 9 /* 存储空间初始分配量 */
#define MAXEDGE 15
#define MAXVEX 9

typedef struct
{
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numVertexes, numEdges; /* 图中当前的顶点数和边数 */
} MGraph;

bool visited[MAXVEX];/* 访问标志的数组 */
/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph MG, int i)
{
    int j;
    visited[i] = true;//定义为已经访问
    cout << MG.vexs[i] << ' '; /* 打印顶点，也可以其它操作 */
    for (j = 0; j < MG.numVertexes; j++)
        if (MG.arc[i][j] == 1 && !visited[j])//如果<i，j>属于图中的边但是没有被访问到
            DFS(MG, j);/* 对为访问的邻接顶点递归调用 */
}
/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph MG)
{
    int i;
    for (i = 0; i < MG.numVertexes; i++)
        visited[i] = false;/* 初始所有顶点状态都是未访问过状态，在包含所有顶点的数组中操作*/
    for (i = 0; i < MG.numVertexes; i++)
        if (!visited[i])//如果未访问
            DFS(MG, i);/* 对未访问过的顶点调用DFS，若是连通图,只会执行一次*/
}

邻接表：
/* 邻接表结构****************** */
typedef struct EdgeNode /* 边表结点 */
{
    int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
    int weight;     /* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
} EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
    int in; //结点入度
    char data; /* 顶点域,存储顶点信息 */
    EdgeNode *firstedge;/* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;//邻接表
    int numVertexes, numEdges; /* 图中当前顶点数和边数 */
} graphAdjList, *GraphAdjList;

bool visited[MAXVEX];/* 访问标志的数组 */
/* 邻接表的深度优先递归算法 */
void DFS(GraphAdjList GL, int i)
{
    EdgeNode *p;
    visited[i] = true;
    cout << GL->adjList[i].data << ' '; /* 打印顶点，也可以其它操作 */
    p = GL->adjList[i].firstedge;//该顶点的邻接表的第一个元素
    while (p)
    {
        if (!visited[p->adjvex])
            DFS(GL, p->adjvex);/* 对为访问的邻接顶点递归调用 */
        p = p->next;
    }
}
/* 邻接表的深度遍历操作 */
void DFSTraverse(GraphAdjList GL)
{
    int i;
    for (i = 0; i < GL->numVertexes; i++)
        visited[i] = false;/* 初始所有顶点状态都是未访问过状态 */
    for (i = 0; i < GL->numVertexes; i++)
        if (!visited[i])
            DFS(GL, i);/* 对未访问过的顶点调用DFS，若是连通图,只会执行一次*/
}
-------------------------------------------------------------
BFS：
//邻接矩阵的广度遍历算法
void BFSTraverse(Graph g)
{
    int i, j;
    Queue q;
    for(i = 0; i < g.numVertexes; i++)
    {
        visited[i] = FALSE;//所有结点置为false
    }
    InitQueue(&q);
    for(i = 0; i < g.numVertexes; i++)//对每个顶点做循环
    {
        if(!visited[i])              //若是未访问过
        {
            visited[i] = TRUE;
            printf("%c ", g.vexs[i]); //打印结点，也可以其他操作
            EnQueue(&q, i);           //将此结点入队列
            while(!QueueEmpty(q))    //将队中元素出队列，赋值给
            {
                intm;
                DeQueue(&q, &m);        
                for(j = 0; j < g.numVertexes; j++)
                {
                    //判断其他顶点若与当前顶点存在边且未访问过
                    if(g.arc[m][j] == 1 && !visited[j])
                    {
                        visited[j] = TRUE;
                        printf("%c ", g.vexs[j]);
                        EnQueue(&q, j);
                    }
                }
            }
        }
    }
}
4.最短路径：（来源：https://blog.csdn.net/qibofang/article/details/51594673）
-------------------------------------------------------------
BFS／DFS:（解决单源最短路径）
DFS：单源最短路径
/***先输入n个结点，m条边，之后输入有向图的m条边，边的前两元素表示起始结点，第三个值表权值，输出1号城市到n号城市的最短距离***/  
/***算法的思路是访问所有的深度遍历路径，需要在深度遍历返回时将访问标志置0***/  
#include <iostream>  
#include <iomanip>  
#define nmax 110  
#define inf 999999999  
using namespace std;  
int n, m, minPath, edge[nmax][nmax], mark[nmax];//结点数，边数，最小路径，邻接矩阵，结点访问标记  
void dfs(int cur, int dst){  
    if(minPath < dst) return;//当前走过路径大于之前最短路径，没必要再走下去  
    if(cur == n){//临界条件，已经到达目标结点
        if(minPath > dst) minPath = dst;  
        return;  
    }  
    else{  
        int i;  
        for(i = 1; i <= n; i++){  
            if(edge[cur][i] != inf && edge[cur][i] != 0 && mark[i] == 0){//判断是否有路，是否已经走过这个结点
                mark[i] = 1;//走过即标记
                dfs(i, dst+edge[cur][i]); //从i城市出发， 
                mark[i] = 0;//探索完成之后归0，便于再次探索          
            }  
        }  
        return;  
    }  
}  
  
int main(){  
    while(cin >> n >> m && n != 0){  
        //初始化邻接矩阵  
        int i, j;  
        for(i = 1; i <= n; i++){  
            for(j = 1; j <= n; j++){  
                edge[i][j] = inf;  
            }  
            edge[i][i] = 0;  
        }  
        int a, b;  
        while(m--){  
            cin >> a >> b;  
            cin >> edge[a][b];  
        }  
        //以dnf(1)为起点开始递归遍历  
        memset(mark, 0, sizeof(mark));  
        minPath = inf;  
        mark[1] = 1;//访问1号结点
        dfs(1, 0);//从1号结点出发，0表示当前已经走过的路程
        cout << minPath << endl;  
    }  
    return 0;  
}  
运行结果：
5 8
1 2 2
1 5 10
2 3 3
2 5 7
3 1 4
3 4 4
4 5 5
5 3 3
9
BFS：
更适用于所有边的权值相同的情况（情景：从A到B最少转机次数）
-------------------------------------------------------------
迪杰克斯特拉算法Dijkstra Algorithm：（单源最短路径）（基于贪心策略）
时间复杂度O(n(^2)
所谓贪心算法是指，在对问题求解时，总是做出在当前看来是最好的选择。也就是说，不从整体最优上加以考虑，他所做出的仅是在某种意义上的局部最优解。
基本思想：每次找到离源点最近的一个顶点，把该顶点的值确认，后以该顶点为中心进行扩展，最终得到最短路径。
步骤：
1.将所有的顶点分成两部分，已知的最短路程的顶点P和未知最短路径的顶点集合Q。
最开始P中只有一个顶点，我们用book来记录哪些点在P中，book[i] == 1, 表示在P中，book[i] == 0表示在Q中。
2.设置源点s到自己的最短路径是0，即dis[s] = 0;
如果有源点能直接到达的顶点i,把dis[i]设为e[s][i],不能的话设置为∞
3.在集合Q中选择一个离源点最近的顶点u,即dis[u]最小，加入P。考察所有以点u为起点的边，对每一条边进行松弛操作。
例如存在一条从u到v的边，可以通过将边u->v添加到尾部来拓展一条从s到v的路径，长度为dis[u]+e[u][v],如果比dis[v]小，那么可以用新值来代替
4，重复3，直到Q为空，dis数组中的值就是源点到所有点的最短路径
#define inf 99999999
/***构建邻接矩阵edge[][],且1为源点***/
for(i = 1; i <= n; i++) dst[i] = edge[1][s]；//边初始化
for(i = 1; i <= n; i++) book[i] = 0;//book初始化
book[1] = 1;
for(i = 1; i <= n-1; i++){
	//找到离源点最近的顶点u，称它为新中心点
	min = inf;
	for(j = 1; j <= n; j++){
		if(book[j] == 0 && dst[j] < min){
			min = dst[j];
			u = j;
		}
	}
	book[u] = 1;
	//更新最短路径数组
	for(k = 1; k <= n; k++){
		if(edge[u][k] < inf && book[k] == 0){
			if(dst[k] > dst[u] + edge[u][k])
				dst[k] = dst[u] + edge[u][k];			
		}
	}
}
本算法不能有负权边。
-------------------------------------------------------------
弗洛伊德算法Floyd-Warshall Algorithm（多源最短路径）
在邻接矩阵中直接对每个结点的值进行更新，核心思想是最开始只允许经过1号顶点进行中转，接下来允许1，2号中转，最后允许1-n号之间中转。
时间复杂度O(n^3),空间复杂度O(n^2)
核心算法：
#define inf 99999999
for(k = 1; k <= n; k++){
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			if(Floyd[i][k] < inf && Floyd[k][j] < inf && Floyd[i][j] > Floyd[i][k] + Floyd[k][j])//正无穷与一个数相加得到一个大于正无穷的数字是不允许的
				Floyd[i][j] = Floyd[i][k] + Floyd[k][j];
		}
	}
}
Floyd-Warshall算法可以处理负权边，但是不能处理负权回路，因为负权回路有可能没有最短路径。
-------------------------------------------------------------
贝尔曼福特算法Bellman-Ford Algorithm（单源最短路径，负权边）
时间复杂度O(nm),空间复杂度O(m)
#define inf 999999999
for(i = 1; i <= n; i++) dst[i] = inf;
dst[1] = 0;
for(k = 1; k <= n-1; k++){
	check = 0;//用来标记本轮松弛数组dis是否会发生更新
	for(i = 1; i <= m; i++){
		if(dst[e[i]] > dst[s[i]] + w[i]){
			dst[e[i]] = dst[s[i]] + w[i];
			check = 1;
		}
	}
	if(check == 0) break;
}
//检测负权回路
flag = 0;
for(i = 1; i <= m; i++){
	if(dst[e[i]] > dst[s[i]] + w[i])
		flag = 1;
}
if(flag) cout << "此图含有负权回路";
