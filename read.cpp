#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <stack>


using namespace std;

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
		contents += "\n";

	}
	xmlfile.close();
	return contents;
}
int main() {

	// input file path in format "driver letter : \\ xml_file_name.xml"
	 //read xml file in one string xml_file
	string xml_file = readxml("D:\\sample.xml");
	cout << xml_file;
}
