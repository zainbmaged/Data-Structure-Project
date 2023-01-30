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

#pragma warning(suppress : 4996)

using namespace std;



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//saving tags  in vector by processing xmlstring char by char O(n)----> n is number of chars in xml file
vector <string> tags(string xmlstring) {
    vector <string> tag;

    for (int i = 0; i < xmlstring.length(); i++)
    {
        string tag_name = "";
        string tag_value = "";
        //for  tags
        if (xmlstring[i] == '<') {
            // save opening tag name and closing tag name/
            for (i = i + 1; xmlstring[i] != '>'; i++)
            {
                tag_name = tag_name + xmlstring[i];
            }
            //push  tag into the vector
            tag.push_back(tag_name);


            for (int k = i + 1; xmlstring[k] != '<' && k < xmlstring.length(); k++) {
                if ((xmlstring[k] != ' ' || xmlstring[k - 1] != ' ') && (xmlstring[k] != ' ' || xmlstring[k - 1] != '>') && (xmlstring[k] != '<' || xmlstring[k - 1] != ' ') && (xmlstring[k] != '\t' || xmlstring[k] != ' ') && (xmlstring[k] != ' ' || xmlstring[k - 1] != '\t')) {
                    tag_value = tag_value + xmlstring[k]; // a value
                }
            }
            if (tag_value != "") tag.push_back(tag_value);
        }
        else continue; // if not "<" 
    }


    return tag;//returning tag vector
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// class nodes 
class Node {
public:
    string id;
    string name;
    vector < string> postBody;
    vector < string> postTopic;
    vector<string> follower;
    int size = 0;
    Node(string id, string name) {
        this->id = id;
        this->name = name;
        size++;
    }
    
};


//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//function to construct user nodes and insert followers , posts and topics for each
vector<Node*> toNodes(vector <string> tags) {
    vector<Node*> users;
    for (int i = 0; i < tags.size(); i++) {
        if (tags[i] == "user") {
            users.push_back(new Node(tags[i + 2], tags[i + 5]));
            int j = i + 5;
            while (tags[j] != "/user" && j + 2 < tags.size()) {

                if (tags[j] == "post") {
                    users[users.size() - 1]->postBody.push_back(tags[j + 2]);
                }
                if (tags[j] == "follower") {
                    users[users.size() - 1]->follower.push_back(tags[j + 2]);
                }
                if (tags[j] == "topic") {
                    users[users.size() - 1]->postTopic.push_back(tags[j + 1]);
                }
                j++;
            }
        }
    }
    return users;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Network Analysis Functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//who is the most influencer user (has the most followers)O(n*m) n is users number and m is followers of most infulencer
string Influncer(vector<Node*> users) {
    int max_followers=0;
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
                    tem ++;
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
            if (followers1 == followers2 ) {
                common_follower.push_back(users[stoi(followers1)-1]->name);
                //avoiding redundancy
                sort(common_follower.begin(),common_follower.end());
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
        for (string followers2 : users[stoi(followers) -1]->follower) {
            if (followers2 != user->id) {
                suggested_follower.push_back(users[stoi(followers2)-1]->name);
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
    string xml_file = readxml("D:\\sample.xml");

    // call function tags to save all tages in tag vector to be used next
    vector <string> tag = tags(xml_file);
    //call function tonodes to convert tags to nodes 
    vector<Node*> users = toNodes(tag);

    //testing Network Analysis function
    // 
    //who is the most influencer user (has the most followers)
    string influncer = Influncer(users);
    cout << influncer<<endl;

    //who is the most active user (connected to lots of users)
    string active = Active(users);
    cout << active << endl;

    //the mutual followers between 2 users
    vector<string> common = common_followers(users[1],users[2],users);
    for (int i = 0; i < common.size(); i++) {
        cout << common[i]<<",";
    }
    cout  << endl;

    //for each user, suggest a list of users to follow
    vector<string> suggested = suggested_followers(users[0], users);
    for (int i = 0; i < suggested.size(); i++) {
        cout << suggested[i] << "-";
    }

    return 0;
}
