#include<iostream>
#include<fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <string>

using namespace std;
void readxml(string name);
vector <string> contents;
string minifying(string str) // function takes a string XML and minifies it
{
    string newStr = regex_replace(str, regex("  "), "");                   // remove every double space
    string nnewStr = regex_replace(newStr, regex("\n"), "");              // remove any new line
    string nnnewStr = regex_replace(nnewStr, regex("> <"), "><");        // remove any space between tags
    //cout << nnnewStr << endl;
    return nnnewStr;                                                  // return the minified XML string
}




int main() //main function
{
    
    
    readxml("C:\\Users\\sondos\\Desktop\\Programming and Electrical Apps\\visual c projects\\ConsoleApplication1\\sample.xml"); //calles the readxml function to return the xml file as a vector

    //code to convert vector to string:
    std::ostringstream out;
    for (string c : contents) {
        out << c;
    }

    std::string s(out.str());
    string l = minifying(s);       //  minifying function is called and the xml string optained from vector conversion is sent as a parameter                                                                                                                                                                                                                 
    //to print the minified string                                                                                                                                                                                                                                                                                                                                           
    cout << l;  
    //code to convert string to file
    fstream file;
    file.open("FILE.txt", ios_base::out);

    if (!file.is_open())
    {
        cout << "Unable to open the file.\n";
        return 0;
    }

    

    file << l;

    file.close();
    

    

    return 0;


}  


                                                                                                                                                                                                                                                                                                                                                  
void readxml(string name)  //function to convert xml file into a vector
{
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
}
