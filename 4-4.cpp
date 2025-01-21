/*4-4 从链表到栈
push_front_list	在链表头结点后插入一个值为val的节点
pop_front_list	删除链表头结点后的节点，如果链表为空则不进行任何操作*/
#include <iostream>
#include <vector>

struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(nullptr) {}
};

using namespace std;

Node head_node(0x7fffffff);

void print_list(Node* head);
void free_list(Node* head);
void push_front_list(Node* head, int val){
  Node* a=new Node(val);
  a->next=head->next;
  head->next=a;
}

void pop_front_list(Node* head){
Node* a=head->next;
   if(!a) return;
   head->next=a->next;
   delete a;
}

int main() {
  Node* head = &head_node;
  head->next = nullptr;

  // Process the operations
  int T;
  cin >> T;
  while (T--) {
    string op_str;
    cin >> op_str;

    if (op_str == "push") {
      int val;
      cin >> val;
      push_front_list(head, val);
    } else if (op_str == "pop") {
      pop_front_list(head);
    } else {
      cout << "error: unknown operation" << endl;
    }
    print_list(head);
  }
  free_list(head);
}

// Free the linked list
void free_list(Node* head) {
  Node* current = head->next;
  while (current) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head->next = nullptr;
}

// Print the linked list
void print_list(Node* head) {
  for (Node* node = head; node; node = node->next) {
    if (node == head) {
      cout << "(head)";
    } else {
      cout << node->val;
    }
    if (node->next) {
      cout << " -> ";
    }
  }
  cout << endl;
}