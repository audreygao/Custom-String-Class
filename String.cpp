/**
 * Ya Gao
 * ECE141A: Assignment 1
 */

#include "String.hpp"
#include <iostream>
#include <cstring>
#include <string.h>

namespace ECE141 {

    //OCF
    String::String(const String &aString, size_t aPresize): BufferManager(aPresize, aString.buffer){
        strcpy(buffer, aString.buffer);
    }
 
    String::String(const char* aBuffer, size_t aPresize): BufferManager(aPresize, aBuffer){
        strcpy(buffer, aBuffer);
    }

    String:: ~String(){
    }

    //copy constructor
    String& String::operator=(const String &aCopy){
        BufferManager(0, aCopy.buffer);
        strcpy(buffer, aCopy.buffer);
        return *this;
    }

    String& String::operator=(const char* aBuffer){
        BufferManager(0, aBuffer);
        strcpy(buffer, aBuffer);
        return *this;
    }

    //accessors...
    size_t String::size() const {
        return strlen(buffer);
    }

    //mutation methods
    char& String::operator[](int pos) {
        if( 0 <= pos && pos < size()) { //check index range
            return buffer[pos];
        } else {
        throw std::out_of_range("Index out of range.");
        }
    }
    
    //return a new string with aString appended to current string
    String String::operator+(const String &aString){
        //copy a new string with the current string
        String newString = *this;

        //update the size of the buffer
        size_t len = size() + aString.size();
        newString.resize(len);

        //concatenate two strings
        strcat(newString.buffer, aString.buffer);
        return newString;
    } 

    String String::operator+(const char* aBuffer){
        String newString = *this;
        size_t len = size() + strlen(aBuffer);
        newString.resize(len);
        strcat(newString.buffer, aBuffer);
        return newString;
    }

    // apend aString to current string
    String& String::operator+=(const String &aString) {
        //update size
        size_t len = size() + aString.size();
        resize(len);

        //append string
        strcat(buffer, aString.buffer);
        return *this;

    } 

    String& String::operator+=(const char* aBuffer) {
        size_t len = size() + strlen(aBuffer);
        resize(len);
        strcat(buffer, aBuffer);
        return *this;
    }

    //insert part of/whole string to given index at current string
    String& String::insert(size_t anIndex, const String &aString, size_t aMaxCopyLen) {
        if (0 <= anIndex && anIndex < size()) {
            size_t maxLen = aMaxCopyLen? aMaxCopyLen : aString.size();

            //shift values to right and fill in the "empty spots"
            rightShift(anIndex, maxLen);
            replace(anIndex, maxLen, aString.buffer);
        }
        return *this;
    }
            
    String& String::insert(size_t anIndex, const char* aString, size_t aMaxCopyLen){
        if (0 <= anIndex && anIndex < size()) {
            size_t maxLen = aMaxCopyLen? aMaxCopyLen : strlen(aString);
            rightShift(anIndex, maxLen);
            replace(anIndex, maxLen, aString);
        }
        return *this;
    }
    

    String& String::replace(size_t anIndex, size_t aMaxCopyLen, const String &aSubString){

        size_t maxLen = aMaxCopyLen? aMaxCopyLen : aSubString.size();

        //check for index in range
        if (0 <= anIndex && anIndex < size()) {
            //determine whether to shift right or shift left
            if (maxLen < aSubString.size()) { //replacing str is longer, original needs to shift right
                rightShift( anIndex + maxLen, aSubString.size() - maxLen);
            } else { //replacing str is shorter/equal, original needs to shift left
                leftShift( anIndex + maxLen, maxLen - aSubString.size());
            }

            //fill in the replacement
            replaceHelper(anIndex, aSubString.buffer);
        }
        return *this;
    }
            
    String& String::replace(size_t anIndex, size_t aMaxCopyLen, const char *aSubString){

        size_t maxLen = aMaxCopyLen? aMaxCopyLen : strlen(aSubString);

        if (0 <= anIndex && anIndex < size()) {
            //determine whether to shift right or shift left
            if (maxLen < strlen(aSubString)) {
                rightShift( anIndex + maxLen, strlen(aSubString) - maxLen);
            } else {
                leftShift( anIndex + maxLen, maxLen - strlen(aSubString));
            }

            //fill in the replacement
            replaceHelper(anIndex, aSubString);
        }
        return *this;
    }

    //remove aCount size of the String starting at anIndex
    String& String::erase(size_t anIndex, size_t aCount){

        if(anIndex + aCount >= size()) { //aCount extends passed end of string
            buffer[anIndex] = '\0'; //erase everything from anIndex
        } else {
            //shift everything after the erased to the left
            leftShift(anIndex+aCount, aCount);
        }

        return *this;
    }

//Comparision methods...
    int String::compare( const String& aString ) const {

        //compare strings lexographically using strcmp
        int result = strcmp(buffer, aString.buffer);

        //return different values based on results
        if (result < 0 ) {
            result = -1;
        } else if (result > 0 ) {
            result = 1;
        } else {result = 0;}
        return result;
    }
    
    bool String::operator==(const String &aString) const {
        return compare(aString)==0;
    }
    bool String::operator==(const char* aBuffer) const {
        return strcmp(buffer, aBuffer)==0;
    }

    bool String::operator<(const String &aString) const {
        return compare(aString)==-1;
    }
    bool String::operator<(const char* aBuffer) const {
        return strcmp(buffer, aBuffer)==-1;
    }

    //Search...
    int String::find( const String &aSubString, size_t anOffset) const {

        //make a copy of the current String and leftshift so that offset becomes index 0
        String tmp(*this);
        tmp.leftShift(anOffset, anOffset);

        //use strstr to get char * of the first instance of the given string
        char * index = strstr(tmp.buffer, aSubString.buffer);

        //given string not found
        if (index == nullptr) {
            return -1;
        }

        //calculate the index based on the char *
        return index - tmp.buffer + anOffset;
    }
            
    //stream...c
    std::ostream& operator << (std::ostream &out, const String &aStr) {
        out << aStr.buffer;
        return out;
    }
    std::istream& operator >> (std::istream &in,  String &aString) {
        //in >> aString.buffer;
        return in;
    }

}