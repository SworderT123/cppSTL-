#include "./lib/include.h"
void test()
{
    tjc::Link::MyLink<int> link;
    link.push_back(3);
    link.push_back(1);
    link.push_back(6);
    link.push_back(1);
    link.insert_value(5, 4);
    // link.delete_value(1);
    std::cout << "size:" << link.get_size() << std::endl;
    link.printvalue();

    link.turn_link();
    std::cout << "turn the link:";
    link.printvalue();

    std::cout << "----The following is a test of a double-link----" << std::endl;

    // 双向链表
    tjc::Link::LinkPlus<int> linkplus;
    linkplus.push_front(3);
    linkplus.push_front(5);

    linkplus.push_back(4);
    linkplus.push_back(2);

    linkplus.pop_back();
    linkplus.pop_front();

    linkplus.printvalue();

    std::cout << "----The following is a test of a stack----" << std::endl;

    tjc::Stack::MyStack<int> stack;
    stack.push(5);
    stack.push(1);
    stack.push(0);
    stack.push(2);

    std::cout << stack.top() << std::endl;
    std::cout << stack.get_size() << std::endl;

    std::cout << stack.pop() << std::endl;

    std::cout << stack.top() << std::endl;
    std::cout << stack.get_size() << std::endl;
    // std::cout << stack.isempty() << std::endl;

    std::cout << stack.pop() << std::endl;
    std::cout << stack.get_size() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.get_size() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.get_size() << std::endl;

    std::cout << "----The following is a test of a queue----" << std::endl;

    tjc::Queue::MyQueue<int> queue;
    queue.push(3);
    queue.push(1);
    queue.push(5);
    queue.push(7);
    queue.push(8);

    std::cout << queue.front() << std::endl;    // 3
    std::cout << queue.get_size() << std::endl; // 5
    std::cout << queue.isempty() << std::endl;  // 1
    std::cout << queue.back() << std::endl;     // 8

    printf("\n");

    std::cout << queue.pop() << std::endl;      // 3
    std::cout << queue.pop() << std::endl;      // 1
    std::cout << queue.pop() << std::endl;      // 5
    std::cout << queue.pop() << std::endl;      // 7
    std::cout << queue.pop() << std::endl;      // 8
    std::cout << queue.get_size() << std::endl; // 0
    std::cout << queue.isempty() << std::endl;  // 0

    std::cout << "----The following is a test of a BST----" << std::endl;

    tjc::Tree::MyBST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(6);
    tree.insert(15);
    tree.insert(25);
    tree.insert(13);
    tree.insert(18);
    tree.insert(12);
    tree.insert(14);

    /*
            10
           /  \
           5  20                // 失衡，20的左子树高度为3，右子树高度为1，相差大于1
          / \ / \
          3 6 15 25
              / \
             13 18
            / \
           12 14


            10
           /  \
           5  20
          / \ / \
          3 6 15 25             // 失衡，15的左子树高度为2，右子树高度为0，相差大于1
              /
             13
            / \
           12 14
    */

    std::cout << search(tree, tree.getRoot(), 2) << std::endl; // 0
    std::cout << search(tree, tree.getRoot(), 0) << std::endl; // 0
    std::cout << tree.find_max() << std::endl;                 // 25
    std::cout << tree.find_min() << std::endl;                 // 3
    std::cout << tree.get_height(tree.getRoot()) << std::endl; // 4
    std::cout << tree.get_depth(14) << std::endl;              // 4
    if (tree.getRoot() == nullptr)
        std::cout << "null root" << std::endl;
    else
        std::cout << " exist root" << std::endl;

    std::cout << "Breadth-first traversal:";
    tree.print_tree(tree.getRoot()); // 遍历树
    std::cout << '\n';
    std::cout << "preorder traversal:";
    tree.print_tree_preorder(tree.getRoot()); // 前序
    std::cout << '\n';
    std::cout << "inorder traversal:";
    tree.print_tree_Inorder(tree.getRoot()); // 中序
    std::cout << '\n';
    std::cout << "postorder traversal:";
    tree.print_tree_postorder(tree.getRoot()); // 后序
    std::cout << '\n';

    std::cout << tree.isBST() << std::endl;                                     // 1
    tree.remove(15);                                                            // 删除15
    std::cout << "after deleting 15,is tree BST:" << tree.isBST() << std::endl; // 1
    std::cout << "after deleting 15,tree is:";
    tree.print_tree_Inorder(tree.getRoot());
    std::cout << '\n';
    std::cout << "after deleting 15,14's depth is:" << tree.get_depth(14) << std::endl; // 2

    try
    {
        std::cout << tree.get_successor(12) << std::endl; // 13
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // std::cout << tree.get_successor(25) << std::endl; // 抛出异常

    std::cout << "----The following is a test of a String----" << std::endl;

    tjc::String::MyString str1("hello world!");
    str1.printString();

    tjc::String::MyString str2("world!");
    str2.printString();

    tjc::String::MyString str3("helo!");
    str3.printString();

    str1.forceMatch(str2);   // success
    str1.forceMatch(str3);   // failed
    str1.forceMatch("helo"); // failed

    /*
        AABCAABA  ABACABAB
        01001231  00101232
    */
    std::cout << "kmpMatch:" << std::endl;
    str1.kmpMatch(str2); // success
    //  str1.kmpMatch(str3);   // failed
    //  str1.kmpMatch("helo"); // failed

    std::cout << "----The following is a test of a AVL----" << std::endl;
    tjc::Tree::MyBST<int> btree;
    btree.insert(14);
    btree.insert(6);
    btree.insert(17);
    btree.insert(5);
    btree.insert(9);
    btree.insert(3);
    std::cout << "BST:";
    btree.print_tree_preorder(btree.getRoot());
    std::cout << '\n';

    tjc::Tree::MyAVL<int> atree;
    atree.insert(14);
    atree.insert(6);
    atree.insert(17);
    atree.insert(5);
    atree.insert(9);
    atree.insert(3);
    std::cout << "AVL:";
    atree.print_tree_preorder(atree.getRoot());

    std::cout << "----The following is a test of vctor----" << std::endl;

    tjc::Vector::MyVector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
    v.push_back(5);
    std::cout << "current vector's size: " << v.get_size() << std::endl; // 4
    v.printVector();

    v.erase(2);
    std::cout << "current vector's size: " << v.get_size() << std::endl; // 3
    v.printVector();

    v.remove(3);
    std::cout << "current vector's size: " << v.get_size() << std::endl; // 2
    v.printVector();

    v.resize(10);
    std::cout << "current vector's size: " << v.get_size() << std::endl; // 3

    std::cout << "----The following is a test of HuffManTree----" << std::endl;
    std::unordered_map<char, int> freq = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16}};

    tjc::Tree::HFTree hftree(freq);

    std::cout << "the sum of min weight is: " << hftree.get_weight() << std::endl; // 55
    hftree.preorder();
    std::cout << '\n';

    std::cout << "----The following is a test of Graph----" << std::endl;

    int edge[5][5] =
        {
            0, 1, 1, 1, 0,
            1, 0, 1, 1, 1,
            1, 1, 0, 0, 0,
            1, 1, 0, 0, 1,
            0, 1, 0, 1, 0};

    char vertex[] = "ABCDE";
    tjc::Graph::MyGraph<char> G(5, vertex, (int *)edge); // 将edge强制转换为int*类型

    G.print_DFS(0); // 从A开始遍历 -- ABCDE
    std::cout << '\n';
    G.revisited();
    G.print_DFS(3); // 从D开始遍历 -- DABCE
    std::cout << '\n';

    G.revisited();
    G.print_BFS(0); // 从A开始遍历 -- ABCDE
    std::cout << '\n';
    G.revisited();
    G.print_BFS(2); // 从C开始遍历 -- CABDE
    std::cout << '\n';
}

int main()
{
    test();
    return 0;
}