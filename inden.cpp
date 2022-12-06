
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;
vector <string> readxml(string name);
vector <string> prettify(string name);

int main(void)
{
    vector <string> contents= prettify("sample.xml");
  //  for (int y = 0; y < contents.size(); y++)
    //    cout << contents[y] << endl;

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

vector <string> prettify(string name)
{ //vector<string> check;
 vector <string> tem=readxml( name);
vector <string>::iterator it;
for (int y = 0; y < tem.size();y++)
{ it= find(tem.begin(),tem.end(),"</");
if(it==tem.end())
{cout<< "\t"<<endl;
 cout << tem[y] << endl;}

   // int i= tem[y].find("<",y);
    //int j=tem[y].find(">",i+1);
}}

/*for (int y = 0; y < tem.size();)
   {  int i= tem[y].find("<",y);
       while (i!= tem[y].size())
       {int j=tem[y].find(">",i+1);
      check.push_back(tem[y].substr(i,j-i+1));
        y=j+1;
        i= tem[y].find("<",y);}
   } return tem;}
 //if (line.find("<",y))
    {
        if (line.find("</"))
            cout<< " /t"<< endl;
    }
       check.push(tem[y]);
        if (closing tag) pass;
else increase identation;


}*/
