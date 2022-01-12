#include <iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAX 1000
class Stack {
    int top1;
    string  a[MAX]; // Maximum size of Stack
public:
    Stack() { top1 = -1; }
    bool push(string  x);
    string pop();
    string  top();
    bool empty();
    int size();
};

bool Stack::push(string  x)
{
    if (top1 >= (MAX - 1)) {
        cout << "Stack Overflow";
        return false;
    }
    else {
        a[++top1] = x;

        return true;
    }
}

  int Stack:: size(){
 return top1+1;
  }
string  Stack::pop()
{
    if (top1 < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        string x = a[top1--];
        return x;
    }
}
string  Stack::top()
{
    if (top1 < 0) {
        cout << "Stack is Empty";
        return 0;
    }
    else {
        string  x = a[top1];
        return x;
    }
}

bool Stack::empty()
{
    return (top1 < 0);
}
