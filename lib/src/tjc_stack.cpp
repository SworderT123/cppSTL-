#include "../include.h"

namespace tjc
{
    namespace Stack
    {
        // 初始化
        template <class T>
        MyStack<T>::MyStack() : size(0), head(nullptr) {}

        template <class T>
        int MyStack<T>::get_size() const // 返回大小
        {
            return this->size;
        }

        template <class T>
        void MyStack<T>::push(T val) // 使用链表实现压栈 -- 头插
        {
            // 为要插入的节点分配大小
            link *temp = new link(val);

            // 寻找此时的尾节点
            link *current;
            current = head;

            // 头节点指向插入的节点，插入节点的下一个节点指向插入前的第一个节点
            head = temp;
            temp->next = current;

            // 大小+1
            size++;
        }

        template <class T>
        T MyStack<T>::pop() // 访问顶部数据并删除
        {
            if (head == nullptr)
            {
                throw std::out_of_range("栈为空！");
            }

            link *current = head;
            T val = current->val;

            head = head->next;
            delete current;

            size--;
            return val;
        }

        template <class T>
        const T &MyStack<T>::top() const // 访问顶部数据
        {
            if (head == nullptr)
            {
                // return; 不能空返回，因为返回类型是T
                throw std::out_of_range("栈为空！"); // 抛出异常
            }

            return head->val; // 返回顶部数据
        }

        template <class T>
        bool MyStack<T>::isempty() // 判断栈是否为空
        {
            if (head == nullptr)
            {
                return true;
            }
            return false;
        }
    }
}
