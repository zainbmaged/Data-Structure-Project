#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


using namespace std;
void readxml(string name);

vector <string> contents;
int main(void)
{
   readxml("D:\\Senoir_1\\courses\\DS\\sample.xml");
for (int y=0; y<contents.size() ;y++)
   cout << contents[y] <<endl;


void readxml(string name){
string file_name= name ;
ifstream xmlfile;
xmlfile.open(file_name);
if(xmlfile.fail())
{
    cout << "file failed to open " << endl;

}
string line, word;
while (!xmlfile.eof())//till end of file
{   //read line by line
    getline(xmlfile,line);
    contents.push_back(line);


}
xmlfile.close();
}

