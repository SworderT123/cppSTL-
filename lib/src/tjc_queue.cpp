#include "../include.h"
namespace tjc
{
    namespace Queue
    {
        template <class T>
        MyQueue<T>::MyQueue() : size(0), head(nullptr), tail(nullptr) {}

        template <typename T> // 重载函数时其接收指针
        void MyQueue<T>::push(const T *val)
        {
            link *temp = new link(*val);
            if (this->head == nullptr)
            {
                this->head = temp;
                this->tail = this->head;
            }
            else
            {
                tail->next = temp;
                this->tail = temp;
            }
            this->size++;
        }

        template <class T> // 传递非指针
        void MyQueue<T>::push(const T &val)
        {
            link *temp = new link(val);

            if (head == nullptr)
            {
                head = temp;
                tail = head;
            }
            else
            {
                tail->next = temp; // 先让尾节点的next指向temp
                tail = temp;       // 再让尾节点指向temp，进行连接
            }
            size++;
        }

        template <class T>
        T MyQueue<T>::pop()
        {
            if (head == nullptr)
            {
                throw std::out_of_range("队列为空！");
            }

            link *current = head;
            T val = head->val;
            head = head->next;
            delete current;

            size--;
            return val;
        }

        template <class T>
        int MyQueue<T>::get_size()
        {
            return this->size;
        }

        template <class T>
        bool MyQueue<T>::isempty()
        {
            if (head == nullptr)
            {
                return true;
            }

            return false;
        }

        template <class T>
        const T MyQueue<T>::front() const
        {
            if (head == nullptr)
            {
                throw std::out_of_range("队列为空！");
            }
            return head->val;
        }

        template <class T>
        const T MyQueue<T>::back() const
        {
            if (head == nullptr)
            {
                throw std::out_of_range("队列为空！");
            }
            return tail->val;
        }
    }
}