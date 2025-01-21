#include <iostream>  
#include <cstdlib>  
using namespace std;  
  
typedef int Elemtype;  
typedef struct lineStack {  
    Elemtype data;  
    lineStack* next;  
} lineStack;  
  
// ��ʼ����ջ  
void initstack(lineStack*& head) {  
    head = new lineStack;  
    head->next = NULL;  
}  
  
// ������ջ  
void creatstack(lineStack*& head, int n) {  
    initstack(head);  
    for (int i = 0; i < n; i++) {  
        lineStack* p = new lineStack;  
        cin >> p->data;  
        p->next = head->next;  
        head->next = p;  
    }  
}  
  
// ������ջ  
void destroy(lineStack*& s) {  
    while (s->next) {  
        lineStack* p = s->next;  
        s->next = p->next;  
        delete p;  
    }  
    delete s;  // ��Ҫ����ɾ��ͷ�ڵ�  
}  
  
// ��ջ��  
int length(lineStack* s) {  
    lineStack* q = s->next;  // ��ʼ�� q Ϊ��һ��Ԫ��  
    int count = 0;  
    while (q) {  
        count++;  
        q = q->next;  
    }  
    return count;  
}  
  
// ��ջ  
void push(lineStack*& s, Elemtype e) {  
    lineStack* p = new lineStack;  
    p->data = e;  
    p->next = s->next;  
    s->next = p;  
}  
  
// ��ջ  
bool pop(lineStack*& s, Elemtype& e) {  
    if (s->next == NULL) return false;  
    else {  
        lineStack* p = s->next;  
        e = p->data;  
        s->next = p->next;  
        delete p;  
        return true;  
    }  
}  
  
int main() {  
    lineStack* s;  
    creatstack(s, 6);  
    Elemtype e;  
    if (pop(s, e)) {  
        cout << e << endl;  
    } else {  
        cout << "Stack is empty!" << endl;  
    }  
    push(s, 7);  
    if (pop(s, e)) {  
        cout << e << endl;  
    } else {  
        cout << "Stack is empty!" << endl;  
    }  
    destroy(s);  
    system("pause");  
    return 0;  
}
