#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

string str1 ;
int nUsers;


string readxml(string name)
{
	string contents;
	string file_name = name;
	ifstream xmlfile;
	xmlfile.open(file_name);
	if (xmlfile.fail())
	{
		cout << "file failed to open " << endl;

	}
	string line, word;
	while (!xmlfile.eof())//till end of file
	{   //read line by line
		getline(xmlfile, line);
		contents += line;


	}
	xmlfile.close();
	return contents;
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
     str1 = readxml("sample.xml");
    //cout<<str1;
    vector<Node*> tem;

    int i=0;
   while(1){
    string check;
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
         { string follow;//c=str1[i++];
              while(c!='<') c=str1[i++]; //i--;
         // c=str1[i++];
          if(c=='<' && str1[i]!='/' ){
          c=str1[i++];
        while (c!='>') {follow+=c;c=str1[i++];}
         if (follow=="id") {
         c=str1[i++];
        string fId;
       while (c!='<') {fId+=c;c=str1[i++];}i--;
       tem[nUsers-1]->follower.push_back(fId);}}
       } }

   if(c=='<'&&str1[i]=='/') //closing tag
      { //string check;
          c=str1[i++];c=str1[i++];
          while(c!='>') {check+=c;c=str1[i++];}i--;
            c=str1[i++];
      }
    if(check=="users") break;

        }

        return tem;}

int main()
{  //vector<int> *adj = new vector<int>[V];
    vector<Node*> users; //cout<<"Reem";
    users=parsing();
   // cout<<users.size(); 
    return 0;}

