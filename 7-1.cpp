/*7-1 独立字符统计
题目描述
现在有一篇文章，需要统计其中的每个字母的出现的次数。
注意：相同字符连续出现只计一次。

输入描述
一行，为一篇长度不超过2×10 5文章。文章只包含小写字母。

输出描述
一行，用空格分隔的26个整数，分别表示a到z的出现次数。
相同字符连续出现只计一次。*/
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str[200001];
    cin >> str;
    int cnt[26] = {0};  
    int m = strlen(str);

    for (int i = 0; i < m; i++) {
        if (i == 0 || str[i] != str[i - 1]) {
            cnt[str[i] - 'a']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        cout << cnt[i] << ' ';
    }
    
    return 0;
}

