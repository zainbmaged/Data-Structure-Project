// xml2json.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <cstring>

using namespace std;

vector <string> readxml(string name);
string xml2json();
void trim(string &s);
void xml2jsonline( string line, bool check);


// struct a Node for user
struct User
{
    string name;// name
    string id;// user id
    vector<string*>followers;// user followers
    vector<string*>posts;// user posts
};


int main(void)
{
    vector <string> contents= readxml("D:\\sample.xml");
    string s = xml2json();
    cout << s <<endl;
    for (int y = 0; y < contents.size(); y++) {
      //  trim(contents[y]);
        cout << contents[y] << endl;
    }
}

vector <string> readxml(string name)
    {
        vector <string> contents;
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
            contents.push_back(line);


        }
        xmlfile.close();
        return contents;
    }
stringstream json;
vector <string> prev_tag;
    //read ideal space trimmed  xml file and convert it to json
string xml2json() {
    
    json << "{ \t"<<endl;// add intial json bracket
    vector <string> contents = readxml("D:\\sample.xml");
    prev_tag.push_back("");
    for (int i = 0; i < contents.size(); i++) {//for every line
        xml2jsonline( contents[i], true);
   }

    json << endl << "}" << endl;// add final json bracket
    return (json.str());
}
int flag= true;


 void xml2jsonline( string line, bool check) {
     
     int start_open = line.find("<");
     int end_open = line.find(">");
     int start_close = line.find_last_of("/");
     int end_close= line.find_last_of(">");
     
     //for open but not closed in same line tags
     if (start_open != -1 && end_open != -1 && start_close ==-1 ) {

         //if this tag not closed in same line --> contains another tags which is not equivalent to it
         if (start_close ==-1 && line.substr(start_open + 1, end_open - start_open - 1) != prev_tag.back() && prev_tag.back().find(line.substr(start_open + 1, end_open - start_open - 1)) == -1) {
             if (flag == false) {
                 //this will be done only if next tag is the only child of this tag
                 if ((prev_tag.back().find(line.substr(start_open + 1, end_open - start_open - 1)) != -1)) {
                     json << "{0\t" << endl;
                 }
                 flag = true;
                
                 prev_tag.push_back(line.substr(start_open + 1, end_open - start_open - 1));
                 if ((prev_tag.back().find(line.substr(start_open + 1, end_open - start_open - 1)) == -1)) {
                     json  << line.substr(0, start_open) << "\"" << line.substr(start_open + 1, end_open - start_open - 1) << "\": " << "[1" << endl << " {1" << endl;
                 }
                else {
                    json  << line.substr(0, start_open) << "\"" << line.substr(start_open + 1, end_open - start_open - 1) << "\": " << "{2" << endl ;

                 }

             }
             else {
                 flag = false;
                 
                 prev_tag.push_back(line.substr(start_open + 1, end_open - start_open - 1));
                 json << line.substr(0, start_open) << "\"" << line.substr(start_open + 1, end_open - start_open - 1) << "\": {11"<<endl;
             }
         }
         else if(start_close == -1 && line.substr(start_open + 1, end_open - start_open - 1) != prev_tag.back() && prev_tag.back().find(line.substr(start_open + 1, end_open - start_open - 1)) !=-1) {
             json << line.substr(0, start_open) << "\"" << line.substr(start_open + 1, end_open - start_open - 1) << "\": " << "[3" << endl << line.substr(0, start_open)<<"  " << "{3" << endl;;
             prev_tag.push_back(line.substr(start_open + 1, end_open - start_open - 1));
         }
        
         
        
         //(line.substr(end_open + 1, start_close - end_open - 1)).find_first_of(">") != end_close
         
     }
     //tag is opened and closed at the same line
     if (start_open != -1 && end_open != -1 && start_close != -1 && end_close != -1 && end_close !=end_open) {
         json << line.substr(0, start_open) << "\"" << line.substr(start_open + 1, end_open - start_open - 1) << "\": "<<"\"" <<line.substr(end_open + 1, start_close - end_open - 2) << "\"" << endl;
     }
     //line with no opening or closing tag is content of previous tag
     if (start_close == -1 && end_close == -1 && start_open == -1 && end_open == -1) {
         // print whole line 
         
         json << line.substr(0, line.find_first_of("qwertyuiopasdfghjklzxcvbnm")-1) << "\"" <<line.substr(line.find_first_not_of(" ")) << "\""<<"," << endl;
     }
     //tag closing only 
     if (end_close == end_open && start_close != -1 && end_close != -1) {
         if (line.substr(start_close + 1, end_close - start_close - 1) == prev_tag.back()) {

       }
        
     }
 }

     void ltrim(string &s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !isspace(ch);
            }));
    }

    // trim from end (in place)
     void rtrim(string &s) {
        s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !isspace(ch);
            }).base(), s.end());
    }

    // trim from both ends (in place)
     void trim(string &s) {
        ltrim(s);
        rtrim(s);
    }
    
