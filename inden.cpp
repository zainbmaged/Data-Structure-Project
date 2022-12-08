#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Node{
public:
string tagName;
string tagValue;
int level;
vector<Node*> children;

};

string str1 ;


string take_file(){
    freopen("sample.xml","r",stdin);

    string s="";

    while (!feof(stdin)){ // taking lines from the file and make it one line string
        string k;
        getline(cin,k);
        s+=k;
    }

    return s;
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
