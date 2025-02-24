//Jere Lehtimäki mygrep

#include <iostream>
#include <vector>

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
    
    vector<int> firstchars;
    vector<int> IndexForHit;
    string searchline, searchword;

    //increment 1, the result printing is at the end, and is tailored so that it works for both given lines, and files.
    if(argc == 1) {
        cout << "Give a string from which to search for: ";
        getline(cin, searchline);

        cout << "Give a search string: ";
        getline(cin, searchword);

        
        FindWordFromString(firstchars, IndexForHit, searchline, searchword);

        
    }


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
    return 0;
}