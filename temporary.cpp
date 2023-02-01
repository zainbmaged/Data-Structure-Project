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
string str1;
int nUsers;


//function to read xml file line by line  and return it in one string in one string O(n)----> n is number of lines in xml file
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
vector<Node*> parsing(string path)
{
    str1 = readxml(path);
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

    return tem;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//creating root with children user
Node* users_root(vector<Node*> users) {
    Node* root = new Node();
    for (Node* user : users) {
        (root->children).push_back(user);
    }
    return root;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    //creating users nodes
    vector<Node*> users;
    // add path here
    users = parsing("D:\\sample.xml");
    
    
    return 0;
}
