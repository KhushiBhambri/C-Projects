#include <iostream>
#include "stack.h"
using namespace std;
bool isOperator(char x) {
  switch (x) {
  case '+':
  case '-':
  case '/':
  case '*':
    return true;
  }
  return false;
}
int prec(string c){
  if(c == "^")
  return 3;
  else if(c == "*" || c == "/")
  return 2;
  else if(c == "+" || c == "-")
  return 1;
  else
  return -1;
}
string preToPost(string pre_exp){
    Stack s;
    int length = pre_exp.size();
    for (int i=length-1;i>=0;i--){//right to left read
        if (isOperator(pre_exp[i])) {
            string op1 = s.top(); s.pop();
            string op2 = s.top(); s.pop();
            string temp = op1 + op2 + pre_exp[i];
            s.push(temp+" ");
        }
        else if(pre_exp[i] == ' ')continue;//this
        else {
          int num=0;
          while(isdigit(pre_exp[i])) {
          num = num * 10 + (int)(pre_exp[i] - '0');
              i--;  }
              i++;
              string str=to_string(num);
              reverse(str.begin(),str.end());
              s.push(str+" ");
        }
    }
    return s.top();
}
string postToPre(string post_exp)
{
    Stack s;
    int length = post_exp.size();
    for (int i = 0; i < length; i++) { // left to right read
        if (isOperator(post_exp[i])) {
            string op1 = s.top();  s.pop();
            string op2 = s.top();  s.pop();
            string temp = post_exp[i]+op2+ op1;
            s.push(" "+temp);
        }
        else if(post_exp[i] == ' ')continue;//this
        else {int num=0;
        while(isdigit(post_exp[i])) {
        num = num * 10 + (int)(post_exp[i] - '0');
            i++;  }
            i--;
            string str=to_string(num);
            s.push(" "+str);
      	}
    }
    return s.top();
}
string preToInfix(string pre_exp) {
Stack  s;
int length = pre_exp.size();
for (int i = length - 1; i >= 0; i--) { //right to left read
	if (isOperator(pre_exp[i])) {
	string op1 = s.top(); s.pop();
	string op2 = s.top(); s.pop();
	string temp = "(" + op1 + pre_exp[i]+" "+ op2 + ")";
	s.push(temp+" ");
	}
  else if(pre_exp[i] == ' ')continue;//this
	else {string str="";
  while(isdigit(pre_exp[i])) {
      str+=pre_exp[i];
      i--;  }
      i++;
      reverse(str.begin(),str.end());
      s.push(str+" ");
	}
}
return s.top();
}
string infixToPostfix(string s)
{
    Stack st;
    st.push("#");
    int l = s.length();
    string ns="";
    for(int i = 0; i < l; i++)
    {
          if (isdigit(s[i])){
            int num=0;
            while(isdigit(s[i])){
              num = num * 10 + (int)(s[i] - '0');
                  i++;  }
                  i--;
             ns+=to_string(num)+" ";
        }
        else if(s[i] == ' ') continue;
        else if(s[i] == '(') st.push("(");
        else if(s[i] == ')') {
            while(st.top() != "#" && st.top() != "(")
            {
                string c = st.top();
                st.pop();
                ns += c+" ";
            }
            if(st.top() == "(")
            {
                string c = st.top();
                st.pop();
            }
        }
        else{
            string strin(1, s[i]);
            while(st.top() != "#" && prec(strin)<=prec(st.top())){
                string c = st.top();
                st.pop();
                ns += c+" ";
            }
            string str(1, s[i]);
            st.push(str);
        }
    }
    while(st.top() != "#"){
        string c = st.top();
        st.pop();
        ns += c;
    }
    return ns;
}
string postToInfix(string post_exp){
  string res= postToPre(post_exp);
  res= preToInfix(res);
  return res;
}
string infixToPrefix(string in_exp){
  string res=infixToPostfix(in_exp);
  res=postToPre(res);
  return res;
}
int evaluatePostfix(string& exp) {
    Stack s;
    int i;
    //if (!s) return -1;
    for (i = 0; exp[i]; ++i)
    {
        if(exp[i] == ' ')continue;
        else if (isdigit(exp[i])){
            int num=0;
            while(isdigit(exp[i])) {
            num = num * 10 + (int)(exp[i] - '0');
                i++;  }
            i--;
            s.push(to_string(num));
        }
       else{
            int val1 = stoi(s.pop());
            int val2 = stoi(s.pop());
            switch (exp[i]){
            case '+': s.push(to_string(val2 + val1)); break;
            case '-': s.push(to_string(val2 - val1)); break;
            case '*': s.push(to_string(val2 * val1)); break;
            case '/': s.push(to_string(val2/val1)); break;
            }
        }
    }
    return stoi(s.pop());
}
int evaluatePrefix(string& exp) {
    string post = preToPost(exp);
    return evaluatePostfix(post);
}
int evaluateInfix(string& exp) {
    string In = infixToPostfix(exp);
    return evaluatePostfix(In);
}

int main() {
  cout<<"\t\t\t Alzebraic Notations Calculator\n";
  menu:
  cout<<"\n\nexample notations :"<<endl;
  cout << "Infix : (1 - 23 / 4 ) *( 56 / 7 - 89 )\n";
  cout << "Prefix : * - 1 / 23 4 - / 56 7 89 \n";
  cout << "Postfix : 1 23 4 / - 56 7 / 89 - * \n\n";
  cout<<"MENU: "<<endl;
  cout<<"1. Infix to Postfix conversion"<<endl;
  cout<<"2. Postfix to Infix conversion"<<endl;
  cout<<"3. Infix to prefix conversion"<<endl;
  cout<<"4. Prefix to infix conversion"<<endl;
  cout<<"5. Prefix to postfix conversion"<<endl;
  cout<<"6. postfix to prefix conversion"<<endl;
  cout<<"7. infix evaluation "<<endl;
  cout<<"8. postfix evaluation "<<endl;
  cout<<"9. prefix evaluation"<<endl;
  int x;
  string exp;
  cout<<"Enter Query NO. : ";
  cin>>x;
  cin.sync();
  switch(x){
    case 1: cout<<" Enter Infix expression : ";
            getline (cin,exp);
            cout<<"Postfix : " <<infixToPostfix(exp)<<endl;
            break;
    case 2: cout<<" Enter Postfix expression : ";
            getline (cin,exp);
            cout<< "Infix : "<<postToInfix(exp)<<endl;
            break;
    case 3: cout<<" Enter Infix expression : ";
            getline (cin,exp);
            cout<<"Prefix : " <<infixToPrefix(exp)<<endl;
            break;
    case 4: cout<<" Enter Prefix expression : ";
            getline (cin,exp);
            cout<< "Infix : "<<preToInfix(exp)<<endl;
            break;
    case 5: cout<<" Enter Prefix expression : ";
            getline (cin,exp);
            cout<<"Postfix : "<<preToPost(exp)<<endl;
            break;
    case 6: cout<<" Enter Postfix expression : ";
            getline (cin,exp);
            cout<<"Prefix : " <<postToPre(exp)<<endl;
            break;
    case 7: cout<<" Enter Infix expression : ";
            getline (cin,exp);
            cout<<"value : "<<evaluateInfix(exp)<<endl;
            break;
    case 8: cout<<" Enter Postfix expression : ";
            getline (cin,exp);
            cout<<"value : "<<evaluatePostfix(exp)<<endl;
            break;
    case 9: cout<<" Enter Prefix expression : ";
            getline (cin,exp);
            cout<<"value : "<<evaluatePrefix(exp)<<endl;
            break;
    case 10: return 0;
             break;
    default: cout<<"Enter Valid Query! "<<endl;
  }
  goto menu;
  //string pre_exp = "* - 1 / 23 4 - / 56 7 89";
  //string post_exp = "1 23 4 / - 56 7 / 89 - *";
  //string in_exp = "(1 - 23 / 4 ) *( 56 / 7 - 89 )";
  //string exp = "400 200 + 3 / 5 * 7 +";
  return 0;
}
