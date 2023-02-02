#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Node{
public:
string tagName;
string tagValue;
int level;
vector<Node*> children;

};

string str1 ;string prettified="";

Node * parsing(string s)
{ string str1 = s;
    Node *tem;
    Node *root=new Node;
    stack <Node*> st;
    int i=0;
    int lev=0;
    while(true){ //iterating on all the characters of the file
    tem=new Node;
    char c;
    c=str1[i++];
    if(c=='<' && str1[i]!='/' )// opening tag
    {  c=str1[i++];
        string name;
        while (c!='>') {name+=c;c=str1[i++];}
      tem->name=name;
       if(st.empty()) {root=tem; st.push(root); st.top()->level=0;}
       else {st.top()->children.push_back(tem);st.push(tem);st.top()->level=++lev;}

    }
    else if(c=='<'&&str1[i]=='/')//closing tag
        {
            lev--;
            st.pop();
            while(c!='>')c=str1[i++];
            if(st.empty())break;
        }

    else if(c=='<' && str1[i]=='?') // xml prolog
    {
        while(c!='>') c=str1[i++];
    }
    else if (c=='<' && str1[i]=='!') // comment
    {
        while(c!='>') c=str1[i++];
    }


    else { // taking text
        string text;
       while (c!='<') {text+=c;c=str1[i++];}i--;st.top()->data=text;}
    }
     return root;


}



string prettify(Node *tem, int presize=0)
{
    for(int i=0;i<presize;i++)
        prettified+="\t";
    prettified+= "<";
    prettified+= tem->tagName;
    prettified+=">";
    prettified+="\n";
    if(tem->tagValue.size())
    {
        for(int i=0;i<presize+1;i++)
            prettified+="\t";
        prettified+=tem->tagValue;
        prettified+=" ";
        prettified+="\n";
    }
    for(auto x:tem->children)
    {
        prettify(x, presize+1);
    }
    for(int i=0;i<presize;i++)
        prettified+="\t";
    prettified+="</" ;
    prettified+=tem->tagName;
    prettified+=">";
    prettified+="\n";
 return prettified;}

