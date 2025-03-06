//Jere Lehtimäki mygrep

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string strToLowercase(string input) {
    string output;
    for( char c : input ) {
        output += tolower(c);
    }
    return output;
}

int main(int argc, char* argv[]) {
    //increment 1
    if(argc == 1) {
        string searchline, searchword;

        cout << "Give a string from which to search for: ";
        getline(cin, searchline);

        cout << "Give a search string: ";
        getline(cin, searchword);

        size_t found = searchline.find(searchword);


        if(found == string::npos) {
            cout << searchword << " NOT found in " << searchline;
        }
        else {
            cout << searchword << " found in position(s): " << found << endl;
        }
    }
    

    if(argc == 2) {
        cout << "You need to either start the application without any arguments, or with two arguments. Ie:" << endl;
        cout << "./mygrep <characters to find> <ASCII-filename>" << endl;
    }

    //Increment 2
    if(argc == 3) {
        vector<string> stringToPrint;
        string searchline;
        bool noMatches = true;
        ifstream file(argv[2]);
        if(!file.is_open()) {
            cout << "The file could not be opened. Please ensure you have a correct file name and in the correct position in command line." << endl;
            return 0;
        }
        while(getline(file, searchline)) {
            if(searchline.find(argv[1]) != string::npos) {
                stringToPrint.push_back(searchline);
                noMatches = false;
            }
        }
        if(noMatches) {
            cout << argv[1] << " NOT found in " << argv[2] << endl;
        }
        else {
            cout << "\"" << argv[1] << "\" found in lines: " << endl;
            for(string s : stringToPrint) {
                cout << s << endl;
            }
        }
    }
    
    //Increment 3 & 4
    if(argc == 4) {
        vector<string> stringToPrint;
        vector<int> lineNumbers;
        bool lineNumbering = false, Occurences = false, reverseSearch = false, ignoreCase = false;
        bool noMatches = true;
        int lineCount = 0, OccurencesCount = 0;
        string searchline;
        string argv0 = argv[0], argv2 = argv[2], argv3 = argv[3];
        string options = argv[1];
        if(options.find("-o") != string::npos) {
            if(options.find("l", 2) != string::npos) {
                lineNumbering = true;
            }
            if(options.find("o", 2) != string::npos) {
                Occurences = true;
            }
            if(options.find("r", 2) != string::npos) {
                reverseSearch = true;
            }
            if(options.find("i", 2) != string::npos) {
                ignoreCase = true;
            }
        }

        
 


        ifstream file(argv3);
        if(!file.is_open()) {
            cout << "An exception occurred. Exception Nr. -1" << endl;
            cout << "Could not open file: \"" << argv3 << "\". Make sure you have the correct file name and path."<< endl;
            return 0;
        }

        //ignorecase searchword
        if(ignoreCase) {
            argv2 = strToLowercase(argv2);
        }
        //Line by line check
        while(getline(file, searchline)) {
            lineCount++;

            //searchline to lowercase
            if(ignoreCase) {
                searchline = strToLowercase(searchline);
            }
            //default search
            if(!reverseSearch && searchline.find(argv2) != string::npos) {
                stringToPrint.push_back(searchline);
                OccurencesCount++;
                noMatches = false;
                if(lineNumbering) {
                    lineNumbers.push_back(lineCount);
                }
            }

            //reverse search
            if(reverseSearch && searchline.find(argv2) == string::npos) {
                stringToPrint.push_back(searchline);
                OccurencesCount++;
                noMatches = false;
                if(lineNumbering) {
                    lineNumbers.push_back(lineCount);
                }
            }
        }

        if(noMatches) {
            cout << argv2 << " NOT found in " << argv3 << endl;
        }
        //Found lines with line numbers and no reverse search
        else if(!noMatches && lineNumbering && !reverseSearch) {
            cout << "\"" << argv[2] << "\" found in lines: " << endl;
            for(int i = 0; i < stringToPrint.size(); i++) {
                cout << lineNumbers[i] << "  " << stringToPrint[i] << endl;
            }
        }
        //Found lines without line numbers and no reverse search
        else if(!noMatches && !reverseSearch) {
            cout << "\"" << argv[2] << "\" found in lines: " << endl;
            for(string s : stringToPrint) {
                cout << s << endl;
            }
        } else if(!noMatches && reverseSearch) {
            for(string s : stringToPrint) {
                cout << s << endl;
            }
        }
        
        //Occurences for both normal and reverse search
        if(Occurences && reverseSearch) {
            cout << "Occurences of lines NOT containing \"" << argv[2] << "\": " << OccurencesCount << endl;
        }
        else if(Occurences) {
            cout << "Occurences of lines containing \"" << argv[2] << "\": " << OccurencesCount << endl;
        }
    }
    
    return 0;
}