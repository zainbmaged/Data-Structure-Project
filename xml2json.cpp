#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <stack>


using namespace std;
// Functions needed for json --------------------------------------------------------------------------------------------------------------------------------------

string readxml(string name); // read xml
void tags(string xmlstring); // save all tags and values in global vector tags
void xmljson(vector <string> tag); // save json tags and value in global vector jsons
string print_json(vector <string> jsons);// for printing json and return json in one string 
// Global variables-----------------------------------------------------------------------------------------------------------------------------------------------

stack <string> temp;//for close bracket tags
vector <string> tag;// vector saving tags
vector <string> jsons; // for json tages
stringstream json; //stringstream to output json

//driver function--------------------------------------------------------------------------------------------------------------------------------------------------

int main() {

// input file path in format "driver letter : \\ xml_file_name.xml"
 //read xml file in one string xml_file
	string xml_file = readxml("D:\\sample.xml");
	
// call function tags to save all tages in global vector
	tags(xml_file);
// call function  xmljson to save json tags  and values
	xmljson(tag);

// for printing in a json format
	
}

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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//saving tags  in vector by processing xmlstring char by char
void tags(string xmlstring) {
	

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
			tag.push_back(tag_name);


			for (int k = i + 1; xmlstring[k] != '<' && k < xmlstring.length(); k++) {
				if ((xmlstring[k] != ' ' || xmlstring[k - 1] != ' ') && (xmlstring[k] != ' ' || xmlstring[k - 1] != '>') && (xmlstring[k] != '<' || xmlstring[k - 1] != ' ') && (xmlstring[k] != '\t' || xmlstring[k] != ' ') && (xmlstring[k] != ' ' || xmlstring[k - 1] != '\t')) {
					tag_value = tag_value + xmlstring[k]; // a value
				}
			}
			if (tag_value != "") tag.push_back(tag_value);
		}
		else continue; // if not "<" 
	}


	
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// saving json tags
void xmljson(vector <string> tag) {

	int i =0;

	for (; i != tag.size() - 1; ) {
		
		string s = tag[i];//for every tag
		//check first char for opening tags
		if (s[0] != '/' && s[0] != '  ' && s[0] != '{' && s[0] != '}' && s[0] != ',' && s[0] != '[' && s[0] != ']') {
			// as there exist 2 tags at least after this one
			if (tag[i + 1] != tag[tag.size() - 1] && tag[i + 2] != tag[tag.size() - 1]) {
				if (i==0) {
					jsons.push_back(tag[i]);

				}
				if (i != 0 && '/'+ tag[i] != tag[i - 1]) {

					jsons.push_back(tag[i]);
				}
				//value
				string temp = tag[i + 2];
				if ('/' + s == temp) {       // one line xml tags
					jsons.push_back(tag[i+1]);
					i = i + 2; // increase with  to skip the value 
					continue;
				}
				
				if ('/' + s != temp) {  // group opening tag
					jsons.push_back("{");
					i++;
					continue;
				}

			}
		}
		//in case of closing tag
		if (s[0] == '/') {
			
			string tempo = tag[i - 2];
				if (s != '/' + tempo) {
					jsons.push_back("}");
				

			}
				if (i+1 != tag.size() - 1) {
					string next = tag[i + 1]; // find next
					if (next[0] != '/' && next[0] != '}' && next[0] != ',') {//check first char of next tag
						jsons.push_back(","); //tag value add comma
					}
					if (tag[i] == '/' + next) {
						temp.push(tag[i]); // value array push

						int j = jsons.size() - 1;//starting from last element
						j--;// move to previous

						for (j; j != 0;) {
							if ('/' + jsons[j] != tag[i]) {
								j--;//move to previous
								continue;// continue again 
							}
							//done insert opening bracket
							if (jsons[j + 1] != "[") {
								//insert at j+1 position
								jsons.insert(jsons.begin() + j +1 , "[");
							}
							break; // done
						}
						if ('/' + jsons[j] == tag[i] && j == 0) {
							jsons.insert(jsons.begin() + j+1 , "[");
						}
					}
					// for closing bracket ] 

					if (!temp.empty() && tag[i] == temp.top() && tag[i] != '/' + next) {

						jsons.push_back("]");
						temp.pop();

					}
				}
				else { // for last element  check if it has ]
					if (!temp.empty() && tag[i] == temp.top()) {
						jsons.push_back("]");
						temp.pop();
					}
				}
				i++;
			
		}
		
	}

	
}
