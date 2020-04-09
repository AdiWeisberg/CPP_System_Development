#include "PhoneticFinder.hpp"
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;

static bool flagAlmost = false;
static string almostWord;

string phonetic::find(string line, string word)
{
    std::vector<string> words;
    string w = "";
    bool flag = true; // continue checking the same word in line 
    int startIndex = 0;
    string ans = "";
    string originalLine = line;
    if (word.find(' ') != string::npos || word.size() == 0) throw std::runtime_error("The searched word is not valid.");
    transform(line.begin(), line.end(), line.begin(), ::tolower);
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    words = splitBySpaces(line, words);
    int start = 0;
    int end = -1;
    for (int i = 0; i < words.size(); i++) {
        w = words.at(i);
        //cout << w << " Vs. " << word << endl;
        if (w.compare(word) == 0) { // While the same word
            //cout << "\t Same!" << endl;
            start = startIndex;
            end = start + w.size();
            for (int j = start; j < end; ++j)
                ans += (originalLine.at(j));
            //cout << ans << endl;
            return ans;
        }
        else {
            if (w.size() == word.size()) {
                if (checkWords(w, word)) {
                    start = startIndex;
                    end = start + w.size();
                    //cout << " start = " << start << " end = " << end << endl;
                    for (int i = start; i < end; ++i)
                        ans += (originalLine.at(i));
                    //cout << ans << endl;
                    return ans;
                }
            }
        }
        startIndex += w.size() + 1;
    }
    if (flagAlmost) {
        flagAlmost = false;
        throw out_of_range{ almostWord + " is not a full word in the sentence" };
    }
    throw out_of_range{"Did not find the word " + word + " in the text"};
}

const vector<string>& phonetic::splitBySpaces(string str2, vector<string>& v)
{
    //std::cout << "Splitting to words..." << std::endl;
    while (str2.find(" ") != string::npos) {
        int found = str2.find(" ");
        v.push_back(str2.substr(0, found));
        str2 = str2.substr(found + 1);
    }
    v.push_back(str2);
    return v;
}

bool phonetic::checkWords(string a, string b)
{
    cout << "word1 = " << a << ", word2 = " << b << endl;
    bool flag = true;
    string newWord = "";
    for (int i = 0; i < a.size(); i++) {
        if (a.at(i) != b.at(i)) {
            if (!isSame(a.at(i), b.at(i))) {
                if (a.find(newWord) != std::string::npos) {
                    flagAlmost = true;
                    almostWord = newWord;
                }
                //cout << a.at(i) << " = " << b.at(i) << endl;
                return false;
            }
            newWord += b.at(i);
        }

    }
    return true;
}

bool phonetic::isSame(char a, char b)
{
    if ((a == 'v' || a == 'w') && (b == 'w' || b == 'v')) return true;
    if ((a == 'g' || a == 'j') && (b == 'j' || b == 'g')) return true;
    if ((a == 's' || a == 'z') && (b == 'z' || b == 's')) return true;
    if ((a == 'd' || a == 't') && (b == 't' || b == 'd')) return true;
    if ((a == 'o' || a == 'u') && (b == 'u' || b == 'o')) return true;
    if ((a == 'i' || a == 'y') && (b == 'y' || b == 'i')) return true;
    if ((a == 'b' || a == 'f' || a == 'p') && (b == 'b' || b == 'f' || b == 'p')) return true;
    if ((a == 'c' || a == 'k' || a == 'q') && (b == 'c' || b == 'k' || b == 'q')) return true;
    return false;
}





