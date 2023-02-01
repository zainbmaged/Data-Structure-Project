#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <stack>
#include<algorithm>
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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//who is the most influencer user (has the most followers)O(n*m) n is users number and m is followers of most infulencer
string Influncer(vector<Node*> users) {
    int max_followers = 0;
    string influncer;
    for (Node* user : users) {
        if (user->follower.size() > max_followers) {
            influncer = user->name;
            max_followers = user->follower.size();
        }
    }
    return influncer;
}

//who is the most active user (connected to lots of users) O(n^2*m) n is number of users m is max followers of any user
string Active(vector<Node*> users) {
    int max_following = 0;

    string active;
    int tem = 0;
    for (Node* user : users) {
        for (Node* useri : users) {
            for (string follower : useri->follower) {
                if (user->id == follower) {
                    tem++;
                }
            }

        }
        if (tem > max_following) {
            max_following = tem;
            tem = 0;
            active = user->name;
        }
        else {
            tem = 0;
        }
    }

    return active;
}

//the mutual followers between 2 users O(n*m) n is followers of 1st and m is followers of 2nd
vector<string> common_followers(Node* user1, Node* user2, vector<Node*> users) {
    vector<string> common_follower;
    for (string followers1 : user1->follower) {
        for (string followers2 : user2->follower) {
            if (followers1 == followers2) {
                common_follower.push_back(users[stoi(followers1) - 1]->name);
                //avoiding redundancy
                sort(common_follower.begin(), common_follower.end());
                common_follower.erase(unique(common_follower.begin(), common_follower.end()), common_follower.end());
            }
        }
    }
    return common_follower;
}

//for each user, suggest a list of users to follow (the followers of his followers) O(n^2)
vector<string> suggested_followers(Node* user, vector<Node*> users) {
    vector<string> suggested_follower;
    for (string followers : user->follower) {
        for (string followers2 : users[stoi(followers) - 1]->follower) {
            if (followers2 != user->id) {
                suggested_follower.push_back(users[stoi(followers2) - 1]->name);
                //avoiding redundancy
                sort(suggested_follower.begin(), suggested_follower.end());
                suggested_follower.erase(unique(suggested_follower.begin(), suggested_follower.end()), suggested_follower.end());
            }
        }
    }
    return suggested_follower;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{  //vector<int> *adj = new vector<int>[V];
    vector<Node*> users; //cout<<"Reem";
    users=parsing();
   // cout<<users.size(); 
	//testing Network Analysis function
    // 
    //who is the most influencer user (has the most followers)
    string influncer = Influncer(users);
    cout << influncer << endl;

    //who is the most active user (connected to lots of users)
    string active = Active(users);
    cout << active << endl;

    //the mutual followers between 2 users
    vector<string> common = common_followers(users[1], users[2], users);
    for (int i = 0; i < common.size(); i++) {
        cout << common[i] << ",";
    }
    cout << endl;

    //for each user, suggest a list of users to follow
    vector<string> suggested = suggested_followers(users[0], users);
    for (int i = 0; i < suggested.size(); i++) {
        cout << suggested[i] << "-";
    }
    return 0;}

