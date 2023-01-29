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

class Node {
public:
    string id;
    string name;
    vector < string> postBody;
    vector < string> postTopic;
    vector<string> follower;
    int sizes = 0;
    Node(string id, string name) {
        this->id = id;
        this->name = name;
       
    }
   
};



vector<Node*> toNodes(vector <string> tags) {
    vector<Node*> users;
    for (int i = 0; i < tags.size(); i++) {
        if (tags[i] == "user"){
            users.push_back(new Node(tags[i + 2],tags[i+5]));
            int j = i+5;
            while (tags[j] != "/user" && j+2<tags.size()) {
                
                if (tags[j] == "post") {
                    users[users.size()-1]->postBody.push_back(tags[j + 2]);
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



int main()
{
    string xml_file = readxml("D:\\sample.xml");

    // call function tags to save all tages in tag vector to be used next
    vector <string> tag = tags(xml_file);
    //call function tonodes to convert tags to nodes 
    vector<Node*> users = toNodes(tag);
   
    
    return 0;
}
