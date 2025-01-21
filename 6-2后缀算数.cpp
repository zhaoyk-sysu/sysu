/* 6-2 后缀表达式求值
题目描述
后缀表达式（也称为逆波兰表达式）是一种算术表达式表示法，其中运算符位于操作数之后。给定一个只包含四则运算（+、-、*、/）的后缀表达式，编写一个程序来计算其值。

在此题目中，我们假设除法运算规则与C语言中的/运算符相同，即向0取整。

输入描述
一行，包含不超过2×10 5个操作数/运算符，表示后缀表达式。其中，操作数/运算符两两之间用空格分隔。
操作数是整数，运算符是+、-、*、/中的一个。
数据保证：

输入的后缀表达式是合法的；
运算过程中，除数不为0；
操作数/运算中间值/结果不会超出int范围。
输出描述
输出一个整数，表示后缀表达式的计算结果。*/
#include <iostream>       // 用于输入输出
#include <stack>         // 用于使用栈
#include <sstream>       // 用于字符串流处理
#include <string>        // 用于使用字符串
#include <stdexcept>     // 用于异常处理

// 函数：计算后缀表达式
int evaluatePostfix(const std::string& expression) {
    std::stack<int> stack;          // 创建一个整数栈
    std::istringstream tokens(expression); // 将输入字符串转为流
    std::string token;              // 用于存放每个分离出的 token

    // 遍历输入的每个 token
    while (tokens >> token) {
        // 如果是数字（包括负数），将其转换为整数并压入栈中
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            stack.push(std::stoi(token)); // 将字符串转换为整数并压入栈
        } else {
            // 弹出两个操作数
            int b = stack.top(); stack.pop(); // 弹出栈顶元素 b
            int a = stack.top(); stack.pop(); // 弹出下一个元素 a
            int result; // 用于存放运算结果

            // 根据运算符进行计算
            switch (token[0]) {
                case '+':
                    result = a + b; // 加法
                    break;
                case '-':
                    result = a - b; // 减法
                    break;
                case '*':
                    result = a * b; // 乘法
                    break;
                case '/':
                    result = a / b; // 除法（向0取整）
                    break;
                default:
                    throw std::runtime_error("Invalid operator"); // 抛出异常
            }
            stack.push(result); // 将计算结果压入栈中
        }
    }

    return stack.top(); // 返回栈顶元素（最终结果）
}

// 主函数
int main() {
    std::string input; // 用于存放用户输入的后缀表达式
    std::getline(std::cin, input); // 读取一行输入
    try {
        int result = evaluatePostfix(input); // 调用计算函数
        std::cout << result << std::endl; // 输出结果
    } catch (const std::exception& e) { // 捕获异常并输出错误信息
        std::cerr << e.what() << std::endl; // 输出异常信息
    }

    return 0; // 结束程序
}
