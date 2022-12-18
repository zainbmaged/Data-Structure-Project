#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

string readxml(string name);
vector <string> tags(string xmlstring);
string xml2json(vector <string> tag);

int main(void)
{
   string contents = readxml("D:\\sample.xml");
   
    cout << contents << endl;
    vector <string> tag =tags(contents);
    for (int y = 0; y < tag.size(); y++) {
        //  trim(contents[y]);
        cout << tag[y] << endl;
    }
}

//read xml n one string
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

//saving tags  in vector by processing xmlstring char by char
vector <string> tags(string xmlstring) {
    vector <string> tags;// vector saving tags

    for (int i = 0; i < xmlstring.length(); i++)
    {
        string tag_name = "";
        string tag_value = "";
        //for opening tags
        if (xmlstring[i] == '<') {
            // save opening tag name
            for (i = i + 1; xmlstring[i] != '>'; i++)
            {
                tag_name = tag_name + xmlstring[i];
            }
            //push opening tag into the vector
            tags.push_back(tag_name);


            for (int j = i + 1; xmlstring[j] != '<' && j < xmlstring.length(); j++) {
                if (xmlstring[j] != ' ' || xmlstring[j - 1] != ' ' && xmlstring[j] != ' ' || xmlstring[j - 1] != '>' && xmlstring[j] != '<' || xmlstring[j - 1] != ' ' && xmlstring[j] != '\n' && xmlstring[j] != '\t' && xmlstring[j] != ' ' || xmlstring[j - 1] != '\n' && xmlstring[j] != ' ' || xmlstring[j - 1] != '\t') {
                    tag_value += xmlstring[j];
                }

            }
            tags.push_back(tag_value);
        }
        else continue; // if not "<" 
    }
    
    return tags;
}
// changing tags vector into json
stringstream json;
string xml2json(vector <string> tag) {
    auto ptr = tag.begin(); // head of the lst
    json << "{ \t" << endl;// add intial json bracket
  
    for (; ptr != tag.end();) {
    
    }

    json << endl << "}" << endl;// add final json bracket
    return (json.str());
}
