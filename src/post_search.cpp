#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>

using namespace std;

int main() {
  string word, line, username, filePath;
  bool found = false;
  set<string> usernames;

  cout << "Enter a word: \n";
  cin >> word;
  cout << "Enter the file path: \n";
  cin >> filePath;

  ifstream xmlFile(filePath);
  if (xmlFile.is_open()) {
    while (getline(xmlFile, line)) {
      if (line.find("<name>") != string::npos) {
        regex nameRegex("<name>(.*)</name>");
        smatch match;
        if (regex_search(line, match, nameRegex)) {
          username = match[1];
        }
      }
      if (line.find(word) != string::npos && usernames.find(username) == usernames.end()) {
        cout << "Username: " << username << endl;
        usernames.insert(username);
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
