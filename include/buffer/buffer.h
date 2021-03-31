#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

class Buffer
{
public:
    Buffer();
    Buffer(size_t bufferCapacity);
    Buffer(const Buffer& other);
    Buffer& operator=(const Buffer& other);
    ~Buffer();

    unsigned char* getBuffer();
    size_t getCapacity() const;
    size_t getSize() const;
private:
    unsigned char* _buf;
    size_t _capacity;
    size_t _size;
};

#endif // BUFFER_H