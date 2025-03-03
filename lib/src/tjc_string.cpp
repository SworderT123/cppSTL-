#include "../include.h"

namespace tjc::String
{
    MyString::MyString() : str(nullptr), len(0) {}

    MyString::MyString(const char *str)
    {
        if (str)
        {
            const char *temp = str;
            int len = 0;
            for (len = 0; *temp != 0; len++, temp++)
            {
            }

            if (len == 0)
            {
                std::cout << "please enter string!" << std::endl;
                this->str = nullptr;
            }
            else
            {
                temp = str; // 将temp重新指向str的头
                this->len = len;
                this->str = new char[this->len + 1]; // + 1 存放结尾的\0

                for (int i = 0; i < this->len; i++, temp++)
                {

                    this->str[i] = *temp;
                }
            }
        }
        else
        {
            throw std::invalid_argument("Input string is null");
        }
    }

    MyString::~MyString()
    {
        delete[] this->str;
    }

    void MyString::printString() const
    {
        for (int i = 0; i < len; i++)
        {
            std::cout << this->str[i];
        }
        std::cout << '\n';
    }

    void MyString::forceMatch(const MyString &str) const
    {
        int i = 0, j = 0;
        while (i < this->len && j < str.len)
        {
            if (this->str[i] == str.str[j])
            {
                i++;
                j++;
            }
            else
            {
                i = i - j + 1; // 不相等 i 往后移动一位继续寻找
                j = 0;         // j 则从头开始匹配
            }
        }

        if (j == str.len)
        {
            std::cout << "Match success!" << std::endl;
        }
        else
        {
            std::cout << "Match failed!" << std::endl;
        }
    }

    void MyString::kmpMatch(const MyString &str) const
    {
        const int *next = findNext(str);

        int i = 0, j = 0;
        while (i < this->len && j < str.len)
        {
            if (this->str[i] == str.str[j])
            {
                i++;
                j++;
            }
            else
            {
                // 不相等时不对i进行操作，即不进行回溯，i继续走
                i++;
                j = next[j];
            }
        }

        if (j == str.len)
        {
            std::cout << "Match success!" << std::endl;
        }
        else
        {
            std::cout << "Match failed!" << std::endl;
        }

        delete[] next;
    }

    const int *findNext(const MyString &str)
    {
        /*
            该算法需要创建一个next数组，表里存放首位与末尾的前后缀的长度
            比如：
            子串：    AABCAABA  AAACAAAB
            next表：  01001231  01201230

            具体实现见以下，注释会详细标出以防止遗忘
        */

        auto next = new int[str.len]; // 先创建一个子串长度的数组
        next[0] = 0;                  // 首元素设置为0
        int prefix_len = 0;           // 定义前后缀长度，初始化为0

        for (int i = 1; i < str.len; i++)
        {
            // 遍历子串，并且与子串的前后缀长度对应的字符相比较
            // 如果相等
            if (str.str[prefix_len] == str.str[i])
            {
                prefix_len++;         // 公共前后缀长度 + 1
                next[i] = prefix_len; // 将该长度放入next数组中
            }
            else
            {
                // 如果不相等
                if (prefix_len > 0)
                {
                    //     prefix_len = next[prefix_len - 1]; // 回溯到上一个匹配的位置
                    // }
                    // else
                    // {
                    //     next[i] = 0;
                    // }
                    if (str.str[i] == str.str[next[prefix_len - 1]])
                    {
                        prefix_len = next[prefix_len - 1] + 1;
                        next[i] = prefix_len;
                    }
                    else
                    {
                        prefix_len = 0;
                        next[i] = prefix_len;
                    }
                }
            }
        }
        return next;
    }
}