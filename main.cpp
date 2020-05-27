#include <iostream>
#include "bits/stdc++.h"
 #include "objectCodeTable.h"
using namespace std;


void convertLowerCaseReplaceTabsAndSpacesBySingleSpace(string &str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'') i++;
        }
        if (str[i] == '\t') str[i] = ' ';
    }
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
        if (str[i] == '\'') {
            i++;
            while (str[i] != '\'') i++;
        }
        if (i + 1 < str.length()) {
            if (str[i] == ' ' && (str[i + 1] == ' ' || str[i + 1] == ',')) {
                str.erase(str.begin() + i);
                i--;
            } else if (str[i] == ',' && str[i + 1] == ' ') {
                str.erase(str.begin() + i + 1);
                i--;
            }
        }
    }
    if (str[0] == ' ') str.erase(str.begin());
    if (str[str.length() - 1] == '\r') str.erase(str.end() - 1);
    if (str[str.length() - 1] == ' ')str.erase(str.end() - 1);

}

vector<vector<string>> convertToLabels(vector <string> code) {
    vector <vector<string> > instructions(code.size());
    for(int i = 0;i<code.size();i++) {
        std::string s = code[i];
        std::string delimiter = " ";
        s+=" ";
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            instructions[i].push_back(token);
            s.erase(0, pos + delimiter.length());
        }
    }
    return instructions;
}

vector<string> readFile(const string& filename) {
    vector<string> answer;
    std::ifstream file(filename);
    std::string str;
    while (std::getline(file, str)) {
        answer.push_back(str);
    }
    return answer;
}

vector<regex> initializeRegexVector() {
    vector<regex> regexVector;
    string declarationRes = R"([a-z]\w*\s(resb|resw)\s\d{1,4})";
    string declarationByte = R"([a-z]\w*\s(byte)\s(x'([a-f0-9]{0,14})'|c'(\D|\S){0,15}'))";
    string declarationWord = R"([a-z]\w*\s(word)\s-?\d{1,4})";
    regex declaration("(" + declarationWord + "|" + declarationByte + "|" + declarationRes + ")");
    regexVector.push_back(declaration);
    regex access(R"(([a-z]\w*\s)?\+?(st|ld)(x|a|b|s|t|ch)\s(\*|@?[a-z]\w*(,[a-z]\w*)?|#(\d{1,4}|\w*)))");
    regexVector.push_back(access);
    regex jump(R"(([a-z]\w*\s)?(td|rd|wd|jeq|jlt|jle|jge|j|jgt|jsub|tixr)\s(\*|[a-z]\w*))");
    regexVector.push_back(jump);
    regex rsub("rsub");
    regexVector.push_back(rsub);
    regex commentLine(R"(\.(\W|\S)*)");
    regexVector.push_back(commentLine);
    regex emptyLine("");
    regexVector.push_back(emptyLine);
    return regexVector;
}
string decToHexa(int n) 
{    
    // char array to store hexadecimal number 
    string hexaDeciNum="";
      
    // counter for hexadecimal number array 
    int i = 0; 
    while(n!=0) 
    {    
        // temporary variable to store remainder 
        int temp  = 0; 

        // storing remainder in temp variable. 
        temp = n % 16; 
          
        // check if temp < 10 
        if(temp < 10) 
        { 
            hexaDeciNum+= temp + 48; 
            i++; 
        } 
        else
        { 
            hexaDeciNum+= temp + 55; 
            i++; 
        } 
          
        n = n/16; 
    } 
      
    // printing hexadecimal number array in reverse order 
    reverse(hexaDeciNum.begin(),hexaDeciNum.end());
    return hexaDeciNum;
} 

void writeobjCode(vector<vector<string>>code)
{
    
    objectCodeTable table;
    freopen("objcode.txt","w",stdout);
    int prog_len=0;
    while (code[0][0].size()<6)
    {
        code[0][0]+=" ";
    }
    while (code[0][2].size()<6)
    {
        code[0][2]="0"+code[0][2];
    }
    string Sprog_len=decToHexa(prog_len);

    while (Sprog_len.size()<6)
    {
        Sprog_len="0"+prog_len;
    }
    string HRecord="H"+code[0][0]+"^"+code[0][2]+"^"+prog_len;
}

int main() {
    vector<regex> regexVector = initializeRegexVector();
    vector<string> code = readFile("1.txt");

    for (int i = 0; i < code.size(); i++) {
        bool found = false;
        convertLowerCaseReplaceTabsAndSpacesBySingleSpace(code[i]);
        cout<<code[i]<<"\n";
        for (auto & j : regexVector) {
            if (regex_match(code[i], j)) {
                found = true;
            }
        }
        if (!found) cout << "Unmatched " << i << " " << code[i] << endl;
    }
    vector <vector< string>> v = convertToLabels(code);
    /*for(int i = 0;i<v.size();i++){
        for(int j = 0;j<v[i].size();j++) {
            cout<<v[i][j]<<" ";
        }
        cout<<"\n";
    }*/
    writeobjCode(v);
    return 0;
}