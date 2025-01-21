//一些链表的基本操作
#include<iostream>
#include<stdlib.h>

using namespace std;  
  
struct Node {  
    int val;  
    Node* next;
};  
  
//头插法创建链表
void creatlinklist(Node*& head, int n) {  
    head = new Node; 
    Node* current = head; 
  
    for (int i = 0; i < n; i++) {  
        Node* p = new Node; 
		p->next=NULL; 
         p->val=i+10; 
      
        current->next = p; 
        current = p; 
    }  

}  

void creatlinklist2(Node*& head, int n) {  
    head = new Node; 
    Node* current = head; 
  
    for (int i = 0; i < n; i++) {  
        Node* p = new Node; 
		p->next=NULL; 
         p->val=i; 
      
        current->next = p; 
        current = p; 
    }  

}   
 //输出链表
void printlinklist(Node* head) {  
Node* current = head->next;

    while (current) { 
        cout << current->val << " ";  
        current = current->next;  
    }  
    cout << endl;
}  
//查找key值
Node* locate(Node* head, int key) {  
    Node* p = head->next; 
    while (p != NULL && p->val != key) p = p->next;  
    if (p != NULL && p->val == key) return p;  
    else {  
        cout << "查找失败"<< endl;  
        return NULL;  
    }  
} 
//插入 
Node*insert(Node*&head,int i,int e){
    Node*h=head->next;
   
    int j=1;
    while(h&&j<i){
        h=h->next;
        ++j;
    }if(!h||j>i)return NULL;
    else{
        Node*s=new Node;
        s->val=e;
        s->next=h->next;
        h->next=s;
        


    }
}
//删除
Node* dele(Node*&head,int i){
	Node*d=head->next;
	int j=1;
	while(d&&j<i) {
		d=d->next;
		++j;
	}if(!d||j>i) return NULL;
	else{
		Node*s=d;
		s->next=d->next->next;
	}	
	

}
//你指链表
Node*headback(Node*&head){
	Node*p=head->next;
	head->next=NULL;
	Node*q;
	while(p){
		q=p->next;
		p->next=head->next;
		head->next=p;
		p=q;
	}
} 
//合并两个链表
Node*mergelist(Node*head,Node*head1){
	Node* l3 = new Node;  
    l3->next =NULL;  
    Node* p1 = head->next;  
    Node* p2 = head1->next;  
    Node* p3 = l3;  
    while (p1 && p2) {  
        if (p1->val <= p2->val) {  
            p3->next = p1;  
            p1 = p1->next;  
        } else {  
            p3->next = p2;  
            p2 = p2->next;  
        }  
        p3 = p3->next;  
    }  
    p3->next = p1 ? p1 : p2;  
    return l3;  
}

    
int main() {    
    int n = 5;    
    Node* head = NULL;  
	Node*head1=NULL; 
	Node*l3;
    creatlinklist(head, n);    
    creatlinklist2(head1, n);   
    printlinklist(head); 
	 printlinklist(head1);  
    Node* found = locate(head, 3);  
    if (found) {  
        cout << found->val << endl;  
    }  
 insert(head,4,6);
  printlinklist(head);
 dele(head,4);
   printlinklist(head);
   headback(head);
  printlinklist(head);
   headback(head);
   printlinklist(head);
   l3=mergelist(head,head1);
   printlinklist(l3);
    system("pause");
    return 0;
  
   
}
