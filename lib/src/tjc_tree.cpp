#include "../include.h"
/*
    由于该数据结构一些函数的实现需要进行递归，而递归又不得不传入参数，
    而参数又是类内封装的结构体，
    因此一些函数的实现不能在.cpp中，因为这样会导致类不完整实现(编译错误)，
    所以只能将这些 需要传入结构体作为参数 或者是 返回结构体 的函数的实现放在.h文件中
    这样做确实破坏了一定的封装性与规范性，
    但除此外只能将结构体定义在类外部，
    但这样做会很麻烦（懒），因为又得重新规范所有的参数类型和数据结构
    会耗费很长时间，
    因此，为了方便，只能选择破坏一点封装性以及牺牲整体的规范性

*/

// BST
namespace tjc::Tree
{
    template <class T>
    MyBST<T>::MyBST() : root(nullptr), height(0), depth(0) {}

    template <class T>
    void MyBST<T>::insert(T val)
    {
        root = insertBST(root, val);
    }

    template <class T>
    const T MyBST<T>::find_min() const
    {
        link *current = root;
        if (root == nullptr)
        {
            std::cout << "当前无根节点！" << std::endl;
            exit(1);
        }
        else
        {
            while (current->left != nullptr)
            {
                current = current->left;
            }

            return current->val;
        }
    }

    template <class T>
    const T MyBST<T>::find_max() const
    {
        link *current = root;
        if (root == nullptr)
        {
            std::cout << "当前无根节点！" << std::endl;
            exit(1);
        }
        else
        {
            while (current->right != nullptr)
            {
                current = current->right;
            }

            return current->val;
        }
    }

    template <class T>
    int MyBST<T>::get_depth(T val)
    {
        this->depth = 0; // 每次查找前都要将深度置为0
        if (search(*this, this->getRoot(), val, true))
            return this->depth;
        else
            std::cout << "未找到：" << val << std::endl;
        return 0;
    }

    template <class T>
    bool MyBST<T>::isBST() const
    {
        // 传递参数为T()--表示T类型的最小值以及std::numeric_limits<T>::max()--表示T类型的最大值
        return is_BST(root, T(), std::numeric_limits<T>::max());
    }

    template <class T>
    void MyBST<T>::remove(T val)
    {
        root = removeBST(root, val);
    }

    template <class T>
    const T MyBST<T>::get_successor(T val) const
    {
        if (val >= find_max() || val < find_min())
        {
            throw std::out_of_range("Value is not equal the maximum value in the tree");
        }

        const typename MyBST<T>::link *temp = getSuccessor(root, val);

        if (temp == nullptr)
        {
            // 运行时错误异常，用于在程序运行时遇到非特定类型的错误时抛出
            throw std::runtime_error("No successor found for the given value");
        }

        return temp->val;
    }

    template <class U>
    const typename MyBST<U>::link *findNode(const typename MyBST<U>::link *root, U val)
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root->val > val)
        {
            return findNode(root->left, val);
        }
        else if (root->val < val)
        {
            return findNode(root->right, val);
        }
        else
        {
            return root;
        }
    }

    template <class U> // C++不允许模板函数有默认参数，可以编写重载函数来提供不同的版本
    bool search(const MyBST<U> &tree, const typename MyBST<U>::link *node, U val)
    {
        if (node == nullptr)
        {
            return false;
        }
        else if (node->val == val)
        {
            return true;
        }
        else if (val > node->val)
        {
            return search(tree, node->right, val);
        }
        else
        {
            return search(tree, node->left, val);
        }
    }

    template <class U> // 重载
    bool search(MyBST<U> &tree, const typename MyBST<U>::link *node, U val, bool find)
    {
        if (node == nullptr)
        {
            return false;
        }
        else if (node->val == val)
        {
            return true;
        }
        else if (val > node->val)
        {
            if (find == true) // // 只有当find为true时，才增加depth
                tree.depth++;
            return search(tree, node->right, val, true);
        }
        else
        {
            if (find == true)
                tree.depth++;
            return search(tree, node->left, val, true);
        }
    }

    template <class U> // insertBST函数是友元函数，非成员函数，需要在类外定义
    typename MyBST<U>::link *insertBST(typename MyBST<U>::link *root, U val)
    {
        if (root == nullptr)
        {
            return new typename MyBST<U>::link(val);
        }
        else if (val < root->val)
        {
            root->left = insertBST(root->left, val);
        }
        else if (val > root->val)
        {
            root->right = insertBST(root->right, val);
        }
        return root;
    }

    template <class U> // 每一次删除会改变传入参数的值，所以应该返回相同的数据类型并指向根节点
    typename MyBST<U>::link *removeBST(typename MyBST<U>::link *node, U val)
    {
        if (node == nullptr)
        {
            return node; // 如果没有找到要删除的节点，直接返回
        }
        // 由于指针传递的是子节点的地址，所以根节点的地址不会发生改变
        if (val < node->val)
        {
            node->left = removeBST(node->left, val);
        }

        else if (val > node->val)
        {
            node->right = removeBST(node->right, val);
        }

        else if (val == node->val)
        {
            // 如果没有子节点，直接删除
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                node = nullptr;
            }
            // 如果只有一个右子节点，用右子节点替换当前节点
            else if (node->left == nullptr)
            {
                // 引用模板类型参数作为类型时，需要使用 typename 关键字来明确告诉编译器这是一个类型
                typename MyBST<U>::link *temp = node; // 保存要删除的节点
                node = node->right;                   // 将要删除的节点的右子树作为新的根节点
                delete temp;                          // 删除要删除的节点
            }
            // 如果只有一个左子节点，用左子节点替换当前节点
            else if (node->right == nullptr)
            {
                typename MyBST<U>::link *temp = node;
                node = node->left;
                delete temp;
            }
            // 如果有两个子节点，找到右子树中的最小节点，用该节点替换当前节点
            else
            {
                // 保存要删除的节点
                typename MyBST<U>::link *temp = node;
                /*
                    需要明确删除的节点用什么值替补
                    需要注意：将该根节点删除，仍然要满足二叉搜索树的性质
                    因此我们需要用 左孩的最右节点 或者 右孩的最左节点 来替补
                    因为这两个节点的值都接近于要删除的节点的值，并且不会破坏二叉搜索树的性质
                */
                // 我认为找左孩的最右节点的值更精确，两种方法的实现都差不多
                typename MyBST<U>::link *left_max = node->left;
                while (left_max->right != nullptr)
                {
                    left_max = left_max->right; // 找到左孩的最右节点
                }
                node->val = left_max->val; // 用左孩的最右节点的值替换当前节点的值

                // 接下来只需要把左孩的最右节点删除即可(该节点只会有一个左孩或者没有子节点，因为该节点是根节点的最右节点)，而非删除当前节点
                // 使用递归相当于把有两个子节点的情况转换为只有0个或者1个子节点的情况
                node->left = removeBST(node->left, left_max->val); // 删除左孩的最右节点
            }
        }
        else
        {
            std::cout << "not found:" << val << std::endl;
        }

        return node; // node仍然指向根节点，递归删除的只是node的子节点
    }

    template <class U> // 辅助实现isBST函数
    bool is_BST(const typename MyBST<U>::link *node, U min, U max)
    {
        if (node == nullptr)
        {
            return true;
        }

        if (node->val < min || node->val > max)
        {
            return false;
        }

        // 递归检查左子树和右子树,左子树的值的范围是[min, node->val-1]，右子树的值的范围是[node->val+1, max]
        return is_BST(node->left, min, node->val) && is_BST(node->right, node->val, max);
    }

    template <class U> // 辅助实现get_successor函数
    const typename MyBST<U>::link *getSuccessor(const typename MyBST<U>::link *node, U val)
    {
        /*
            因为返回类型为const，所以定义的变量也必须是const
            才能保证左值和右值都是const的
            注意：const int 不能隐式转换为 int ，因为这样会破坏const的常量性
            而 int 可以隐式转换为 const int
        */

        // 该函数中由于各种特性，不能直接调用本函数的递归，因为这样会改变node的指向，而无法找到树的根节点
        // 因此需要定义一个临时变量，初始化为node的指向(树的根节点)然后改变current的指向(后继节点的指向)
        // 也不能使用lambda表达式，因为不能自身递归
        // 只能构造一个函数找到节点了
        const typename MyBST<U>::link *current = findNode(node, val); // 此时current指向后继节点，node指向树的根节点
        if (current == nullptr)
        {
            return current;
        }

        // 如果该节点有右子树，则后继节点为其右子树中最小的节点
        if (current->right != nullptr)
        {
            const typename MyBST<U>::link *temp = current->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            return temp;
        }
        else
        {
            // 如果该节点没有右子树，则后继节点为其祖先节点中第一个比该节点值大的节点
            const typename MyBST<U>::link *ancestor = node;     // ancestor指向树的根节点
            const typename MyBST<U>::link *successor = nullptr; // 直到找到后继节点

            while (ancestor != current)
            {
                if (current->val < ancestor->val)
                {
                    successor = ancestor;      // 先让后继节点等于祖先节点
                    ancestor = ancestor->left; // 再让祖先节点等于左子节点
                }
                else
                {
                    // 如果传入节点的值大于等于祖先节点的值，则祖先节点等于右子节点
                    // 此时后继节点保持不变，因为祖先节点的值小于传入节点，此时后继节点的值更大
                    ancestor = ancestor->right;
                }
            }

            return successor;
        }
    }
}

// AVL
namespace tjc::Tree
{
    template <class T>
    MyAVL<T>::MyAVL() : root(nullptr), depth(0) {}

    template <class T>
    void MyAVL<T>::insert(T val)
    {
        this->root = insertAVL(this->root, val);
    }

    template <class U>
    typename MyAVL<U>::link *insertAVL(typename MyAVL<U>::link *node, U val)
    {
        /*
            递归函数（或者是普通函数）尽量不要对树进行直接操作
            尤其是递归函数
            即形参最好不要传入树(不要直接改变树的结构)
            或直接更改树的根节点
            不然会很麻烦……
            （尽可能只对node进行更改）
        */

        if (!node)
            return new typename MyAVL<U>::link(val);

        if (val < node->val)
            node->left = insertAVL(node->left, val); // 找到左节点

        else if (val > node->val)
            node->right = insertAVL(node->right, val);

        /*
            显式指定getHeight、getHeight、getBalanceFactor后的参数为<U>
        */

        // 获取当前节点的高度和平衡因子
        node->height = 1 + std::max(getHeight<U>(node->left), getHeight<U>(node->right));
        node->bf = getBalanceFactor<U>(node);
        // L情况
        if (node->bf == 2)
        {
            node = leftBalance<U>(node); // 则左平衡
        }

        // R情况
        else if (node->bf == -2)
            node = rightBalance<U>(node); // 则右平衡

        return node; // 一直回溯到满足条件的node
    }

    template <class U> // 实现左旋，参数是失衡节点
    typename MyAVL<U>::link *leftRotate(typename MyAVL<U>::link *node)
    {
        typename MyAVL<U>::link *temp = node->right; // 先保存失衡节点左孩的右节点
        node->right = temp->left;                    // 如果该节点有左孩，则让该左孩为传入节点的右孩

        temp->left = node;

        // 更改高度
        node->height = 1 + std::max(getHeight<U>(node->left), getHeight<U>(node->right));
        temp->height = 1 + std::max(getHeight<U>(temp->left), getHeight<U>(temp->right));
        return temp;
    }

    template <class U> // 实现右旋
    typename MyAVL<U>::link *rightRotate(typename MyAVL<U>::link *node)
    {
        typename MyAVL<U>::link *temp = node->left; // 先保存失衡节点的左孩
        node->left = temp->right;                   // 如果该节点有右孩，则让该右孩为传入节点的左孩

        temp->right = node;

        // 更改高度
        node->height = 1 + std::max(getHeight<U>(node->left), getHeight<U>(node->right));
        temp->height = 1 + std::max(getHeight<U>(temp->left), getHeight<U>(temp->right));

        return temp;
    }

    template <typename U> // 实现左平衡
    typename MyAVL<U>::link *leftBalance(typename MyAVL<U>::link *node)
    {
        int bf = node->left->bf;
        bf = getBalanceFactor<U>(node->left);
        // LL情况：直接右旋根节点即可
        if (bf == 1)
        {
            node = rightRotate<U>(node);
        }

        // LR情况：先左旋左孩，再右旋根节点
        else if (bf == -1)
        {
            node = leftRotate<U>(node->left);
            node = rightRotate<U>(node);
        }

        return node;
    }

    template <typename U> // 实现右平衡
    typename MyAVL<U>::link *rightBalance(typename MyAVL<U>::link *node)
    {
        int bf = node->right->bf;
        bf = getBalanceFactor<U>(node->right);
        // RR情况：直接左旋根节点即可
        if (bf == -1)
        {
            node = leftRotate<U>(node);
        }
        // RL情况：先右旋右孩，再左旋根节点
        else if (bf == 1)
        {
            node = rightRotate<U>(node->right);
            node = leftRotate<U>(node);
        }

        return node;
    }

    template <typename U>
    const int getHeight(const typename MyAVL<U>::link *node)
    {
        // 递归地计算左子树和右子树的高度，并返回较大值加 1
        // 真踏马牛逼！绝了啊！！！
        // 传入参数是根节点的子节点，所以后面不用 - 1
        return node ? 1 + std::max(getHeight<U>(node->left), getHeight<U>(node->right)) : 0;
    }

    template <typename U>
    const int getBalanceFactor(const typename MyAVL<U>::link *node)
    {
        return node ? getHeight<U>(node->left) - getHeight<U>(node->right) : 0;
    }
}

// HFTree
namespace tjc::Tree
{
    HFTree::HFTree() : root(nullptr), length(0), min_sum_weight(0) {}

    HFTree::~HFTree()
    {
        delete_HFTree(root);
    }

    // 传入字符和权值，由于是无序排列，因此时间为O(1)
    HFTree::HFTree(const std::unordered_map<char, int> &freq)
    {
#if 0 
        for (const auto &pair : freq) // pair与freq的数据类型相同，这里对freq的每个键值进行遍历
        {
            minHeap.push(hfNode(pair.first, pair.second)); // 调用hfNode的构造函数给最小堆赋值
        }

        min_sum_weight = 0;
        while (minHeap.size() > 1) // 当堆的大小大于 1 时，循环
        {
            const hfNode *left = &minHeap.top();  // 最小值存左节点
            minHeap.pop();                        // 删去最小值
            const hfNode *right = &minHeap.top(); // 第二小的值存右节点
            minHeap.pop();                        // 删去右节点

            int sum = left->weight + right->weight; // 计算最小权值之和
            min_sum_weight += sum;
            hfNode *parent = new hfNode(0, sum); // 建立新树
            parent->left = new hfNode(*left);
            parent->right = new hfNode(*right);

            minHeap.push(*parent); // 把父节点存到堆里
        }

        root = new hfNode(minHeap.top()); // 让根节点指向容器中的顶端元素
#endif

        // 使用最小堆（因为优先队列默认是最大堆，所以我们用大于比较符来实现最小堆）
        // 顶端元素即是所需求的最小权值 -- operator> 重载>实现了降序排列
        // priority_queue 默认使用 vector 作为其底层容器，可以通过第二个模板参数指定其他容器类型
        // std::priority_queue<hf Node, std::vector<hfNode>, std::greater<hfNode>> minHeap;
        std::priority_queue<hfNode *, std::vector<hfNode *>, std::greater<hfNode *>> minHeap;

        for (const auto &pair : freq)
        {
            minHeap.push(new hfNode(pair.first, pair.second)); // 为传入的节点创建空间
        }

        min_sum_weight = 0;
        while (minHeap.size() > 1)
        {
            hfNode *left = minHeap.top();
            minHeap.pop();
            hfNode *right = minHeap.top();
            minHeap.pop();

            min_sum_weight = left->weight + right->weight;  // 累加权重
            hfNode *parent = new hfNode(0, min_sum_weight); // 创建新的父节点
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        root = minHeap.top(); // 让根节点指向容器中的顶端元素
    }

    void HFTree::preOrder(const hfNode *root) const
    {
        if (root == nullptr)
            return;
        if (root->ch)
            std::cout << root->ch << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    bool HFTree::hfNode::operator>(const hfNode &other) const
    {
        return weight > other.weight; // 插入的元素从大到小排列，因此顶端元素为最小值（最小堆）
    }

    void HFTree::delete_HFTree(const hfNode *node)
    {
        if (node)
        {
            delete_HFTree(node->left);
            delete_HFTree(node->right);

            delete node;
        }
    }
}

// 在源文件的末尾显式实例化模板,告诉编译器生成特定类型的模板函数的代码
template bool tjc::Tree::search<int>(const MyBST<int> &, const MyBST<int>::link *, int);
template bool tjc::Tree::search<int>(MyBST<int> &, const MyBST<int>::link *, int, bool);
template bool tjc::Tree::search<char>(const MyBST<char> &, const MyBST<char>::link *, char);
template bool tjc::Tree::search<char>(MyBST<char> &, const MyBST<char>::link *, char, bool);
