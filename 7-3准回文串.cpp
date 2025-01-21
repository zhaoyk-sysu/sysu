/*7-3 准回文串
题目描述
判断一个字符串是否为准回文串。
一个字符串被称为准回文串，当且仅当它是一个回文串，或者删除某个字符后是一个回文串。

注意：测试数据中存在多组数据。

输入描述
第1行，一个整数T (T≤100)，表示数据组数。
接下来是T组数据，每组数据：
1行，一个字符串s (1≤∣s∣≤10 5)，只包含小写字母。

数据保证所有字符串长度之和不超过10 6。

输出描述
对于每组数据，输出一行，如果这个字符串是准回文串，则输出YES，否则输出NO。
注意区分大小写。*/
#include<iostream>
#include<string>
using namespace std;
bool isPalindrome(const string &s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

bool isNearlyPalindrome(const string &s) {
    int left = 0;
    int right = s.size() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
       
            return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
        }
        left++;
        right--;
    }
    return true;
}

int main(){
	int n;
	cin>>n;
	cin.ignore();
	for(int i=0;i<n;i++){
		 string line;
		 getline(cin, line);
		 int m=line.size()-1;
		 if(isPalindrome(line,0,m)||isNearlyPalindrome(line)){
		 	cout<<"YES"<<endl;
		 }else cout<<"NO"<<endl;
	}
	return 0;
}
