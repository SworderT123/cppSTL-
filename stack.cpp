#include "lib/include.h"
#include <cstring>
#include <vector>
#include <cassert>

/*实例输入：

    {}[]() 正确
    {[(13,[sf].g)]} 正确
    {}[(])]   错误--[(]
    {}[()]}   错误--无匹配的}

*/

void test()
{
#if 0

    tjc::Stack::MyStack<char> left; // 存左括号
    // int存位置，char存括号
    std::vector<std::pair<int, char>> lpos; // 存左括号

    int rsize = 0; // 记右括号的个数

    char instr[100];
    std::cin >> instr;
    size_t len = strlen(instr);

    // 遍历输入字符串，将所有括号压入各自的栈中
    for (int i = 0; i < len; i++)
    {
        if (instr[i] == '(' || instr[i] == '[' || instr[i] == '{')
        {
            left.push(instr[i]);
            lpos.push_back(std::make_pair(i, instr[i])); // 保存左括号的位置
        }

        if (instr[i] == ')' || instr[i] == ']' || instr[i] == '}')
        {
            rsize++; // 记录右括号的个数
        }
    }

    // 左右括号数量不相等
    if (left.get_size() != rsize)
    {
        std::cout << "符号匹配失败！--括号数量不同" << std::endl;
        return;
    }

    // 遍历输入字符串，尝试匹配括号
    for (int i = 0; i < left.get_size(); i++)
    {
        char ltop = left.top(); // 先提取出左括号的栈顶

        // 提取出左括号栈顶元素对应字符的位置
        int topPos = lpos[left.get_size() - i - 1].first;
        // 对右括号从最后一个左括号开始进行遍历

        for (int j = topPos + 1; j < len; j++)
        {
            // 左括号 + 1/2 = 右括号 且 左括号的位置比右括号小
            // 说明左括号的栈顶找到了对应的一个右括号
            if (ltop + 1 == instr[j]) // 对应小括号
            {
                for (int k = topPos + 1; k < j; k++)
                {
                    if (instr[k] == ']' || instr[k] == '}')
                    {
                        std::cout << "符号匹配错误！--不能交叉" << std::endl;
                        return;
                    }
                }
                left.pop(); // 删除左括号栈的顶部
                break;
            }

            if (ltop + 2 == instr[j]) // 对应中 / 大括号
            {
                if (ltop == '[') // 对应中括号
                {
                    for (int k = topPos; k < j; k++)
                    {
                        if (instr[k] == ')' || instr[k] == '}')
                        {
                            std::cout << "符号匹配错误！--不能交叉" << std::endl;
                            return;
                        }
                    }
                    left.pop();
                    break;
                }

                if (ltop == '{') // 对应大括号
                {
                    for (int k = topPos; k < j; k++)
                    {
                        if (instr[k] == ')' || instr[k] == ']')
                        {
                            std::cout << "符号匹配错误！--不能交叉" << std::endl;
                            return;
                        }
                    }
                    left.pop();
                    break;
                }
            }
        }

        // 如果左括号或者右括号不为空，说明有未匹配的括号
        if (left.isempty())
        {
            std::cout << "符号匹配成功！" << std::endl;
        }
        else
        {
            std::cout << "符号匹配失败！--存在未匹配" << std::endl;
            return;
        }
    }

#endif

    /*
    以上思路完全错误！！为什么要首先对所有左括号进行压栈？！！
    明明是要进行即时匹配，整个在一循环里，遇到左括号则下一个右括号一定是匹配的不就可以了？
    否则就是匹配失败！！
    全部压栈很明显非常愚蠢以及复杂！！！！！！！！！！！

    以下两种方案是根据lzl学长的思路进行的修改
    */

    // 简单修改
#if 0
    tjc::Stack::MyStack<char> s;

    std::cout << "Enter:";
    std::string m_str;
    std::cin >> m_str;

    for (int i = 0; i < m_str.size(); i++)
    {
        auto c = m_str[i]; // 存入每个字符给c
        // 压入相匹配的符号
        if (c == '(')
            s.push(')');
        else if (c == '[')
            s.push(']');
        else if (c == '{')
            s.push('}');

        else if (c == ']' || c == ')' || c == '}') // 如果遇到右括号
        {
            if (c != s.top())
            {
                if (s.isempty())
                {
                    std::cout << "nothing bracket";
                    return;
                }
                std::cout << "expect:" << s.top() << "but:" << c << "in:" << i + 1;
                return;
            }

            s.pop();
        }
    }

    if (s.isempty())
    {
        std::cout << "success";
    }
#endif
}

// 扩展修改--封装成一个类
class BracketMatch
{
public: // 定义各种情况
    enum Situation
    {
        Success = 0,
        Failed,
        Overflow,
        Lack,
        StateNum,
    };

    BracketMatch(const std::string &str) : m_str(str) {}

    // 返回各种情况（）
    Situation match()
    {
        tjc::Stack::MyStack<char> s;
        int index = -1;

        for (int i = 0; i < m_str.size(); i++)
        {
            auto c = m_str[i];

            static char bracket[4] = {0, ')', ']', '}'};

            switch (c)
            {
            case '(':
            case '[':
            case '{':
                if (s.isempty())
                {
                    index = i;
                }
                s.push(bracket[(c & 0x60) >> 5]);
                break;
            case ')':
            case ']':
            case '}':
                if (s.isempty())
                {
                    index = i;
                    Debug(index);
                    return Lack;
                }
                if (s.top() != c)
                {
                    index = i;
                    Debug(index);
                    std::cout << "expect: " << s.top() << " but: " << c << " in " << i + 1 << std::endl;
                    return Failed;
                }
                s.pop();
                if (s.isempty())
                {
                    index = -1; // 重新初始化栈底索引
                }
                break;
            default:
                break;
            }
        }

        if (s.isempty())
        {
            return Success;
        }
        else
        {
            assert(index != -1);
            Debug(index);

            return Overflow;
        }
    }

    void Debug(int i)
    {
        printf("\n");
        std::cout << m_str << std::endl;

        std::cout << std::string(i, '~') << '^' << std::string(m_str.size() - i - 1, '~') << std::endl;
    }

    // 将枚举类型中的字符串对应的数字转为对应的字符串
    static std::string CodetoStr(Situation code)
    {
        assert(code < StateNum); // 断言传入的code一定小于状态数，否则报错
        return code_to_str[code];
    }

private:
    std::string m_str;
    static std::string code_to_str[StateNum]; // 对应数字
};
std::string BracketMatch::code_to_str[] = {
    "Success",
    "Failed",
    "Overflow",
    "Lack"};

int main()
{
    // test();
    std::string input;
    bool loop = true;
    while (loop)
    {

        std::cout << "enter:";
        std::cin >> input;

        if (input == "exit")
        {
            break;
        }

        BracketMatch p(input);
        std::cout << BracketMatch::CodetoStr(p.match()) << std::endl; // 输出用户输入的字符串

        system("pause"); // 按任意键进行
        system("cls");
    }
    return 0;
}