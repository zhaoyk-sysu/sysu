/*7-4 字符串匹配
题目描述
在目标串s中，查找模式串t的出现的次数以及位置。

输入描述
两行，分别为模式串t和目标串s，1≤∣t∣≤∣s∣≤5×10 6。
数据保证字符串只包含小写字母。

输出描述
第1行，一个整数n，表示模式串t在目标串s中出现的次数。
第2行，n个升序排列的整数，表示所有出现位置的起始索引（从0开始计数），每个索引之间用空格隔开。*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 构建部分匹配表（next数组）
vector<int> buildPrefixTable(const string& pattern) {
    int m = pattern.size();
    vector<int> prefixTable(m, 0);
    int j = 0;

    // 构建前缀表
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = prefixTable[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        prefixTable[i] = j;
    }
    return prefixTable;
}

// KMP 搜索算法
vector<int> KMP_Search(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> prefixTable = buildPrefixTable(pattern);
    vector<int> occurrences; // 记录模式串在目标串中的出现位置
    int j = 0;

    // 遍历目标串
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = prefixTable[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        // 当模式串完全匹配
        if (j == m) {
            occurrences.push_back(i - m + 1); // 记录匹配的起始位置
            j = prefixTable[j - 1]; // 准备下一次匹配
        }
    }

    return occurrences;
}

int main() {
    string pattern, text;

    // 输入模式串和目标串
    cin >> pattern >> text;

    // 使用KMP算法查找模式串的所有出现位置
    vector<int> result = KMP_Search(text, pattern);

    // 输出模式串在目标串中出现的次数
    cout << result.size() << endl;

    // 输出所有出现位置的起始索引
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
