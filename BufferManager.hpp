#ifndef BufferManager_hpp
#define BufferManager_hpp

#include <iostream>

class BufferManager {
    public:

    char * buffer;
    size_t bufferSize = 0;
    size_t strSize();

    BufferManager();
    BufferManager(size_t preSize, const char * str);
    ~BufferManager();
    void resize(size_t newLen);

    void rightShift(size_t index, size_t len);
    void leftShift(size_t index, size_t len);
    void replaceHelper(size_t start, const char * str);

};

#endif