#include "../include.h"

namespace tjc::Vector
{
    template <class T>
    MyVector<T>::MyVector() : data(nullptr), size(0), capacity(0) {}

    template <class T>
    MyVector<T>::~MyVector()
    {
        delete[] data;
    }

    template <class T>
    int MyVector<T>::get_size() const
    {
        return size;
    }

    template <class T>
    int MyVector<T>::get_capacity() const
    {
        return capacity;
    }

    template <class T>
    void MyVector<T>::push_back(T val)
    {
        if (size == capacity)
            resize(capacity ? capacity * 2 : 1); // 如果大小和容量相等，则扩大大小为原来的两倍

        data[size++] = val; // 直接在size后面赋值即可，避免重复赋值
#if 0 
        // 该写法导致内存泄漏而且效率很低，每次都要重新分配并且完全复制
        for (int i = 0; i < size; i++)
        {
            data[i] = val;
        }
#endif
    }

    template <class T>
    void MyVector<T>::erase(int pos) // 从位置删除
    {
        assert(pos >= 0 && pos < size);
        if (size == 0)
        {
            delete[] data;
            data = nullptr;
        }

        int newSize = size - 1;
        T *temp = new T[newSize];
        for (int i = 0, j = 0; i < size; i++)
        {
            if (i == pos)
                continue;
            temp[j++] = data[i];
        }
        delete[] data;

        data = temp;
        size = newSize;
    }

    template <class T>
    void MyVector<T>::remove(T val) // 以大小删除
    {
        int newSize = size - 1;
        T *temp = new T[newSize];

        for (int i = 0, j = 0; i < size; i++)
        {
            if (data[i] != val)
                temp[j++] = data[i];
        }
        delete[] data;

        data = temp;
        size = newSize;
    }

    template <class T>
    void MyVector<T>::printVector() const
    {
        /*

        以我目前的水平，我只能输出是int / char类型的值，
        如果是比较复杂的值，像是结构或者是自定义数据类型，
        我暂时还不知道如何处理

        */
        for (int i = 0; i < size; i++)
        {
            std::cout << data[i] << " " << std::endl;
        }
    }

    template <class T>
    void MyVector<T>::resize(int num)
    {
        T *newData = new (std::nothrow) T[num]; // 使用nothrow以避免异常
        if (!newData)
        {
            throw std::bad_alloc(); // 如果分配失败，抛出异常
        }

        // 复制现有元素到新数组
        for (size_t i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }

        // 释放旧数组内存
        delete[] data;

        // 更新指针和容量
        data = newData;
        capacity = num;
    }
}