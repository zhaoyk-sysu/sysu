#include <iostream>  
#include <cstdlib>  
using namespace std;  
  
typedef int Elemtype;  
typedef struct lineStack {  
    Elemtype data;  
    lineStack* next;  
} lineStack;  
  
// 初始化链栈  
void initstack(lineStack*& head) {  
    head = new lineStack;  
    head->next = NULL;  
}  
  
// 建立链栈  
void creatstack(lineStack*& head, int n) {  
    initstack(head);  
    for (int i = 0; i < n; i++) {  
        lineStack* p = new lineStack;  
        cin >> p->data;  
        p->next = head->next;  
        head->next = p;  
    }  
}  
  
// 销毁链栈  
void destroy(lineStack*& s) {  
    while (s->next) {  
        lineStack* p = s->next;  
        s->next = p->next;  
        delete p;  
    }  
    delete s;  // 不要忘记删除头节点  
}  
  
// 求栈长  
int length(lineStack* s) {  
    lineStack* q = s->next;  // 初始化 q 为第一个元素  
    int count = 0;  
    while (q) {  
        count++;  
        q = q->next;  
    }  
    return count;  
}  
  
// 入栈  
void push(lineStack*& s, Elemtype e) {  
    lineStack* p = new lineStack;  
    p->data = e;  
    p->next = s->next;  
    s->next = p;  
}  
  
// 出栈  
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
