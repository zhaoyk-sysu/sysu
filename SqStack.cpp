#include<iostream>  
using namespace std;  
#define Maxsize 100  
typedef int Elemtype; 
typedef struct SqStack {  
    Elemtype* base;  
    int* top;  
} SqStack;  
  
bool initStack(SqStack& S) {  
    S.base = new Elemtype[Maxsize];  
    S.top = S.base;  
    return true;  
}  
  
bool push(SqStack& S,Elemtype n) {  
    if (S.top - S.base == Maxsize) {  
        cout << "栈满" << endl;  
        return false;  
    }  
    *S.top = n;  
    S.top++;  
    return true;  
}  
  
bool pop(SqStack& S, Elemtype& e) {  
    if (S.base == S.top)  
        return false;  
    e = *(--S.top);  
    return true;  
}  
  
int main() {  
    SqStack S;  
    initStack(S);  
    int n;  
  
    cin >> n;  
    push(S, n);  
    int e;  
    if (pop(S, e)) {  
        cout << "弹出的元素为 " << e << endl;  
    } else {  
        cout << "栈为空" << endl;                
    }  
     
    system("pause");  
    return 0;  
}
