﻿#include <iostream>
#include <algorithm>
using namespace std;

struct HuffmanNode
{
    int index;
    int weight;
	int parent, lchild, rchild;
};
// 定义结点的排序规则，sort算法需要使用这个重载的运算符
bool operator<(const HuffmanNode &node1, const HuffmanNode &node2)
{
	return node1.weight < node2.weight;
}

struct HuffmanTree
{
	HuffmanNode *nodes;
	int leafnumber;
};

// 在哈夫曼树[0~n-1]范围内查找根结点权值最小的k1和根结点权值次小的k2
int select(HuffmanTree &T, int n, int &k1, int &k2)
{
    int i1 = -1, i2 = -2;
    for (int i = 0; i < n; i++)
    {
        // 略过非根结点
        if (T.nodes[i].parent != -1)
            continue;
        if (i1 == -1 || T.nodes[i].weight < T.nodes[i1].weight)
        {
            // 发现一个比目前已知权值最小的i1更小的根结点i
            // 原来的最小变成了次小
            i2 = i1;
            i1 = i;
        }
        else if (i2 == -1 || T.nodes[i].weight < T.nodes[i2].weight)
        {
            // 发现一个比目前已知权值次小的i2更小的根结点i
            i2 = i;
        }
    }

    // 约定先出现的（低下标）在左子
    k1 = min(i1, i2);
    k2 = max(i1, i2);
    return 0;
}

// 采用顺序查找权值最小次小根结点的策略构造哈夫曼树
int CreateHuffmanTree2(HuffmanTree &T, int leafnumber, int *weights)
{
    // 分配哈夫曼树存储空间
    T.nodes = new HuffmanNode[leafnumber + leafnumber - 1];
    T.leafnumber = leafnumber;

    // 初始化叶结点
    for (int i = 0; i < leafnumber; i++)
    {
        T.nodes[i].index = i;
        T.nodes[i].weight = weights[i];
        T.nodes[i].parent = T.nodes[i].lchild = T.nodes[i].rchild = -1;
    }

    // 开始构造哈夫曼树
    for (int i = 0; i < leafnumber - 1; i++)
    {
        // 选择权值最小和次小的根结点k1, k2，且k1 < k2
        int k1, k2;
        select(T, leafnumber + i, k1, k2);

        // 将根结点k1, 根结点k2合并到新增根结点i + leafnumber下
        T.nodes[i + leafnumber].weight = T.nodes[k1].weight + T.nodes[k2].weight;
        T.nodes[i + leafnumber].parent = -1;
        T.nodes[i + leafnumber].lchild = k1;
        T.nodes[i + leafnumber].rchild = k2;
        T.nodes[k1].parent = i + leafnumber;
        T.nodes[k2].parent = i + leafnumber;
    }

    return 0;
}

int CreateHuffmanTree(HuffmanTree &T, int leafnumber, int *weights)
{
	// 分配哈夫曼树存储空间
	T.nodes = new HuffmanNode[leafnumber + leafnumber - 1];
	T.leafnumber = leafnumber;

	// 初始化叶结点
	for (int i = 0; i < leafnumber; i++)
	{
        T.nodes[i].index = i;
        T.nodes[i].weight = weights[i];
		T.nodes[i].parent = T.nodes[i].lchild = T.nodes[i].rchild = -1;
	}
	
	// 将叶结点按权值排序
	sort(T.nodes, T.nodes + leafnumber);
	
	// 开始构造哈夫曼树
	int s = 0, t = leafnumber; // 分别用来遍历叶结点和非叶结点
	for (int i = 0; i < leafnumber - 1; i++)
	{
		// 选择第一个权值最小的根结点
		int k1;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k1 = s++;
		else
			k1 = t++;
		
		// 选择第二个权值最小的根结点
		int k2;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k2 = s++;
		else
			k2 = t++;

		// 将根结点k1, 根结点k2合并到新增根结点i + leafnumber下
		T.nodes[i + leafnumber].weight = T.nodes[k1].weight + T.nodes[k2].weight;
		T.nodes[i + leafnumber].parent = -1;
		T.nodes[i + leafnumber].lchild = k1;
		T.nodes[i + leafnumber].rchild = k2;
		T.nodes[k1].parent = i + leafnumber;
		T.nodes[k2].parent = i + leafnumber;
	}

	return 0;
}

int DestroyHuffmanTree(HuffmanTree &T)
{
    delete[] T.nodes;
    T.nodes = nullptr;
    T.leafnumber = 0;
    return 0;
}

int main()
{
	HuffmanTree T;
	int weights[] = { 3, 7, 8, 6, 21 };
	CreateHuffmanTree(T, sizeof(weights)/sizeof(*weights), weights);

	for (int i = 0; i < T.leafnumber + T.leafnumber - 1; i++)
	{
		cout << i << ":" << T.nodes[i].weight << ", " << T.nodes[i].parent << ", " << T.nodes[i].lchild << ", " << T.nodes[i].rchild << endl;
	}

    DestroyHuffmanTree(T);
    system("pause");
	return 0;
}