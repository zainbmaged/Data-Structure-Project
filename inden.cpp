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

string str1 ;


string take_file(){
    freopen("sample.xml","r",stdin);

    string s="";

    while (!feof(stdin)){ // taking lines from the file and make it one line string
        string k;
        getline(cin,k);
        s+=k;
    }

    return s;
}


Node * parsing()
{ str1 = take_file();
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
      tem->tagName=name;
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
       while (c!='<') {text+=c;c=str1[i++];}i--;st.top()->tagValue=text;}
    }
     return root;


}

void prettify(Node *tem, int presize=0)
{
    for(int i=0;i<presize;i++)
        cout<<"\t";
    cout<< "<"<<tem->tagName;
    cout<<">"<<endl;
    if(tem->tagValue.size())
    {
        for(int i=0;i<presize+1;i++)
            cout<<"\t";
        cout<< tem->tagValue<<" "<<endl;

    }
    for(auto x:tem->children)
    {
        prettify(x, presize+1);
    }
    for(int i=0;i<presize;i++)
        cout<<"\t";
    cout<<"</" <<tem->tagName<< ">" << endl;
}



int main() {


    Node* r = parsing();
    prettify(r,0);


    return 0;
}

