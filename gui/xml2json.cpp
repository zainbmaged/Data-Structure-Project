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
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// creating user nodes and adding attributes of each
int XML_TO_JSON(string* input, string xml) 
{
    
    string str1 =xml;
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

    int max_followers = 0;
    string influncer;
    *input += "\"users\" : { \n";
    if (root == NULL)
        return 0;
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
                *input += "\t\"user\" : [ \n";
                *input += "\t { \n";
                *input += "\t \"id \" :"+ p->children[i]->id+"\n";
                *input += "\t \"name\" :" + p->children[i]->name + "\n";
                *input += "\t  \"posts\" : { \n";
                *input += "\t    \"post\" : [ \n ";
                for (string posts : p->children[i]->postBody) {
                    *input += "\t\t {\n";
                    remove(posts.begin(), posts.end(), ' ');
                    *input += "\t\t \"body\" " +posts + ",\n";
                    *input += " \t\t\t\"topics \" : {\n";

                    *input += "\t\t\t\"topic \" : [\n";
                    for (string topics : p->children[i]->postTopic) {
                        
                        *input += "\t"+ topics + "\n";

                        
                    }
                    *input += "\t\t\t\t]\n";
                    *input += " \t\t\t}\n";
                    
                }
                *input += "\t  \"followers\" : { \n";
                *input += "\t    \"follower\" : [ \n ";
                for (string follow : p->children[i]->follower) {
                    *input += "\t\t {\n";
                    *input += "\t\t\t\"id \" : " + follow + "\n";
                    *input += "\t\t }\n";
                }
                *input += "\t\t]\n";
                *input += "\t }\n";
            }
            n--;
        }

    }
    *input += " }\n";
    return 1;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------






int main()
{


    string xml_file = readxml("D:\\sample.xml");
    string out = "";


    XML_TO_JSON(&out, xml_file);
    cout << out;

    return 0;
}
