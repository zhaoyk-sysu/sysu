/* 4-2 链表单向转双向
输入描述
第1行，1个整数n (1≤n≤10 4)，表示链表a的元素个数。
第2行，n个整数，表示链表a中的元素。
输入保证所有整数的绝对值不超过10 9。

输出描述
输出一个链表的遍历结果。*/
#include <iostream>
#include <vector>
struct DoublyNode {
  int val;
  DoublyNode* next;
  DoublyNode* prev;
};

using namespace std;

void backward_link(DoublyNode* a){
    DoublyNode* p;
    p=a;
   while(p->next){
    p->next->prev=p;
    p=p->next;
   }
 
}

int main() {
  int n;
  cin >> n;

  // Read the values and create the linked list
  vector<DoublyNode> nodes(n);
  for (int i = 0; i < n; ++i) {
    cin >> nodes[i].val;
    if (i == n - 1) {
      nodes[i].next = nullptr;
    } else {
      nodes[i].next = &nodes[i + 1];
    }
  }

  // Convert the singly linked list to a doubly linked list
  backward_link(nodes.data());

  // Check and print the doubly linked list
  for (int i = 0; i < n; ++i) {
    cout << nodes[i].val;
    if (i == n - 1) {
      cout << endl;
    } else {
      bool forward = nodes[i].next == &nodes[i + 1];
      bool backward = nodes[i + 1].prev == &nodes[i];
      cout << (backward ? " <" : " ") << "-" << (forward ? "> " : " ");
    }
  }
}