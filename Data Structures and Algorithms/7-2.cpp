/*7-2 单词翻转
题目描述
现在有一篇文章，需要将其中的每个单词翻转，然后输出。
这里，一段连续的字母被称为一个单词。

输入描述
若干行，为一篇总长度不超过2×10 5文章。
文章只可能包含可显示字符（ASCII码值从32到126的字符），以及换行符。

注意：空白符或标点符号可能连续出现。

输出描述
每个单词翻转后的文章。*/
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void reverseWordsInSentence(const string &line) {
    int start = 0; 
    while (start < line.size()) {
        while (start < line.size() && !isalpha(line[start])) {
            cout << line[start]; 
            start++;
        }
        
        int end = start;
        while (end < line.size() && isalpha(end)) {
            end++;
        }
        
        // ��ת���ʲ����
        if (start < end) {
            string word = line.substr(start, end - start);
            reverse(word.begin(), word.end());
            cout << word;
            start = end;
        }
    }
    cout << endl;
}

int main() {
    string line;
    // ���ж�ȡ����
    while (getline(cin, line)) {
        reverseWordsInSentence(line);
    }
    return 0;
}

