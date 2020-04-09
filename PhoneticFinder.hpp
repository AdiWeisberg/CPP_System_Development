
#include <string>
#include <vector>
using namespace std;

namespace phonetic {
	string find(string test, string word);
	const vector<string>& splitBySpaces(string str2, vector<string>& v);
	bool checkWords(string a, string b);
	bool isSame(char a, char b);
}