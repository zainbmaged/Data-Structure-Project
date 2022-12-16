#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;
vector<int> encoding(string inputStr)
{

	map<string, int> codeTable;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		codeTable[ch] = i;
	}
	string p = "", c = "";
	p += inputStr[0];
	int code = 256;
	vector<int> output_code;
	for (int i = 0; i < inputStr.length(); i++) {
		if (i != inputStr.length() - 1)
			c += inputStr[i + 1];
		if (codeTable.find(p + c) != codeTable.end()) {
			p = p + c;
		}
		else {
			output_code.push_back(codeTable[p]);
			codeTable[p + c] = code;
			code++;
			p = c;
		}
		c = "";
	}
	output_code.push_back(codeTable[p]);
	return output_code;
}

void decoding(vector<int> encodeStr)
{
	map<int, string> codeTable;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		codeTable[i] = ch;
	}
	int tmp = encodeStr[0], n;
	string s = codeTable[tmp];
	string c = "";
	c += s[0];
	int count = 256;
	for (int i = 0; i < encodeStr.size() - 1; i++) {
		n = encodeStr[i + 1];
		if (codeTable.find(n) == codeTable.end()) {
			s = codeTable[tmp];
			s = s + c;
		}
		else {
			s = codeTable[n];
		}
		c = "";
		c += s[0];
		codeTable[count] = codeTable[tmp] + c;
		count++;
		tmp = n;
	}
}
int main()
{
    //copy input file to variable
    string allFile;
    ifstream file("C:\\Users\\sara\\Desktop\\pro\\compress\\sample.xml");
    copy( istream_iterator<char>{ file >> noskipws }, {}, back_inserter( allFile ) );
    file.close();

    //output compressed file
    ofstream myfile;
    myfile.open ("C:\\Users\\sara\\Desktop\\pro\\compress\\compress2.txt");

    //Encode the input file
    vector<int> output_code = encoding(allFile);
    //put encoded data into output compressed file
    for (int i = 0; i < output_code.size(); i++) {
        //cout << output_code[i] << " ";
        myfile <<output_code[i] << " ";
    }

    string outFile;
    ifstream ofile("C:\\Users\\sara\\Desktop\\pro\\compress\\compress2.txt");
    copy( istream_iterator<char>{ ofile >> noskipws }, {}, back_inserter( outFile ) );
    ofile.close();

    //change the string of int to vector of int
    stringstream iss(outFile);
    int n;
    std::vector<int> myNumbers;
    while ( iss >> n )
        myNumbers.push_back( n );

    //decode the data
    decoding(myNumbers);
}
