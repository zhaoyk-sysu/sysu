/*3-2 字典顺序
题目描述
给定两个线性表a和b，设他们的长度分别为n 
a
​
 和n 
b
​
 。
判断a与b的字典顺序关系。

输入描述
第1行，2个整数n 
a
​
 ,n 
b
​
  (1≤n 
a
​
 ,n 
b
​
 ≤10 
4
 )，表示线性表a和b的元素个数。
第2行，n a个整数，表示线性表a中的元素。
第3行，n b个整数，表示线性表b中的元素。
输入保证所有整数的绝对值不超过10 9。

输出描述
1行，一个字符串，表示a与b的字典顺序关系。
如果a先于b，输出a < b；否则，如果b先于a，输出a > b；否则输出a == b。
注意，输出字符串中符号的前后有空格。*/
#include<iostream>
#include<stdlib.h>

using namespace std;  
  
struct Node {  
    int val;  
    Node* next;
};  
  

void creatlinklist(Node*& head, int n) {  
    head = new Node; 
    Node* current = head; 
  
    for (int i = 0; i < n; i++) {  
        Node* p = new Node; 
		p->next=NULL; 
        cin>>p->val; 
      
        current->next = p; 
        current = p; 
    }  

}  

void printlinklist(Node* head) {  
Node* current = head->next;

    while (current) { 
        cout << current->val << " ";  
        current = current->next;  
    }  
    cout << endl;
}
int comp(Node*head1,Node*head2){
	Node*h1=head1->next;
	Node*h2=head2->next;
	while(h1&&h2){
		if(h1->val>h2->val)return 2;
		else if(h1->val<h2->val)return 1;
		else return 0; 
	}
}
int main(){
	int n1,n2;
	cin>>n1>>n2;
	Node*head1=NULL;
	Node*head2=NULL;
	creatlinklist(head1,n1);
	creatlinklist(head2,n2); 
	int n=comp(head1,head2);
	if(n==2){
		cout<<"a < b"<<endl; 
	}else if(n==1) cout<<"a > b";
	else if(n1==n2)cout<<"a == b";
	else if(n1>n2)cout<<"a < b";
	else cout<<"a > b";
	return 0;
}
