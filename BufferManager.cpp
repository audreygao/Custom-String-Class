/**
 * Ya Gao
 * ECE141A: Assignment 1
 */

#include "BufferManager.hpp"
#include <iostream>
#include <string.h>
#include <cstring>

BufferManager::BufferManager(size_t preSize, const char * str){
    size_t size;
    if(preSize != 0 && preSize > strlen(str)) { // there's size user wants to set to
        size = preSize;
    } else { 
        size = strlen(str);
    }

    //allocate memory
    buffer = new char[size];

    //update buffer size
    bufferSize = size;
}

BufferManager:: ~BufferManager() {
    delete [] buffer;
    bufferSize = 0;
}

// gives the size of the string, not the buffer
size_t BufferManager::strSize() {
    return strlen(buffer);
}

//reside the buffer when it's full
void BufferManager::resize(size_t newLen) {
    if(newLen > bufferSize-1) {
        bufferSize = 2*newLen; //new buffersize
        char * tmp = new char[bufferSize];
        strcpy(tmp, buffer);
        delete [] buffer;
        buffer = tmp;
    }
}

//shift string starting at index to the right for len size
void BufferManager::rightShift(size_t index, size_t len) {
    if(len == 0) {return;}

    size_t partSize = strSize() - index; //size of the shifting portion

    if (strSize() + len > bufferSize) {
        resize(index + len + partSize); //resize buffer if necessary
    }

    buffer[strSize()+len] = '\0'; //append '\0' to indicate end of string

    //copy the chars to shifted positions
    for(size_t i = strSize()-1+len; i>= index+len; i--) {
        buffer[i] = buffer[i-len];
    }
    
}

//shift to left
void BufferManager::leftShift(size_t index, size_t len) {
    if (len == 0) {return;}
    for(size_t i = index-len; i < strSize()-len; i++) {
        buffer[i] = buffer[i+len];
    }
    buffer[strSize()-len] = '\0'; // indicate end of string
}

//replace buffer starting at index start with given str
void BufferManager::replaceHelper(size_t start, const char * str) {
    int len = strlen(str);
    int j = 0;
    for(size_t i = start; i < start + len; i++ ) {
        buffer[i] = str[j];
        j++;
    }
}