#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include "BufferManager.hpp"
#include <iostream>

namespace ECE141 {

    class String : public BufferManager{

    public:
        String(const String &aString, size_t aPresize=0);
        String(const char* aBuffer, size_t aPresize=0);
        ~String();
        String& operator=(const String &aCopy);
        String& operator=(const char* aBuffer);
        
        //accessors...
        size_t size() const;    

        //mutation methods...
        char& operator[](int pos);
    
        String operator+(const String &aString);  //append (construct) methods
        String operator+(const char* aBuffer);
        
        String& operator+=(const String &aString);  //append (to self) methods
        String& operator+=(const char* aBuffer);

        String& insert(size_t anIndex, const String &aString, size_t aMaxCopyLen);
        String& insert(size_t anIndex, const char* aString, size_t aMaxCopyLen);
        
        String& replace(size_t anIndex, size_t aMaxCopyLen, const String &aSubString);
        String& replace(size_t anIndex, size_t aMaxCopyLen, const char *aSubString);
            
        String& erase(size_t anIndex, size_t aCount); //from given position, remove N chars...("cut")
        
        //Comparision methods...
        int compare( const String& aString ) const; //[-1 if <, 0 if ==, 1 if >]
        
        bool operator==(const String &aString) const;
        bool operator==(const char* aBuffer) const;

        bool operator<(const String &aString) const;
        bool operator<(const char* aBuffer) const;

        //Search...
        int find( const String &aSubString, size_t anOffset = 0 ) const;
                
        //stream...
        friend std::ostream& operator << (std::ostream &out, const String &aStr);
        friend std::istream& operator >> (std::istream &in,  String &aString);      
    };

}
#endif