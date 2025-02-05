#include <iostream>
#include <cstring>
using namespace std;

void concatenateStrings(char *, const char *, int bufferSize);
bool isSubstring(const char*, const char*);

int main(){
    const int BUFFERSIZE = 80;
    char string1[80];
    char string2[80];

    cout<<"Enter two strings: ";
    cin>>string1>>string2;

    concatenateStrings(string1,string2,BUFFERSIZE);
    cout<<"Concatenated String: "<<string1<<endl;
    cout<<(isSubstring(string1,string2) ? "Yes" : "No")<<endl;


    char largeString[] = "ThisIsAVeryLargeStringThatWillFillUpTheBuffer";
    concatenateStrings(largeString,"Extra",10);

    cout<<"Testing Substring at different positions: "<<endl;
    cout<<(isSubstring("abcdef","abc") ? "Yes" : "No")<<endl;
    cout<<(isSubstring("abcdef","bcd") ? "Yes" : "No")<<endl;
    cout<<(isSubstring("abcdef","def") ? "Yes" : "No")<<endl;

    
}

void concatenateStrings(char *s1, const char *s2, int bufferSize){
    int s1Length = strlen(s1);
    int s2Length = strlen(s2);
    if (s1Length + s2Length > bufferSize){
        cout<<"Error: Buffer Overflow"<<endl;
        return;
    }

    while (*s1 != '\0') s1++;
    for(; (*s1=*s2);s1++,s2++); //for(; *s2!='\0'; ++s1, ++s2) -> *s1 = *s2
    *s1 = '\0';
}

bool isSubstring(const char *s1, const char *s2){
    return strstr(s1,s2) != nullptr;
}