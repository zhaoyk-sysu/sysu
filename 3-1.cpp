/*3-1 插队
题目描述
设线性表v中的n个整数递增有序，设计一个算法，将整数x插入到线性表v中，使得插入后的线性表依然保持递增有序的。

输入描述
第1行，2个整数n,x (1≤n≤10 4)，表示线性表v中的元素个数和待插入的整数。
第2行，n个整数，表示线性表v中的元素，输入保证递增有序。
输入保证所有整数的绝对值不超过10 9。

输出描述
1行，n+1个整数，表示插入后的线性表v。*/
#include<iostream>  
using namespace std;  
  
struct Node {  
    int val;  
    Node* next;  
};  
void creatlinklist(Node*&head,int n){
    head=new Node;
    head->next=NULL;
    Node*current=head;
    for(int i=0;i<n;i++){
        Node*p=new Node;
        cin>>p->val;
        p->next=NULL;
        current->next=p;
        current =p;
    }

}
void insert(Node* &head, int e) {  
    Node* current = head; 
    Node* prev = NULL; 
    while (current->next != NULL && current->next->val < e) {  
        prev = current;  
        current = current->next;  
    }  

    Node* newNode = new Node;  
    newNode->val = e;  
    newNode->next = current->next;  
    current->next = newNode;  

}  
void printlinklist(Node* head) {  
    Node* current = head->next; 
    while (current != NULL) {  
        cout << current->val << " ";  
        current = current->next;  
    }  
    cout << endl;  
}  
int main(){
    int n,e;
    cin>>n>>e;
    Node*head=NULL;
    creatlinklist(head,n);
    insert(head,e);
    printlinklist(head);
    return 0;
}