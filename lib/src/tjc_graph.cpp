#include "../include.h"

namespace tjc::Graph
{
    template <class T>
    MyGraph<T>::MyGraph() {}

    template <class T>
    MyGraph<T>::MyGraph(int VerNum, T *v, int *e)
    {
        // 开辟空间
        graph = new Graph(VerNum);

        // 为顶点赋值
        for (int i = 0; i < VerNum; i++)
        {
            // graph->vertex[i] = v[i];
            graph->vertex.push_back(v[i]);
        }
        // 为边赋值
        for (int i = 0; i < VerNum; i++)
        {
            for (int j = 0; j < VerNum; j++)
            {
                graph->edge[i][j] = *(e + i * VerNum + j); // 每行每列的边的int值为传入的e，后为偏移量

                if (graph->edge[i][j] == 1)
                    graph->edgeNum++; // 如果该值为 1 ，则边的数量加一
            }
        }
        graph->edgeNum /= 2; // 因为是无向边，所以为原来的一半

        visited = new int[graph->verNum];
        for (int i = 0; i < graph->verNum; i++)
        {
            visited[i] = 0;
        }
    }

    template <class T>
    MyGraph<T>::~MyGraph()
    {
        for (int i = 0; i < graph->verNum; ++i)
        {
            delete[] graph->edge[i];
        }
        delete[] graph->edge;

        delete[] visited;

        delete graph;
    }

    template <class T>
    void MyGraph<T>::print_DFS(int index) const
    {
        assert(index <= graph->verNum); // 断言索引一定 小于 顶点数量

        visited[index] = 1;
        std::cout << graph->vertex[index] << " "; // 先输出该索引对应的顶点

        for (int i = 0; i < graph->verNum; i++)
        {
            if (!visited[i] && graph->edge[index][i] == 1) // 每次递归从传入的索引后面的数开始循环，未找到就进行回溯
                print_DFS(i);
        }
    }

    template <class T>
    void MyGraph<T>::print_BFS(int index) const
    {
        // 需要一个队列把索引对应的顶点及其相邻的顶点存进去，实现方法类似树
        tjc::Queue::MyQueue<T> q;
        q.push(graph->vertex[index]);
        visited[index] = 1;
        std::cout << graph->vertex[index] << " "; // 输出当前索引对应的顶点

        int flag = 0; // 寻找当前索引下该顶点所连接的最后一个顶点
        for (int i = index; i < graph->verNum && !q.isempty(); i = flag)
        {
            q.pop(); // 将先进的先出队
            for (int j = 0; j < graph->verNum; j++)
            {
                if (!visited[j] && graph->edge[i][j] == 1)
                {
                    flag = j;
                    std::cout << graph->vertex[j] << " ";
                    visited[j] = 1;
                    q.push(graph->vertex[j]);
                }
            }
        }
    }

    template <class T>
    void MyGraph<T>::revisited()
    {
        for (int i = 0; i < graph->verNum; i++)
        {
            visited[i] = 0;
        }
    }
}