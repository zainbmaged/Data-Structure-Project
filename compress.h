#include<iostream>
#include<string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//Encoding function need string that is to be encoded
vector<int> encoding(string s1);	

//Decoding function output string that will be printed 
//Need vector of int
string decoding(vector<int> op);

//Function to write the encoded values to .dat file
void writeFile(string f, vector<int> a);

//Function to read the encoded values to .dat file
vector<int> readFile(string f);
