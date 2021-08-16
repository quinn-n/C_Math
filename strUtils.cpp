#include <string>
#include <cstring>
#include <sstream>
#include <ctime>
#include <cstdlib>

std::string chars = "`~1!2@3#4$56^7&8*9(0)-_=+qQwWeErRtTyYuUiIoOpPaAsSdDfFgGhHjJkKlL;:'\"zZxXcCvVbBnNmM,<.>/?";
int charsLen = chars.length();

//get the elements of a string from start to end.
std::string getStringRange(std::string string, int start, int end) {
    std::string returnString = "";
    for(int i=start;i<end;i++) {
        returnString += string[i];
    }
    return returnString;
}

void deleteString(std::string& string, int index) { //delete element index from string.
    std::string newString;
    unsigned long strLen = string.length();
    for(int i=0;i<strLen;i++) {
        if(i != index) {
            newString += string[i];
        }
    }
    string = newString;
}

void deleteInString(std::string& string, int start, int end) { //delete all the elements in string from start to end.
    int numToDelete = end-start;
    for(int i=0;i<numToDelete;i++) {
        deleteString(string,start);
    }
}

//convert an int into a string
std::string atos(int input) {
    std::stringstream stream;
    stream << input;
    return stream.str();
}

std::string atos(long int input) {
  std::stringstream stream;
  stream << input;
  return stream.str();
}

//convert an int into a char string
char* atoc(int num) {
    return (char*) atos(num).c_str();
}

std::string atos(float num) {
    std::stringstream stream;
    stream << num;
    return stream.str();
}

std::string atos(double num) {
    std::stringstream stream;
    stream << num;
    return stream.str();
}

char* atoc(double num) {
    return (char*) atos(num).c_str();
}

std::string atos(long double num) {
    std::stringstream stream;
    stream << num;
    return stream.str();
}

char* atoc(long double num) {
    return (char*) atos(num).c_str();
}

std::string genRandomString(unsigned long long len) {
    std::string outString = "";
    srand(time(NULL));
    for(unsigned long long i=0;i<len;i++) {
        outString += chars[rand()%charsLen];
    }
    return outString;
}
