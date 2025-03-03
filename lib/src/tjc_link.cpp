#include "../include.h"

// 对Mylib库中link的实现
template <class T>
tjc::Link::MyLink<T>::MyLink() : head(nullptr), size(0) {} // 初始化成员列表

// 析构函数，释放内存
template <class T>
tjc::Link::MyLink<T>::~MyLink()
{
    link *current;
    link *temp;
    current = head;
    while (current != nullptr)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}

// 获取链表大小
template <class T>
const int tjc::Link::MyLink<T>::get_size() const
{
    return size;
}

// 定义头插
template <class T>
void tjc::Link::MyLink<T>::push_front(T x)
{
    link *temp = new link(x);

    temp->next = head;
    head = temp;

    // 大小+1
    size++;
}

// 定义头删
template <class T>
void tjc::Link::MyLink<T>::pop_front()
{
    if (head != nullptr)
    {
        link *temp = head;
        head = head->next;
        delete temp;

        // 大小-1
        size--;
    }
}

// 定义尾插
template <class T>
void tjc::Link::MyLink<T>::push_back(T x)
{
    // 为要插入的节点分配大小
    link *temp = new link(x);
    temp->next = nullptr;

    // 寻找此时的尾节点
    link *current;
    current = head;

    // 如果只有头节点
    if (head == nullptr)
    {
        head = temp;
    }

    // 否则
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }

        // 尾节点指向要插入的节点
        current->next = temp;
    }

    // 大小+1
    size++;
}

// 定义尾删
template <class T>
void tjc::Link::MyLink<T>::pop_back()
{
    link *current;
    current = head;
    link *prev;
    prev = nullptr;

    if (head != nullptr)
    {
        // 寻找尾节点
        while (current->next != nullptr)
        {
            // prev始终在current前一个节点
            prev = current;
            current = current->next;
        }

        // 删去尾节点
        delete current; // 删除指针指向的内存区域，因此current不需要给内存

        // 将尾节点的前一个节点指向空
        prev->next = nullptr;

        // 大小-1
        size--;
    }
}

// 输出链表中的每个值
template <class T>
void tjc::Link::MyLink<T>::printvalue() const
{
    link *current = head;
    while (current->next != nullptr)
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    std::cout << current->val << std::endl;
}

// 在任意位置后插入一个数
template <class T>
void tjc::Link::MyLink<T>::insert_value(T val, int pos)
{
    // 创造移动节点
    link *current;
    link *prev;

    // 创造插入节点
    link *temp = new link(val);
    temp->next = nullptr;

    int flag = 0;
    current = head;

    // 在尾指针前面插入
    if (pos <= size)
    {
        while (current != NULL && flag < pos)
        {
            prev = current; // prev指针始终在current前面一个节点
            current = current->next;
            flag++;
        }

        // 此时current指向pos + 1的节点，prev指向pos的节点
        prev->next = temp;
        temp->next = current;

        size++;
    }

    if (pos > size)
    {
        std::cout << "当前链表大小为：" << get_size() << ",请重新输入！" << std::endl;
    }
}

// 在任意位置删除一个数
template <class T>
void tjc::Link::MyLink<T>::delete_value(int pos)
{
    // 创造移动节点
    link *current;
    link *prev;

    int flag = 0;
    current = head;

    if (pos <= 0 || pos > size)
    {
        std::cerr << "该位置不允许删除，请重新输入！" << std::endl;
        return;
    }
    // 在尾指针前面删除
    else
    {
        // 对头节点需要特殊操作，防止删除空指针
        if (pos == 1)
        {
            link *temp = head; // temp与head指向同一个地址
            head = head->next; // 更新头节点指针
            delete temp;       // 删除该地址，不能直接删除head
        }
        else
        {
            while (current != NULL && flag < pos - 1)
            {
                prev = current;
                current = current->next;
                flag++;
            }
            // 删除
            link *temp = current->next;
            delete current;
            prev->next = temp;
        }
        size--;
    }
}

// 反转链表
template <class T>
void tjc::Link::MyLink<T>::turn_link()
{
    link *current;
    link *prev = nullptr;
    link *temp;
    current = head;

    while (current != nullptr)
    {
        temp = current->next; // 保存下一个节点
        current->next = prev; // 令第一个节点指向空，current指针指向前一个

        prev = current; // 更新prev
        current = temp; // 将current指针向后移动
    }
    head = prev;
}

// 双向链表的实现
// 初始化列表
template <class T>
tjc::Link::LinkPlus<T>::LinkPlus() : head(nullptr), size(0) {}

// 释放指针开辟的堆空间
template <class T>
tjc::Link::LinkPlus<T>::~LinkPlus()
{
    linkplus *current;
    linkplus *temp;
    current = head;
    while (current != nullptr)
    {
        temp = current->next;
        delete current;
        current = temp;
    }
}

// 输出值
template <class T>
void tjc::Link::LinkPlus<T>::printvalue()
{
    linkplus *current = head;
    if (head == nullptr)
    {
        return;
    }

    while (current != nullptr)
    {
        std::cout << current->val << " ";
        current = current->next;
    }
    printf("\n");
}

#if 0 // 报错找不到原因，干脆不用了
// 创造新节点
template <class T>
typename tjc::Link::LinkPlus<T>::linkplus *tjc::Link::LinkPlus<T>::create_newnode(T x)
{
    return new linkplus(x);
}
#endif

// 头插
template <class T>
void tjc::Link::LinkPlus<T>::push_front(T val)
{
    linkplus *newnode = new linkplus(val);
    if (head == nullptr)
    {
        head = newnode; // 头节点指向新创建的节点
    }
    else
    {
        newnode->next = head; // 新创建的节点的next指向头节点指向的第一个节点
        head->prev = newnode; // 第一个节点的前一个节点指向新创建的节点
        head = newnode;
    }
    size++;
}

// 头删
template <class T>
void tjc::Link::LinkPlus<T>::pop_front()
{
    if (head == nullptr)
    {
        return;
    }
    else
    {
        linkplus *current = head;
        head = current->next;
        current->prev = nullptr; // 注意第二个节点的前一个节点要指向空

        delete current;
    }
    size--;
}

// 尾插
template <class T>
void tjc::Link::LinkPlus<T>::push_back(T val)
{
    linkplus *newnode = new linkplus(val);
    linkplus *current = head;

    if (head == nullptr)
    {
        head = newnode;
    }
    else
    {
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newnode;
        newnode->prev = current;
    }
    size++;
}

// 尾删
template <class T>
void tjc::Link::LinkPlus<T>::pop_back()
{
    linkplus *current = head;
    linkplus *prev = nullptr;

    if (head == nullptr)
    {
        return;
    }
    else
    {
        while (current->next != nullptr)
        {
            prev = current;
            current = current->next;
        }

        delete current;
        prev->next = nullptr;
    }
    size--;
}
