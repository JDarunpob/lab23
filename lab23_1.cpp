#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &name, vector<int> &score, vector<char> &grade){
    ifstream source;
    source.open(filename);
    string textline;
    char format[] = "%[^:]: %d %d %d";
    char name1[100];
    int a,b,c;
    while(getline(source,textline)){
        const char *text = textline.c_str();
        sscanf(text,format,name1,&a,&b,&c);
        name.push_back(name1);
        score.push_back(a+b+c);
        grade.push_back(score2grade(a+b+c));
    }
    source.close();

}

void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command: \n";
    getline(cin,input);
    int lo = input.find_first_of(" ");
    command = input.substr(0,lo);
    key = input.substr(lo+1);
}

void searchName(vector<string> name, vector<int> score, vector<char> grade, string key) {
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < name.size(); i++) {
        if (key == toUpperStr(name[i])) { 
            cout << name[i] << "'s score = " << score[i] << "\n";
            cout << name[i] << "'s grade = " << grade[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> name, vector<int> score, vector<char> grade, string key) {  
    bool found = false; 
    cout << "---------------------------------\n";
    for (unsigned int i = 0; i < name.size(); i++) {
        if (key[0] == grade[i]) { 
            cout << name[i] << " (" << score[i] << ")\n";
            found = true; 
        }
    }
    if (!found) { 
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n"; 
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
