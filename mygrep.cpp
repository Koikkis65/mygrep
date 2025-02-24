//Jere Lehtimäki mygrep

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//Finds all of the "first characters" of given word from the entire search line or file, and store the position of those characters into vector
void firstCharLocation(const char& firstchar, const string& searchline, vector<int>& charIndex) {
    for(int i = 0; i < searchline.size(); i++) {
        if(firstchar == searchline[i]) {
            charIndex.push_back(i);
        }
    }
}

void FindWordFromString(vector<int>& firstchars, vector<int>& IndexForHit, const string& searchline, const string& searchword) {
    //Find the position of every letter that is the first character of the wanted word and list them in "firstchars" vector
    firstCharLocation(searchword[0], searchline, firstchars);

    //Go through the wanted "string" or file based on the first character positions figured out earlier and
    //cross reference that to the wanted word, if the entire word matches, the initial position index will be listed in IndexForHit
    for(int i = 0; i < firstchars.size(); i++) {
        int firstCharIndex = firstchars[i];
        for(int j = 0; j < searchword.size(); j++) {
            if(searchline[firstCharIndex + j] == searchword[j]) {
                if(j + 1 == searchword.size()) {
                    IndexForHit.push_back(firstCharIndex);
                }
                continue;
            }
            else {
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    //increment 1
    if(argc == 1) {
        vector<int> firstchars;
        vector<int> IndexForHit;
        string searchline, searchword;

        cout << "Give a string from which to search for: ";
        getline(cin, searchline);

        cout << "Give a search string: ";
        getline(cin, searchword);

        
        FindWordFromString(firstchars, IndexForHit, searchline, searchword);

        if(IndexForHit.size() == 0) {
            if(argc == 1) {
                cout << searchword << " NOT found in " << searchline;
            }
        }
        else {
            cout << searchword << " found in position(s): ";
            for(int i = 0; i < IndexForHit.size(); i++) {
                if(i != 0) {
                    cout << ", ";
                }
                cout << IndexForHit[i];
            }
        }
    }

    if(argc == 2) {
        cout << "You need to either start the application without any arguments, or with two arguments. Ie:" << endl;
        cout << "./mygrep <characters to find> <ASCII-filename>" << endl;
    }

    //Increment 2
    if(argc == 3) {
        ifstream file(argv[2]);
        if(!file.is_open()) {
            cout << "The file could not be opened. Please ensure you have a correct file name." << endl;
            return 0;
        }
        bool noMatches = true;
        string searchline;
        while(getline(file, searchline)) {
            vector<int> firstchars;
            vector<int> IndexForHit;
            FindWordFromString(firstchars, IndexForHit, searchline, argv[1]);
            if(IndexForHit.size() > 0) {
                cout << searchline << endl;
                noMatches = false;
            }
        }
        if(noMatches) {
            cout << argv[1] << " NOT found in " << argv[2] << endl;
        }
    }

    //Increment 3
    if(argc == 4) {
        bool lineNumbering = false, Occurences = false;
        string options = argv[1];
        if(options == "-olo") {
            lineNumbering = true;
            Occurences = true;
        }
        else if(options == "-ol") {
            lineNumbering = true;
        }
        else if(options == "-oo") {
            Occurences = true;
        }

        ifstream file(argv[3]);
        if(!file.is_open()) {
            cout << "The file could not be opened. Please ensure you have a correct file name." << endl;
            return 0;
        }
        bool noMatches = true;
        int lineCount = 0, OccurencesCount = 0;
        string searchline;
        while(getline(file, searchline)) {
            lineCount++;
            vector<int> firstchars;
            vector<int> IndexForHit;
            FindWordFromString(firstchars, IndexForHit, searchline, argv[2]);
            if(IndexForHit.size() > 0) {
                OccurencesCount++;
                if(lineNumbering) {
                    cout << "line: " << lineCount << "  " << searchline << endl;
                }
                else {
                    cout << searchline << endl;
                }
                noMatches = false;
            }
        }
        if(Occurences) {
            cout << endl << "Occurences of lines containing \"" << argv[2] << "\": " << OccurencesCount << endl;
        }
        if(noMatches) {
            cout << argv[1] << " NOT found in " << argv[2] << endl;
        }
    }
    
    return 0;
}