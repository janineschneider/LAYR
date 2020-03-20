#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <fstream>
#include <istream>
#include <vector>

/**
 * \brief Wrapper class for file stream handling \n
 *        This class creates a vector like interface for file streams
 * \author Janine Schneider
 * \date June, 2018
 */
class ByteContainer
{
public:
    ByteContainer(std::istream& input);

    /**
     * \brief Function which returns the size of the stream
     * \return Size as const size_t
     */
    const uint64_t size() const;

    /**
     * \brief Character access via index
     * \param position Index as int
     * \param lowerBound Lower block sequence access bound
     * \param upperBound Upper block sequence access bound
     * \return Reference to unsigned char
     */
    unsigned char& at(uint64_t position, uint64_t lowerBound, uint64_t upperBound);

    /**
     * \brief Character access via index and pointer offset
     * \param offset Offset as int
     * \param position Index as int
     * \param lowerBound Lower block sequence access bound
     * \param upperBound Upper block sequence access bound
     * \return Reference to unsigned char
     */
    unsigned char& at(uint64_t offset, uint64_t position, uint64_t lowerBound, uint64_t upperBound);

    /**
     * \brief Returns the first character in the stream
     * \return Reference to unsigned char
     */
    unsigned char& front();

    /**
     * \brief Returns the last character in the stream
     * \return Reference to unsigned char
     */
    unsigned char& back();

    /**
     * \warning Do not copy big sequences with that function!
     * \brief Copies a data sequence to a vector \n
     *        Can be used to get a sequence of bytes from the read in raw data \n
     *        For small content pieces (like file allocation table) ONLY
     * \param start Starting index of byte sequence
     * \param end Ending index of byte sequence
     * \return Content of block sequence as bytes
     */
    std::vector<unsigned char> copy2Vector(uint64_t start, uint64_t end);

    /**
     * \brief Function to print stream content to cout
     * \param start Begin of the stream content which shall be copied
     * \param end End of the stream content which shall be copied
     */
    void print2Cout(uint64_t start, uint64_t end);

private:
    /**
     * \brief Character access via index
     * \param position Index as int
     * \return Reference to unsigned char
     */
    unsigned char& at(uint64_t position);

    std::istream& m_input;
    unsigned char m_singleByte;
};

#endif // BYTESTREAM_H
