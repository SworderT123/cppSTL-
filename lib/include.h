#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <iostream>
#include <optional>    // 提供可选参数：c++17后
#include <type_traits> // 用于 std::is_pointer
#include <queue>
#include <limits> // 提供 std::numeric_limits，用于获取各种类型的最大值和最小值,如：std::numeric_limits<int>::max()
#include <cstring>
#include <cassert>       // 用于assert断言
#include <unordered_map> // 用于unordered_map
#include <functional>    // 提供比较算法
#include <vector>

namespace tjc::Link
{
    // 单向链表
    template <class T>
    class MyLink
    {
    public:
        MyLink(); // 初始化成员列表

        // 析构函数，释放内存
        ~MyLink();

        // 获取链表大小
        const int get_size() const;

        // 定义头插
        void push_front(T x);

        // 定义头删
        void pop_front();

        // 定义尾插
        void push_back(T x);

        // 定义尾删
        void pop_back();

        // 输出链表中的每个值
        void printvalue() const;

        // 在任意位置后插入一个数
        void insert_value(T val, int pos);

        // 在任意位置删除一个数
        void delete_value(int pos);

        // 反转链表
        void turn_link();

    private:
        struct link
        {
            T val;
            link *next;
            link(T x) : val(x), next(nullptr) {}
        };

        int size;
        link *head;
    };

    // 双向链表
    template <class T>
    class LinkPlus
    {
    public:
        LinkPlus(); // 初始化

        ~LinkPlus(); // 析构函数，释放堆内存

#if 0 // 不知道为什么这个函数一直报错，找不到原因
        typename LinkPlus<T>::linkplus *create_newnode(T x); // 创建一个新节点

#endif
        void push_front(T val); // 头插

        void push_back(T val); // 尾插

        void pop_front(); // 头删

        void pop_back(); // 尾删

        void printvalue(); // 输出值

    private:
        struct linkplus
        {
            T val;
            linkplus *next;
            linkplus *prev;
            linkplus(T x) : val(x), next(nullptr), prev(nullptr) {}
        };

        linkplus *head;
        int size;
    };
}

namespace tjc::Vector
{
    template <class T>
    class MyVector
    {
    public:
        MyVector();

        ~MyVector();

        int get_size() const;

        int get_capacity() const;

        void printVector() const;

        void push_back(T val);

        void erase(int pos); // 删除特定位置的数

        void remove(T val); // 删除特定大小的数

        void resize(int num); // 自定义给出的大小

        const T &operator[](int index) const // 重载[]
        {
            return data[index];
        }

        T &operator[](int index) // 重载[]
        {
            return data[index];
        }

    private:
        T *data;
        int size;
        int capacity;
    };
}

namespace tjc::Stack
{
    template <class T>
    class MyStack
    {
    public:
        MyStack();

        int get_size() const; // 返回栈的大小

        void push(T val); // 压栈

        bool isempty(); // 判断栈是否为空

        T pop(); // 从顶部返回元素并移出栈

        const T &top() const; // 访问顶部数据不移出

    private:
        struct link
        {
            T val;
            link *next;
            link(T x) : val(x), next(nullptr) {}
        };

        int size;
        link *head; // head指向栈顶
    };
}

namespace tjc::Queue
{
    template <class T>
    class MyQueue
    {
    public:
        MyQueue();

        void push(const T &val); // 先进先出

        void push(const T *val); // 接收指针

        T pop(); // 读取并删除第一个元素

        int get_size();

        bool isempty();

        const T front() const; // 获取第一个元素

        const T back() const; // 获取最后一个元素

    private:
        struct link
        {
            T val;
            link *next;
            link(T x) : val(x), next(nullptr) {}
        };

        link *head;
        link *tail;
        int size;
    };
}

namespace tjc::Tree
{
    template <class T>
    class MyBST
    {
    public:
        MyBST();

        const typename MyBST<T>::link *getRoot() const;

        void insert(T val); // 第一个插入的数就是根节点

        const T find_min() const; // 可以用递归也可以循环，这里使用循环，在后面重载一个递归

        const T find_max() const;

        int get_depth(T val);

        // 令根节点的高度为0
        int get_height(const typename MyBST<T>::link *node); // 寻找树的高度,默认是二叉搜索树

        // 广度优先遍历树 -- 层次遍历
        void print_tree(const typename MyBST<T>::link *node) const;

        // 深度优先遍历树 -- 前序、中序、后序（按照根节点的顺序）
        // 前序
        void print_tree_preorder(const typename MyBST<T>::link *node) const;

        // 中序--从小到大排列
        void print_tree_Inorder(const typename MyBST<T>::link *node) const;

        // 后序
        void print_tree_postorder(const typename MyBST<T>::link *node) const;

        bool isBST() const; // 判断是否为二叉搜索树

        // 删除一个节点(不知道为什么用delete报错？)
        void remove(T val);

        const T get_successor(T val) const; // 获取后继节点

        // 得到平衡二叉树（AVL）
        // AVL:每个节点的左子树高度减去右子树高度的差值（平衡因子）的绝对值不超过1
        // friend void getAVL(typename MyBST<T>::link *root);

    private:
        const T find_min(const typename MyBST<T>::link *node) const; // 使用递归重载

        const T find_max(const typename MyBST<T>::link *node) const;

        // 在类内声明友元函数时需要模板参数U来表示这是一个模板函数

        // 类中通用的查找函数，返回值对应的节点
        template <class U>
        friend const typename MyBST<U>::link *findNode(const typename MyBST<U>::link *root, U val);

        // 类中通用的插入函数，非成员变量(友元函数)，故不能在类中定义，只能在类中声明
        template <class U>
        friend typename MyBST<U>::link *insertBST(typename MyBST<U>::link *root, U val);

        // 类中通用的删除函数
        template <class U>
        friend typename MyBST<U>::link *removeBST(typename MyBST<U>::link *root, U val);

        // 类中通用的搜索函数
        template <class U>
        friend bool search(const MyBST<U> &tree, const typename MyBST<U>::link *node, U val);

        // 重载搜索函数，以便匹配不同的参数数量
        template <class U>
        friend bool search(MyBST<U> &tree, const typename MyBST<U>::link *node, U val, bool find);

        template <class U> // 辅助实现isBST函数
        friend bool is_BST(const typename MyBST<U>::link *node, U min, U max);

        // 返回val值的后序节点
        template <class U>
        friend const typename MyBST<U>::link *getSuccessor(const typename MyBST<U>::link *node, U val);

    private:
        struct link
        {
            T val;
            link *left;
            link *right;
            link(T x) : val(x), left(nullptr), right(nullptr) {}
        };

        link *root;
        int height;
        int depth;
    };

    // 在类定义内部或可见范围内定义模板成员函数
    template <class T>
    const typename MyBST<T>::link *MyBST<T>::getRoot() const
    {
        return root;
    }

    template <class T>
    const T MyBST<T>::find_min(const typename MyBST<T>::link *node) const
    {
        if (node->left == nullptr)
        {
            return node->val;
        }
        else
        {
            return find_min(node->left);
        }
    }

    template <class T>
    const T MyBST<T>::find_max(const typename MyBST<T>::link *node) const
    {
        if (node->right == nullptr)
        {
            return node->val;
        }
        else
        {
            return find_max(node->right);
        }
    }

    template <class T>
    int MyBST<T>::get_height(const typename MyBST<T>::link *node)
    {
        if (node == nullptr)
        {
            return height;
        }
        // 返回规则
        // 如果没有子节点，则高度 + 1后返回高度，否则高度 + 1后继续;
        if (node->left == nullptr && node->right == nullptr)
        {
            height++;
            return height;
        }
        else
        {
            height++;
        }

        int llheight = height, lrheight = height;
        if (node->left != nullptr)
        {
            llheight = get_height(node->left); // 最左边的左节点高度

            link *temp = node->left;    // 提取最左节点的左节点
            if (temp->right != nullptr) // 如果最左节点的右节点不为空
            {
                lrheight = get_height(temp->right); // 最左节点的右节点的高度
            }
        }

        int lheight = std::max(llheight, lrheight); // 得到左节点中最大深度

        height = 0; // 寻找右节点时，需要先将height初始化

        int rrheight = height, rlheight = height;
        if (node->right != nullptr)
        {
            rrheight = get_height(node->right); // 最右边的右节点高度

            link *temp = node->right;  // 提取最右节点的右节点
            if (temp->left != nullptr) // 如果最右节点的左节点不为空
            {
                rlheight = get_height(temp->left); // 最右节点的左节点的高度
            }
        }

        int rheight = std::max(rrheight, rlheight); // 得到右节点中最大深度

        return std::max(lheight, rheight); // 返回最大深度
    }

    template <class T>
    void MyBST<T>::print_tree(const typename MyBST<T>::link *node) const
    {
        if (node == nullptr)
        {
            std::cout << "无数据！" << std::endl;
            exit(1);
        }
        else
        {
            // auto q = std::queue<const typename MyBST<T>::link *>();
            // 确认是传递的const类型
            tjc::Queue::MyQueue<const typename MyBST<T>::link *> q;
            q.push(node);
            while (!q.isempty())
            {
                const link *current = q.front();  // 每次先提取队列的首元素
                std::cout << current->val << " "; // 输出首元素值

                // 保存首元素的子节点
                if (current->left != nullptr)
                    q.push(current->left);
                if (current->right != nullptr)
                    q.push(current->right);

                q.pop(); // 删去首元素
            }
        }
    }

    template <class T>
    void MyBST<T>::print_tree_preorder(const typename MyBST<T>::link *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        std::cout << node->val << " ";   // 访问并打印当前节点的值
        print_tree_preorder(node->left); // 递归遍历左子树
        // 左节点遍历完后 ‘回溯到上一次调用’ ，进行输出右节点的指令
        // 直到最右节点 = nullptr
        print_tree_preorder(node->right); // 递归遍历右子树
    }

    template <class T>
    void MyBST<T>::print_tree_Inorder(const typename MyBST<T>::link *node) const
    {
        if (node == nullptr)
        {
            return;
        }
        print_tree_Inorder(node->left);  // 先访问到最后一个左节点
        std::cout << node->val << " ";   // 输出
        print_tree_Inorder(node->right); // 访问右节点
    }

    template <class T>
    void MyBST<T>::print_tree_postorder(const typename MyBST<T>::link *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        print_tree_postorder(node->left);
        // 每次回溯只会进行第二个递归
        print_tree_postorder(node->right);
        std::cout << node->val << " ";
    }

    template <class T>
    class MyAVL
    {
    public:
        MyAVL();

        typename MyAVL<T>::link *getRoot() const;

        void insert(T val);

        void print_tree_preorder(const typename MyAVL<T>::link *node) const;

    private:
        // 获取每个根节点的平衡因子
        template <typename U>
        friend const int getBalanceFactor(const typename MyAVL<U>::link *node);

        // 计算每个节点的高度
        template <typename U>
        friend const int getHeight(const typename MyAVL<U>::link *node);

        template <typename U>
        friend typename MyAVL<U>::link *insertAVL(typename MyAVL<U>::link *node, U val);

        // 右旋
        template <typename U>
        friend typename MyAVL<U>::link *rightRotate(typename MyAVL<U>::link *node);

        // 左旋
        template <typename U>
        friend typename MyAVL<U>::link *leftRotate(typename MyAVL<U>::link *node);

        // 左平衡
        template <typename U>
        friend typename MyAVL<U>::link *leftBalance(typename MyAVL<U>::link *node);

        // 右平衡
        template <typename U>
        friend typename MyAVL<U>::link *rightBalance(typename MyAVL<U>::link *node);

    private:
        struct link
        {
            T val;
            int height;
            int bf;
            link *left;
            link *right;
            link(T x) : val(x), height(0), bf(0), left(nullptr), right(nullptr) {}
        };

        link *root;
        int depth;
    };

    template <class T>
    typename MyAVL<T>::link *MyAVL<T>::getRoot() const
    {
        return this->root;
    }

    template <class T>
    void MyAVL<T>::print_tree_preorder(const typename MyAVL<T>::link *node) const
    {
        if (node == nullptr)
        {
            return;
        }

        std::cout << node->val << " ";   // 访问并打印当前节点的值
        print_tree_preorder(node->left); // 递归遍历左子树
        // 左节点遍历完后 ‘回溯到上一次调用’ ，进行输出右节点的指令
        // 直到最右节点 = nullptr
        print_tree_preorder(node->right); // 递归遍历右子树
    }

    // 哈夫曼树
    class HFTree
    {
    public:
        HFTree();

        HFTree(const std::unordered_map<char, int> &freq); // 传入无序排列map类型

        ~HFTree();

        void preorder() const
        {
            preOrder(root);
        }

        const int get_weight() const
        {
            return min_sum_weight;
        }

    private:
        struct hfNode
        {
            char ch;       // 如果是叶子节点，存储字符；否则为0或其他无效值
            int weight;    // 权值
            hfNode *left;  // 左孩
            hfNode *right; // 右孩
            hfNode(char c = 0, int x = 0) : ch(c), weight(x), left(nullptr), right(nullptr) {}

            // 构建优先队列最小堆
            bool operator>(const hfNode &other) const; // 用于优先队列的比较函数（权重降序排列）
        };
        const hfNode *root;
        int length;
        int min_sum_weight;

        void delete_HFTree(const hfNode *node);
        void preOrder(const hfNode *root) const;
    };
}

namespace tjc::String
{
    /*
        该空间用于实现字符串的相关操作
        主要是实现一些常见的匹配算法
        与模板没有什么关系
        主要是一些算法
    */
    class MyString
    {
    public:
        MyString();

        MyString(const char *str); // 为str赋值

        ~MyString(); // 释放开辟的空间

        void printString() const; // 打印字符串

        void reverseString(); // 反转字符串

        void forceMatch(const MyString &str) const; // 暴力匹配

        void kmpMatch(const MyString &str) const; // kmp算法匹配

    private:
        friend const int *findNext(const MyString &str); // kmp算法得先找到next表

    public:
        char *str;
        int len;
    };
}

namespace tjc::Graph
{
    // 图（有向图）
    template <class T>
    class MyGraph
    {
    public:
        MyGraph();

        MyGraph(int VerNum, T *v, int *e);

        ~MyGraph();

        void revisited(); // 重置visited以便多次遍历

        void print_DFS(int index) const; // 深度优先遍历，参数为从第index个顶点开始遍历

        void print_BFS(int index) const; // 广度优先遍历

    private:
        struct Graph
        {
            tjc::Vector::MyVector<T> vertex; // T类型的顶点
            int **edge;                      // 用二维数组记录顶点是否与边相连（1--相连，0--不相连）
            int verNum;                      // 顶点数量
            int edgeNum;                     // 边数量

            Graph(int VerNum) : verNum(VerNum), edgeNum(0)
            {
                // 为顶点赋予传入数量的容量
                vertex.resize(VerNum);
                // 为 edge 开辟空间
                edge = new int *[VerNum];
                for (int i = 0; i < VerNum; ++i)
                {
                    edge[i] = new int[VerNum]();
                }
            }
        };

        Graph *graph;
        int *visited; // 该参数为遍历时，若遍历到该索引的顶点了则令其为 1;
    };
}

// 显式实例化模板
template class tjc::Link::MyLink<int>;
template class tjc::Link::LinkPlus<int>;
template class tjc::Stack::MyStack<int>;
template class tjc::Stack::MyStack<char>;
template class tjc::Stack::MyStack<tjc::Tree::MyBST<int>::link *>;
template class tjc::Queue::MyQueue<int>;
template class tjc::Queue::MyQueue<char>;
template class tjc::Queue::MyQueue<tjc::Tree::MyBST<int>::link *>;
template class tjc::Tree::MyBST<int>;
template class tjc::Tree::MyBST<char>;
template class tjc::Tree::MyAVL<int>;
template class tjc::Tree::MyAVL<char>;
template class tjc::Vector::MyVector<int>;
template class tjc::Vector::MyVector<char>;
template class tjc::Graph::MyGraph<char>;

#endif