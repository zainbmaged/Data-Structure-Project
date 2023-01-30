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
{
    str1 = take_file();

    vector<Node*> tem;

    int i=0;
    for (int v = 0; v < str1.length(); v++){
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
        {
            nUsers++; tem.push_back(new Node);
            while(c!='<')c=str1[i++];i--;
        }

        if (name=="id")
         {   string text; c=str1[i++];
          while (c!='<') {text+=c;c=str1[i++];}
         i--; tem[nUsers-1]->id=text;
         }
         if (name=="name")
         { string mi; c=str1[i++];
          while (c!='<') {mi+=c;c=str1[i++];}i--;
          tem[nUsers-1]->name=mi;
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
         {string  body; c=str1[i++];
              while (c!='<') {body+=c;c=str1[i++];}i--;
           tem[nUsers-1]->postBody.push_back(body);
         }
         if (name=="topics")
         {
              while(c!='<') c=str1[i++];i--;
         }
         if (name=="topic")
         {string  topic; c=str1[i++];
             while (c!='<') {topic+=c;c=str1[i++];}i--;
          tem[nUsers-1]->postTopic.push_back(topic);
         }
         if (name=="followers")
         {
              while(c!='<') c=str1[i++];i--;
         }
        
 if (name=="follower")
         { string follow;c=str1[i++];
              while(c!='<') c=str1[i++]; i--;
          c=str1[i++];
          if(c=='<' && str1[i]!='/' ){
          c=str1[i++];
        while (c!='>') {follow+=c;c=str1[i++];}
         if (follow=="id") {
         c=str1[i++];
        string fId;
       while (c!='<') {fId+=c;c=str1[i++];}i--;
       tem[nUsers-1]->follower.push_back(fId);}}
       }

   if(c=='<'&&str1[i]=='/') //closing tag
      {
          while(c!='<')c=str1[i++];i--; }
       }

        }return tem;}

