#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

string str1 ;
int nUsers;


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



class Node{
public:
string id;
string name;
vector < string> postBody;
vector < string> postTopic;
vector<string> follower;
};



vector<Node*> parsing()
{ str1 = take_file();
    vector<Node*> tem;
    int i=0;

    while(true){
    char c;

    c=str1[i++];
  if(c=='<' && str1[i]!='/' )// opening tag
    {  c=str1[i++];
        string name;
        while (c!='>') {name+=c;c=str1[i++];}
        if (name=="users")
         {
              while(c!='<')c=str1[i++];i--;
         }
        if (name=="user")
        {nUsers++; tem.push_back(new Node);
            while(c!='<')c=str1[i++];i--;
        }

        if (name=="id")
         { string text; c=str1[i++];
          while (c!='<') {text+=c;c=str1[i++];}
         i--; tem[nUsers]->id=text;
         }
         if (name=="name")
         { string text; c=str1[i++];
          while (c!='<') {text+=c;c=str1[i++];}i--;
          tem[nUsers]->name=text;
         }
         if (name=="posts")
         {
              while(c!='<') c=str1[i++];i--;
         }
         if (name=="post")
         {
              while(c!='<') c=str1[i++];i--;
         }
         if (name=="body")
         {string  body;
              while (c!='<') {body+=c;c=str1[i++];}i--;
           tem[nUsers]->postBody.push_back(body);

         }

         if (name=="topics")
         {
              while(c!='<') c=str1[i++];i--;
         }
         if (name=="topic")
         {string  topic;
             while (c!='<') {topic+=c;c=str1[i++];}i--;

          tem[nUsers]->postTopic.push_back(topic);
         }
         if (name=="followers")
         {
              while(c!='<') c=str1[i++];i--;
         }
         if (name=="follower")
         { string follow;
              while(c!='<') c=str1[i++]; i--;
          c=str1[i++];
          if(c=='<' && str1[i]!='/' ){
          c=str1[i++];
        while (c!='>') {follow+=c;c=str1[i++];}
         if (follow=="id") {
         c=str1[i++];
        string fId;
       while (c!='<') {fId+=c;c=str1[i++];}i--;
       tem[nUsers]->follower.push_back(fId);}}

       }
    }


   if(c=='<'&&str1[i]=='/') //closing tag
      {  c=str1[i++];
          while(c!='<')c=str1[i++];i--;}

        } return tem;}

void addEdge(vector<int> adj[],int first,int second)
{
    adj[first].push_back(second);
     adj[second].push_back(first);
}



int main()
{
    vector<Node*> users;
    users=parsing();
    int c=nUsers;
    vector<int> adj[nUsers];
    for(auto x: users)
    {
       int s=x->follower.size();
       for(int i=0;i<s;s++)
       {string idd=x->id; int iddd=stoi(idd);
        string t=x->follower[i];
       int tt=stoi(t);
       addEdge(adj,iddd,tt);

       }
    }

}
