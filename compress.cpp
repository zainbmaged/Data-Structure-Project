//Encoding function need string that is to be encoded
vector<int> encoding(string s1)
{
	unordered_map<string, int> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[ch] = i;
	}

	string p = "", c = "";
	p += s1[0];
	int code = 256;
	vector<int> output_code;
	for (int i = 0; i < s1.length(); i++) {
		if (i != s1.length() - 1)
			c += s1[i + 1];
		if (table.find(p + c) != table.end()) {
			p = p + c;
		}
		else {
			output_code.push_back(table[p]);
			table[p + c] = code;
			code++;
			p = c;
		}
		c = "";
	}
	output_code.push_back(table[p]);
	return output_code;
}
//Decoding function output string that will be printed 
//Need vector of int 
string decoding(vector<int> op)
{
	string out = "";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	cout << s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		out += s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
	return out;
}
//Function to write the encoded values to .dat file
void writeFile(string f,vector<int> a) {
	ofstream file(f, ios::binary | ios::out);
	for (int i = 0; i < a.size(); i++) {
		int num = a[i];
		file.write((char *)&num, sizeof(int));
	}
	file.close();
}
//Function to read the encoded values to .dat file
vector<int> readFile(string f) {
	ifstream file(f, ios::binary | ios::in);
	vector<int>b;
	while (!file.eof()) {
		int num;
		file.read((char *)&num, sizeof(int));
		b.push_back(num);
	}
	file.close();
	return b;
}
/* Example how to use functions
int main()
{
	vector<string> t;
	string text;
	string x = "";
	ifstream fileRead("hi.xml");		//input stream 
	while (getline(fileRead, text)) {	//read the file line by line without any spaces in beginning of the line
		size_t i = text.find('<');
		text.erase(0, i);
		t.push_back(text);
		x += t.back();
	}
	fileRead.close();					//close file stream
	vector<int> a = encoding(x);		//encode the desired file and store the output of the function to vector to be stored in .dat file 
	writeFile("hi.dat", a);				//write the ouput vector to .dat file 
	vector<int>b;
	b = readFile("hi.dat");				//read encoded numbers from .dat file to decode 
	b.pop_back();						//delete end of file 
	string s = decoding(b);				//decode to original file
	cout << s;							//output of the file(Note:it is output is in one line) 
	return 0;
}
*/
