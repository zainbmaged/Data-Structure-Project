//read ideal  xml file and convert it to json
    string xml2json() {
        stringstream json;
        json << "{  \"users\": ";// add intial json bracket
        vector <string> contents = readxml("D:\\sample.xml");
        
        for (int i = 0; i < contents.size(); i++) {//for every line

            trim(contents[i]);//call trim to remove spaces
            
            if (contents[i] =="</users>") {//if reached end of file return
                return json.str();
            }
            //-------
            else{

                string user2json(User * user);
            
            }
            
        }
            
        json << endl << "}" << endl;// add final json bracket
        return (json.str());
    }
     void ltrim(string &s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !isspace(ch);
            }));
    }

    // trim from end (in place)
     void rtrim(string &s) {
        s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !isspace(ch);
            }).base(), s.end());
    }

    // trim from both ends (in place)
     void trim(string &s) {
        ltrim(s);
        rtrim(s);
    }
    
