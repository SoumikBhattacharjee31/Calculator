#include<iostream>
#include<string>
#include<stack>
#include<cmath>
class signNode{
    char sign;
    long double val;
    signNode* left;
    signNode* right;
public:
    signNode(char sign, long double val=0, signNode* left=NULL, signNode* right=NULL){
        this->sign=sign;
        this->val=val;
        this->left=left;
        this->right=right;
    }
    long double getval(){
        return val;
    }
    signNode* getleft(){
        return left;
    }
    signNode* getright(){
        return right;
    }
    char getsign(){
        return sign;
    }
};
void deletebst(signNode* node){
    if(node==NULL)return;
    //std::cout<<node->getval()<<" ";
    if(node->getleft()!=NULL)deletebst(node->getleft());
    if(node->getright()!=NULL)deletebst(node->getright());
    if(node->getleft()!=NULL)delete node->getleft();
    if(node->getright()!=NULL)delete node->getright();
}
long double solve(signNode* node){
    long double temp;
    //std::cout<<node->getval()<<" ";
    if(node->getsign()=='+')
        temp=solve(node->getleft())+solve(node->getright());
    else if(node->getsign()=='-')
        temp=solve(node->getright())-solve(node->getleft());
    else if(node->getsign()=='*')
        temp=solve(node->getleft())*solve(node->getright());
    else if(node->getsign()=='/')
        temp=1.0*solve(node->getright())/solve(node->getleft());
    else if(node->getsign()=='^')
        temp=std::pow(solve(node->getright()),solve(node->getleft()));
    else if(node->getsign()==0)
        temp=node->getval();
    else std::cout<<"Hello"<<std::endl;
    return temp;
}
void my_truth_table_generator(std::string s){
    s='('+s+')';
    int priority[128]={0};
    priority['+']=priority['-']=1;
    priority['*']=priority['/']=2;
    priority['^']=2;
    std::stack<char> cstk;
    std::stack<signNode*> nstk;
    signNode* tree=NULL;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(')
            cstk.push(s[i]);
        else if(s[i]>='0'&&s[i]<='9'){
            long double num=0;
            int k=i;
            for(;k<s.size()&&s[k]>='0'&&s[k]<='9';k++)
                num=num*10+(int)(s[k]-'0');
            signNode* temp= new signNode(0,num);
            //std::cout<<num<<" ";
            nstk.push(temp);
            i=k-1;
        }
        else if(priority[s[i]]>0){
            while(!cstk.empty()&&cstk.top()!='('&&priority[cstk.top()]>priority[s[i]]){
                char temp0=cstk.top();
                cstk.pop();
                signNode* temp1=nstk.top();
                nstk.pop();
                signNode* temp2=nstk.top();
                nstk.pop();
                tree= new signNode(temp0,0,temp1,temp2);
                nstk.push(tree);
            }
            cstk.push(s[i]);
        }
        else if(s[i]==')'){
            while(!cstk.empty()&&cstk.top()!='('){
                char temp0=cstk.top();
                cstk.pop();
                signNode* temp1=nstk.top();
                nstk.pop();
                signNode* temp2=nstk.top();
                nstk.pop();
                tree= new signNode(temp0,0,temp1,temp2);
                nstk.push(tree);
            }
            cstk.pop();
        }
    }
    tree=nstk.top();
    nstk.pop();
    std::cout<<solve(tree)<<std::endl;
    deletebst(tree);
    delete tree;
}
int main(){
    freopen("in.txt","r",stdin);
    std::string s;
    std::cin>>s;
    my_truth_table_generator(s);
    std::getchar();
    return 0;
}
