#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

string read_file(){
    ifstream xml_file;
    char c;
    string s;
    xml_file.open("C:\\Users\\dell\\Downloads\\sample.xml");
    xml_file.get(c);
    while(!xml_file.eof())
    {
        s=s+c;
        xml_file.get(c);
    }xml_file.close();
    return s;
}

bool valid(){
    string b=read_file();
    stack<string>s;
    stack <int> nm;
    while (1){
    for (int i = 0;i< b.size(); i++){
        string opening_tag_name = "";
        string closing_tag_name = "";

        if (b[i] == '<')
    {
            switch (b[i + 1])
            {
            case'!':
                break;
            case'?':
                break;
            case'/':
            { //extracting closing tag name
                 for (int j = i + 2; b[j] != '>'; j++)
                {
                    closing_tag_name = closing_tag_name +b[j];
                }
            if (!s.empty() && s.top() == closing_tag_name)
                {
                    s.pop();
                    nm.pop();
                }
                else if (!s.empty() && s.top() != closing_tag_name)
                {  cout << "ERROR! the closing tag " << closing_tag_name << " Not Matching the opening tag " << s.top() << endl;
                  while (s.top() != closing_tag_name)

                    {
                        string closetag = "</" + closing_tag_name + ">";
                        string right_closing_tag = "</" + s.top() + ">";//must be added
                        string data = "";
                        string opentag_of_right_closing_tag = "<" + s.top() + ">"; //tag(top of stack)
                        for (int l = nm.top()+ opentag_of_right_closing_tag.length(); b[l] != '<'; l++)
                        {
                            data = data + b[l];

                        }
                        if (data == "" )
                            //||( isspace(data[1])))//nested tag
                        {
                          b.insert(i -1, right_closing_tag);//********
                            s.pop();
                            nm.pop();
                        }
                        else
                        {
                            b.insert(nm.top()+ opentag_of_right_closing_tag.length() + data.length(), right_closing_tag);
                            s.pop();
                            nm.pop();
                        }
                    }
                    break;
                }//end else if 1
                ///////////////////////////////////////////////////////////////
                else if (s.empty())
                {    cout << "ERROR! the closing tag " << closing_tag_name << " without opening tag" << endl;
                 b.erase(i, closing_tag_name.length() + 1);}
               //////////////////////////////////////////////////////////////
                break;
            }
            default:
            {
                //extracting opening tag name
                for (int k = i + 1; b[k] != '>'; k++)
                {
                    opening_tag_name = opening_tag_name + b[k];
                }
                s.push(opening_tag_name);
                 nm.push(i);
                break;
            }
            }
            continue;
    }//end if
   else
            continue;
    }//end for

    if (s.empty())
    { cout << b<< endl;
        cout << "The XML File is valid" << endl;
        //cout << b;
        return true;
    }
    else
    {
       cout << "ERROR! opening tag " << s.top() << " without closing tag " << endl;
       //handling ERROR
        while (!s.empty())
        {
            string missing_close_tag = "</" + s.top() + ">";
           b = b + missing_close_tag;
            s.pop();
            nm.pop();
        }

    }

}}//end fun



