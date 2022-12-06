
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
   // string parent= "<users>";
    //tring children1= "<user>";
    //ing children2= "<name>";
    //string children3= "<id>" ;
   // string children4= "<posts>";
    //string children5= "<post>" ;
    //string children6= "<body>" ;
    //string children7= "<topic>" ;
    //string children8= "<topics>" ;
   // string children9= "<followers>" ;
    //string children10= "<follower>" ;
std::stack<string> *ch;
//stack *ch;
 vector <string> tem=readxml(name);
//vector<string>::iterator itr;
for (int y = 0; y < tem.size();y++)
{ int i ;

if ((tem[y].find("<users>"))||(tem[y].find("</users>"))) {cout << tem[y] << endl;}
if ((tem[y].find("<user>"))||(tem[y].find("</user>"))) {cout<< "\t"<<endl;cout << tem[y] << endl;}
if ((tem[y].find("<id>"))||(tem[y].find("</id>"))|| (tem[y].find("<posts>"))||(tem[y].find("</posts>"))||(tem[y].find("<name>"))||(tem[y].find("</name>"))|| (tem[y].find("<followers>"))||(tem[y].find("</followers>"))) { if(tem[y].find("<id>")||(tem[y].find("</id>"))) { if(ch->top()=="<follower>") {ch->pop();cout<<"\t"<<"\t"<<"\t"<< "\t"<< endl;cout << tem[y] << endl;}} cout<< "\t"<<"\t"<<endl; cout <<tem[y]<<endl;}
if ((tem[y].find("<post>"))||(tem[y].find("</post>"))||(tem[y].find("<follower>"))||(tem[y].find("</follower>",y))) { if(tem[y].find("<follower>",y)){ch->push("<follower>");cout<< "\t"<<"\t"<<"\t" <<endl;cout << tem[y] << endl;}}
if ((tem[y].find("<body>"))||(tem[y].find("</body>"))|| (tem[y].find("<topics>"))||(tem[y].find("</topics>",y))) {cout<< "\t"<<"\t"<<"\t"<< "\t"<< endl;cout << tem[y] << endl;}
if ((tem[y].find("<topic>"))||(tem[y].find("</topic>"))) {cout<< "\t"<<"\t"<<"\t"<< "\t"<<"\t"<<endl; cout << tem[y] << endl;}

}
}
//vector <string>::iterator it;
/*for (int y = 0; y < tem.size();y++)
{ it= find(tem.begin(),tem.end(),"</");
if(it==tem.end())
{cout<< "\t"<<endl;
 cout << tem[y] << endl;}

   // int i= tem[y].find("<",y);
    //int j=tem[y].find(">",i+1);
}} if(tem.find("<id>",y)||if(tem.find("</id>",y)) {if(ch->top()=="<follower>")  cout<< "\t"<<"\t"<<"\t"<< "\t"<< endl; cout <<tem[y]<<endl;}}}
*/
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
