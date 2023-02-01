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

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//who is the most influencer user (has the most followers)O(n) n is users number 
string Influncer(Node* root) {
    int max_followers = 0;
    string influncer;

    if (root == NULL)
        return "0";
    // using level order traversal 
    // using queue
    queue<Node*> q;  // Create a queue
    q.push(root); // Enqueue root
    while (!q.empty())
    {
        int n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node* p = q.front();
            q.pop();


            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->children.size(); i++) {
                q.push(p->children[i]);
                if (p->children[i]->follower.size() > max_followers) {
                    influncer = p->children[i]->name;
                    max_followers = p->children[i]->follower.size();
                }
            }
            n--;
        }

    }

    return influncer;
}

//who is the most active user (connected to lots of users) O(n^2) n is number of users m is max followers of any user
string Active(Node* root) {

    int max_following = 0;
    string active;
    int tem = 0;


    if (root == NULL)
        return "0";
    // using level order traversal 
    // using queue
    queue<Node*> q;  // Create a queue
    q.push(root); // Enqueue root
    while (!q.empty())
    {
        int n = q.size();

        // If this node has children
        while (n > 0)
        {
            // Dequeue an item from queue and print it
            Node* p = q.front();
            q.pop();


            // Enqueue all children of the dequeued item
            for (int i = 0; i < p->children.size(); i++) {
                q.push(p->children[i]);
                for (int j = 0; j < p->children.size(); j++) {
                    for (int k = 0; k < p->children[j]->follower.size(); k++) {
                        if (p->children[j]->follower[k] == p->children[i]->id) {
                            tem++;
                        }
                    }
                }
                if (tem > max_following) {
                    max_following = tem;
                    tem = 0;
                    active = p->children[i]->name;
                }
                else {
                    tem = 0;
                }
            }

            n--;
        }

    }

    return active;
}

//the mutual followers between 2 users O(n*m) n is followers of 1st and m is followers of 2nd
vector<string> common_followers(Node* user1, Node* user2, Node* root) {
    vector<string> common_follower;




    for (string followers1 : user1->follower) {
        for (string followers2 : user2->follower) {
            if (followers1 == followers2) {
                common_follower.push_back(root->children[stoi(followers1) - 1]->name);
                //avoiding redundancy
                sort(common_follower.begin(), common_follower.end());
                common_follower.erase(unique(common_follower.begin(), common_follower.end()), common_follower.end());
            }
        }
    }


    return common_follower;
}

//for each user, suggest a list of users to follow (the followers of his followers) O(n^2)
vector<string> suggested_followers(Node* user, Node* root) {
    vector<string> suggested_follower;
    for (string followers : user->follower) {
        for (string followers2 : root->children[stoi(followers) - 1]->follower) {
            if (followers2 != user->id) {
                suggested_follower.push_back(root->children[stoi(followers2) - 1]->name);
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
{
    //creating users nodes
    vector<Node*> users;
    // add path here
    users = parsing("D:\\sample.xml");
    //creating root for users
    Node* root = users_root(users);

    //testing Network Analysis function
    // 
    //who is the most influencer user (has the most followers)
    string influncer = Influncer(root);
    cout << influncer << endl;

    //who is the most active user (connected to lots of users)
    string active = Active(root);
    cout << active << endl;

    //the mutual followers between 2 users
    vector<string> common = common_followers(users[1], users[2], root);
    for (int i = 0; i < common.size(); i++) {
        cout << common[i] << ",";
    }
    cout << endl;

    //for each user, suggest a list of users to follow
    vector<string> suggested = suggested_followers(users[0], root);
    for (int i = 0; i < suggested.size(); i++) {
        cout << suggested[i] << "-";
    }
    return 0;
}
