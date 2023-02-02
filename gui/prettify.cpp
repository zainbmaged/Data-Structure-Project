#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <stack>

using namespace std;

class Node {
public:
	string tagName;
	string tagValue;
	int level=0;
	vector<Node*> children;

};
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
void prettify(string* input,Node* tem, int presize = 0)
{

    for (int i = 0; i < presize; i++)
        *input+= "\t";
    *input += "<" + tem->tagName;
    *input += ">";
    * input += "\n";
    if (tem->tagValue.size())
    {
        for (int i = 0; i < presize + 1; i++)
            *input += "\t";
        *input += tem->tagValue + " " + "\n";

    }
    for (auto x : tem->children)
    {
        prettify(input,x, presize + 1);
    }
    for (int i = 0; i < presize; i++)
        *input += "\t";
    *input += "</" + tem->tagName + ">" + "\n";
}

string parsing(string *input, string xml)
{
    string str1 = xml;
    Node* tem;
    Node* root = new Node();
    stack <Node*> st;
    int i = 0;
    int lev = 0;
    while (true) { //iterating on all the characters of the file
        tem = new Node;
        char c;
        c = str1[i++];
        if (c == '<' && str1[i] != '/')// opening tag
        {
            c = str1[i++];
            string name;
            while (c != '>') { name += c; c = str1[i++]; }
            tem->tagName = name;
            if (st.empty()) { root = tem; st.push(root); st.top()->level = 0; }
            else { st.top()->children.push_back(tem); st.push(tem); st.top()->level = ++lev; }

        }
        else if (c == '<' && str1[i] == '/')//closing tag
        {
            lev--;
            st.pop();
            while (c != '>')c = str1[i++];
            if (st.empty())break;
        }

        else if (c == '<' && str1[i] == '?') // xml prolog
        {
            while (c != '>') c = str1[i++];
        }
        else if (c == '<' && str1[i] == '!') // comment
        {
            while (c != '>') c = str1[i++];
        }


        else { // taking text
            string text;
            while (c != '<') { text += c; c = str1[i++]; }i--; st.top()->tagValue = text;
        }
    }
    
    prettify(input, root, 0);
    return *input;
}





int main() {

   string xml= readxml("D:\\sample.xml");
    string out =""; //stringstream to save json
    out= parsing(&out,xml);
    cout << out;


    return 0;
}
