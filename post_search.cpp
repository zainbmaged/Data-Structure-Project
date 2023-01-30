#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
  string word, line, username;
  bool found = false;

  cout << "Enter a word: \n";
  cin >>word;

  ifstream xmlFile("sample.xml");
  if (xmlFile.is_open()) {
    while (getline(xmlFile, line)) {
      if (line.find("<name>") != string::npos) {
        regex nameRegex("<name>(.*)</name>");
        smatch match;
        if (regex_search(line, match, nameRegex)) {
          username = match[1];
        }
      }
      if (line.find(word) != string::npos) {
        cout << "Username: " << username << endl;
        found = true;
      }
    }
    xmlFile.close();
  }

  if (!found) {
    cout << "Word not found." << endl;
  }

  return 0;
}
