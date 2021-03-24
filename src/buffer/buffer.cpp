#include "../../include/buffer/buffer.h"

Buffer::Buffer()
{
    _buf = new unsigned char[4096];
    _buf = {0};
}

Buffer::Buffer(size_t bufferCapacity)
{
    _capacity = bufferCapacity;
    _buf = new unsigned char[_capacity];
    _buf = {0};
}

Buffer::Buffer(const Buffer& other)
{
    _size = other._size;
    _capacity = other._capacity;
    _buf = new unsigned char[_capacity];

    /*copy elements from other buffer to this*/
    for (size_t i = 0; i < _capacity; ++i)
        _buf[i] = other._buf[i]; 
}

Buffer& Buffer::operator=(const Buffer& other)
{
    delete [] _buf;
    _size = other._size;
    _capacity = other._capacity;
    _buf = new unsigned char[_capacity];

    /*copy elements from other buffer to this*/
    for (size_t i = 0; i < _capacity; ++i)
        _buf[i] = other._buf[i];

    return *this;
}

Buffer::~Buffer()
{
    delete [] _buf;
}

size_t Buffer::getCapacity() const
{
    return _capacity;
}

size_t Buffer::getSize() const
{
    return _size;
}