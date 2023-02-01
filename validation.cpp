#include <iostream>
#include <stack>
#include <string>
#include<vector>
using namespace std;



vector<pair<string,int>>detecterrors(vector<string> xml_data) {
    vector<pair<string,int>>errors;
    stack <string>  tag_stack;
    string tag="";

    for(size_t i=0;i < xml_data.size();i++) {
        // pushing in the stack
        if (xml_data[i][0] == '<' && xml_data[i][1] != '!' && xml_data[i][1] != '?' && xml_data[i][1] != '/') { //not comment
            int j =1;    // there is open tag
            tag ="";
            while (xml_data[i][j] != ' '&& xml_data[i][j] != '>') {
                tag += xml_data[i][j];  //open tag name
                j++;
            }
            tag_stack.push(tag);
        }
        //poping from the stack
        else if (xml_data[i][0] == '<' && xml_data[i][1] == '/') {
            int j =2; //there is closed tag
            tag ="";
            while (xml_data[i][j] != ' ' && xml_data[i][j] != '>') {
                tag += xml_data[i][j]; //close tag name
                j++;
            }//checking
            if(!tag_stack.empty()){
                if (tag_stack.top() == tag) {
                    tag_stack.pop();
                }
                else{
                    errors.push_back({tag,i});
                    tag_stack.pop();

                }
            }
        }
    }


    int l =xml_data.size();
    if(!tag_stack.empty()){
        errors.push_back({tag_stack.top(),l} );
        l++;
        tag_stack.pop();
    }
    return errors;
}




string correcterrors(vector<string> xml_data){
    stack <string>  tag_stack;
    string output="";
    string tag="";
    for(size_t i=0;i < xml_data.size();i++) {
        // pushing in the stack
        if (xml_data[i][0] == '<' && xml_data[i][1] != '!' && xml_data[i][1] != '?' && xml_data[i][1] != '/') {
            int j =1;    // to cut the chars of the tag
            tag ="";
            output += xml_data[i];
            while (xml_data[i][j] != ' '&& xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            tag_stack.push(tag);
        }
        //poping from the stack
        else if (xml_data[i][0] == '<' && xml_data[i][1] == '/') {
            int j =2;
            tag ="";
            while (xml_data[i][j] != ' ' && xml_data[i][j] != '>') {
                tag += xml_data[i][j];
                j++;
            }
            if(!tag_stack.empty()){//checking error
                if (tag_stack.top() == tag) {
                    output += xml_data[i];
                    tag_stack.pop();
                }
                else{ //correct error
                    output+="</"+tag_stack.top()+">";
                    tag_stack.pop();
                }
            }
        }
        //to show the text
        else {
            output+=xml_data[i];
        }
    }

    if(!tag_stack.empty()){
        output+="</"+tag_stack.top()+">";
        tag_stack.pop();
    }
    return output;
}
