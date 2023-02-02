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
#include<queue>
#pragma warning(suppress : 4996)

using namespace std;





//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Node {
public:
    string id;
    string name;
    vector < string> postBody;
    vector < string> postTopic;
    vector<string> follower;
    vector<Node*> children;
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// creating user nodes and adding attributes of each
string common_followers(string user1, string user2, string path)
{
    //reading xml in one string
    string contents;
    string file_name = path;
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
    string str1 = contents;
    int nUsers=0;
    //cout<<str1;
    vector<Node*> tem;

    int i = 0;
    while (1) {
        string check;
        char c;
        c = str1[i++];
        if (c == '<' && str1[i] != '/')// opening tag
        {
            c = str1[i++];
            string name;
            while (c != '>') { name += c; c = str1[i++]; }
            if (name == "users")
            {
                while (c != '<')c = str1[i++]; i--;
            }
            if (name == "user")
            {
                nUsers++; tem.push_back(new Node);
                while (c != '<')c = str1[i++]; i--;
            }

            if (name == "id")
            {
                string text; c = str1[i++];
                while (c != '<') { text += c; c = str1[i++]; }
                i--; tem[nUsers - 1]->id = text;
            }
            if (name == "name")
            {
                string mi; c = str1[i++];
                while (c != '<') { mi += c; c = str1[i++]; }i--;
                tem[nUsers - 1]->name = mi;
            }
            if (name == "posts")
            {
                while (c != '<') c = str1[i++]; i--;
            }
            if (name == "post")
            {
                while (c != '<') c = str1[i++]; i--;
            }
            if (name == "body")
            {
                string  body; c = str1[i++];
                while (c != '<') { body += c; c = str1[i++]; }i--;
                tem[nUsers - 1]->postBody.push_back(body);
            }
            if (name == "topics")
            {
                while (c != '<') c = str1[i++]; i--;
            }
            if (name == "topic")
            {
                string  topic; c = str1[i++];
                while (c != '<') { topic += c; c = str1[i++]; }i--;
                tem[nUsers - 1]->postTopic.push_back(topic);
            }
            if (name == "followers")
            {
                while (c != '<') c = str1[i++]; i--;
            }

            if (name == "follower")
            {
                string follow;//c=str1[i++];
                while (c != '<') c = str1[i++]; //i--;
           // c=str1[i++];
                if (c == '<' && str1[i] != '/') {
                    c = str1[i++];
                    while (c != '>') { follow += c; c = str1[i++]; }
                    if (follow == "id") {
                        c = str1[i++];
                        string fId;
                        while (c != '<') { fId += c; c = str1[i++]; }i--;
                        tem[nUsers - 1]->follower.push_back(fId);
                    }
                }
            }
        }

        if (c == '<' && str1[i] == '/') //closing tag
        { //string check;
            c = str1[i++]; c = str1[i++];
            while (c != '>') { check += c; c = str1[i++]; }i--;
            c = str1[i++];
        }
        if (check == "users") break;

    }


    //creating root with children user
    
    Node* root = new Node();
    for (Node* user : tem) {
        (root->children).push_back(user);
    }
    
    vector<string> common_follower;
    Node* use1 = new Node();
    Node* use2=new Node();
    for (Node* user : root->children) {
        if (user->name == user1) {
             use1 = user;
        }
        if (user->name == user2) {
             use2 = user;
        }
    }


    for (string followers1 : use1->follower) {
        for (string followers2 : use2->follower) {
            if (followers1 == followers2) {
                common_follower.push_back(root->children[stoi(followers1) - 1]->name);
                //avoiding redundancy
                sort(common_follower.begin(), common_follower.end());
                common_follower.erase(unique(common_follower.begin(), common_follower.end()), common_follower.end());
            }
        }
    }
    string common = "";
    for (string commone : common_follower) {
        common += commone;
        common += "-";
    }

    return common;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




int main()
{
    

    //testing Network Analysis function
    // 
    //common followers input two user name case sensitive and xml file path
    string common = common_followers("Reem Hassan","Sara Ramdan","D:\\sample.xml");
    cout << common << endl;

    
   
    return 0;
}
