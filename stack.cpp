#include<bits/stdc++.h>
using namespace std;
bool priority(char a, char b) {
    int power_a = 0, power_b = 0;
    if (a == '^') power_a = 3;
    else if (a == '*' || a == '/') power_a = 2;
    else if (a == '+' || a == '-') power_a = 1;

    if (b == '^') power_b = 3;
    else if (b == '*' || b == '/') power_b = 2;
    else if (b == '+' || b == '-') power_b = 1;

    return power_a > power_b;
}

bool priority_q(char a, char b) {
    int power_a = 0, power_b = 0;
    if (a == '^') power_a = 3;
    else if (a == '*' || a == '/') power_a = 2;
    else if (a == '+' || a == '-') power_a = 1;

    if (b == '^') power_b = 3;
    else if (b == '*' || b == '/') power_b = 2;
    else if (b == '+' || b == '-') power_b = 1;

    return power_a >= power_b;
}


string Infixtopostfix(string s){
    int i = 0;
    int n = s.size();
    string ans = "";
    stack<char> st;
    while(i < n){
        if((s[i] >= 'A' && s[i] <= 'Z') || 
           (s[i] >= 'a' && s[i] <= 'z') || 
           (s[i] >= '0' && s[i] <= '9')) {
            ans += s[i];
        }
        else if(s[i] == '('){
            st.push(s[i]);
        }
        else if(s[i] == ')'){
            while(!st.empty() && st.top() != '('){
                ans += st.top();
                st.pop();
            }
            if(!st.empty()) st.pop(); // Remove '('
        }
        else{
            while(!st.empty() && st.top() != '(' && priority_q(st.top(), s[i])){
                ans += st.top();
                st.pop();
            }
            st.push(s[i]);
        }
        i++;
    }
    while(!st.empty()){
        ans += st.top();
        st.pop();
    }
    return ans;
}

string Infixtoprefix(string s) {
    reverse(s.begin(), s.end());

    // Swap '(' and ')' in the reversed string
    for (char& c : s) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    string ans = "";
    stack<char> st;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        // If the character is an operand, add it to the output
        if ((s[i] >= 'A' && s[i] <= 'Z') ||
            (s[i] >= 'a' && s[i] <= 'z') ||
            (s[i] >= '0' && s[i] <= '9')) {
            ans += s[i];
        }
        // If the character is '(', push it onto the stack
        else if (s[i] == '(') {
            st.push(s[i]);
        }
        // If the character is ')', pop and output from the stack
        else if (s[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // Remove the '('
        }
        // An operator is encountered
        else {
            if (s[i] == '^') {
                while (!st.empty() && st.top() != '(' && priority_q(st.top(), s[i])) {
                    ans += st.top();
                    st.pop();
                }
            } else {
                while (!st.empty() && st.top() != '(' && priority(st.top(), s[i])) {
                    ans += st.top();
                    st.pop();
                }
            }
            st.push(s[i]);
        }
    }

    // Pop all the operators from the stack
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    // Reverse the output to get the prefix expression
    reverse(ans.begin(), ans.end());
    return ans;
}
string Postfix_to_Infix(string s){
     /*
    What we are doing is simpley iterating from starting  of the string
    and if particualar charcter is operand that mean simply push in stack 
    and if operand simply take last 2 elment of stack and just concate like :(You can see below)
   
    
    */
    int i = 0;
    int n = s.size();
    string ans = "";
    stack<string> st;
    while(i<n){
         if((s[i] >= 'A' && s[i] <= 'Z') || 
           (s[i] >= 'a' && s[i] <= 'z') || 
           (s[i] >= '0' && s[i] <= '9')) {
            st.push(string(1,s[i]));
        }
        else {
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string cont = "("+t2+s[i]+t1+")";
            st.push(cont);
        }
        i++;    
    }
    return st.top();

}
string Prefix_to_Infix(string s){
     /*
    What we are doing is simpley iterating from last  of the string
    and if particualar charcter is operand that mean simply push in stack 
    and if operand simply take last 2 elment of stack and just concate like :(You can see below)
   
    
    */
    int n = s.size();
    int i = n-1;
    string ans = "";
    stack<string> st;
    while(i>=0){
         if((s[i] >= 'A' && s[i] <= 'Z') || 
           (s[i] >= 'a' && s[i] <= 'z') || 
           (s[i] >= '0' && s[i] <= '9')) {
            st.push(string(1,s[i]));
        }
        else {
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string cont = "("+t1+s[i]+t2+")";
            st.push(cont);
        }
        i--;    
    }
    return st.top();

}
string Post_to_Prefix(string s){
     /*
    What we are doing is simpley iterating from starting  of the string
    and if particualar charcter is operand that mean simply push in stack 
    and if operand simply take last 2 elment of stack and just concate like :
    s[i]+t2(second element from stack)+t1(first element from stack ) ;
    
    */
    int n = s.size();
    int i = 0;
    string ans = "";
    stack<string> st;
    while(i<n){
        // Operand
         if((s[i] >= 'A' && s[i] <= 'Z') || 
           (s[i] >= 'a' && s[i] <= 'z') || 
           (s[i] >= '0' && s[i] <= '9')) {
            st.push(string(1,s[i]));
        }
        // Operator
        else {
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string cont = s[i]+t2+t1;
            st.push(cont);
        }
        i++;    
    }
    return st.top();

}
string Prefix_to_post(string s){
    /*
    What we are doing is simpley iterating from lasst of the string
    and if particualar charcter is operand that mean simply push in stack 
    and if operand simply take last 2 elment of stack and just concate like :
    t1(first element from stack )+ t2(second element from stack)+ s[i];

    */
    int n = s.size();
    int i = n-1;
    string ans = "";
    stack<string> st;
    while(i>=0){
        // Operand
         if((s[i] >= 'A' && s[i] <= 'Z') || 
           (s[i] >= 'a' && s[i] <= 'z') || 
           (s[i] >= '0' && s[i] <= '9')) {
            st.push(string(1,s[i]));
        }
        // Operator
        else {
            string t1=st.top();
            st.pop();
            string t2=st.top();
            st.pop();
            string cont = t1+t2+s[i];
            st.push(cont);
        }
        i--;    
    }
    return st.top();

}
int main(){
//  INfix to postfix 
   /*
   string x = "a+b*(c^d-e)^(f+g*h)-i";
   cout<<Infixtopostfix(x);
*/

   /* 
   Infix to Prefix is just simply infix to postfix.
   Just reverse the string and then to infix to post and at last reverse answer.

  
  string x ="(a+b)*c-d+f";
  string ans =Infixtoprefix(x);
  cout<<ans;
  */

//  postfix to Infix

// string x ="AB-DE+F*/";
// cout<<Postfix_to_Infix(x);


// prefix to Infix
// string x= "*+PQ-MN";
// cout<<Prefix_to_Infix(x);
    
    // Postfix to Prefix

// string x ="AB-DE+F*/";
// cout<<Post_to_Prefix(x);

//  prefix to post fix
string x="/-AB*+DEF";
cout<<Prefix_to_post(x);

 
}