#include "bytecontainer.h"
#include "customexception.h"
#include <iostream>

ByteContainer::ByteContainer(std::istream& input) : m_input(input)
{

}

const uint64_t ByteContainer::size() const
{
    m_input.seekg(0, m_input.end);
    size_t length = m_input.tellg();
    m_input.seekg(0, m_input.beg);

    return length;
}

unsigned char& ByteContainer::at(uint64_t position, uint64_t lowerBound, uint64_t upperBound)
{
    //TODO Block size currently always 512 byte
    uint64_t lowerByte = lowerBound * 512;
    uint64_t upperByte = (upperBound * 512) + 512;

    if ((position < lowerByte) || (position > upperByte)) {
        throw bvex;
    }

    m_input.seekg(position);
    m_singleByte = (unsigned char)m_input.get();
    m_input.seekg(0, m_input.beg);
    m_input.clear();

    return m_singleByte;
}

unsigned char& ByteContainer::at(uint64_t offset, uint64_t position, uint64_t lowerBound, uint64_t upperBound)
{
    //TODO Block size currently always 512 byte
    uint64_t lowerByte = lowerBound * 512;
    uint64_t upperByte = (upperBound * 512) + 512;

    if (((offset + position) < lowerByte) || ((offset + position) > upperByte)) {
        throw bvex;
    }

    m_input.seekg(offset + position);
    m_singleByte = (unsigned char)m_input.get();
    m_input.seekg(0, m_input.beg);
    m_input.clear();

    return m_singleByte;
}

unsigned char& ByteContainer::front()
{
    return at(0);
}

unsigned char& ByteContainer::back()
{
    size_t last = size() - 1;
    m_input.seekg(last);
    m_singleByte = (unsigned char)m_input.get();
    m_input.seekg(0, m_input.beg);

    return m_singleByte;
}

std::vector<unsigned char> ByteContainer::copy2Vector(uint64_t start, uint64_t end)
{
    uint64_t size = end - start + 1;
    uint64_t counter = 0;
    std::vector<unsigned char> sequence;

    m_input.seekg(start);

    char c;
    unsigned char uc;
    while (m_input.get(c)) {
        if(counter >= size) {
            break;
        }
        uc = (unsigned char)c;
        sequence.push_back(uc);
        counter++;
    }

    m_input.seekg(0, m_input.beg);

    return sequence;
}

void ByteContainer::print2Cout(uint64_t start, uint64_t end)
{
    uint64_t count = (end - start);
    uint32_t bufferSize = 1048576;
    char buffer[1048576];

    if (count < bufferSize) {
        bufferSize = count;
    }

    while(count >= bufferSize) {
        m_input.seekg(start);
        m_input.read(buffer, bufferSize);
        std::cout.write(buffer, bufferSize);
        count -= bufferSize;
        start += bufferSize;
    }

    m_input.read(buffer, count);
    std::cout.write(buffer, count);

    m_input.seekg(0, m_input.beg);
}

unsigned char& ByteContainer::at(uint64_t position)
{
    m_input.seekg(position);
    m_singleByte = (unsigned char)m_input.get();
    m_input.seekg(0, m_input.beg);
    m_input.clear();

    return m_singleByte;
}
