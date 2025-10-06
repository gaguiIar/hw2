#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{ // "The Great Gatsby" "Oh, the Places You'll Go!"
    // "The" "Great" "Gatsby" | "Oh" "The" "Places" "You" "ll" "Go"
    std::set<std::string> dictionary;
    string word;
    for(char c: rawWords) {
        //add valid characters to string 
        if( (c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'z') )
        {
            word += c;
            //cout << "w:" << word << endl;
        }
        else if (c >= 'A' && c <= 'Z'){
            c = c - 'A' + 'a';
            word += c;
            //cout << "w:" << word << endl;
        }
        else {
            if(word.size() >= 2) {
                dictionary.insert(word);
            }
            word.clear();
        }
        
    }
    if(word.size() >= 2) dictionary.insert(word);
    
    return dictionary;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
