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
string suggested_followers(string user1, string path)
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
    int nUsers = 0;
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

    vector<string> suggested_follower;
    Node* use1 = new Node();

    for (Node* user : root->children) {
        if (user->name == user1) {
            use1 = user;
        }

    }



    for (string followers : use1->follower) {
        for (string followers2 : root->children[stoi(followers) - 1]->follower) {
            if (followers2 != use1->id ) {
                suggested_follower.push_back(root->children[stoi(followers2) - 1]->id);
                //avoiding redundancy
                sort(suggested_follower.begin(), suggested_follower.end());
                suggested_follower.erase(unique(suggested_follower.begin(), suggested_follower.end()), suggested_follower.end());
            }
        }
    }
    int k = 0;
    for (string suggested : suggested_follower) {
        for (string followers : use1->follower) {
            if (suggested == followers) {
                suggested_follower.erase(suggested_follower.begin() + k, suggested_follower.end());
            }
        }
        k++;
    }
    string suggest = "";
    for (string suggested : suggested_follower) {
        
        suggest += root->children[stoi(suggested) - 1]->name;
        suggest += "-";
    }

    return suggest;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




int main()
{


    //testing Network Analysis function
    // 
    //suggested followers input one user name case sensitive and xml file path
    string suggest = suggested_followers("Sondos Ayman", "D:\\sample.xml");
    cout << suggest << endl;



    return 0;
}
