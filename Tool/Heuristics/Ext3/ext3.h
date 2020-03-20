#ifndef EXT3_H
#define EXT3_H

#include "../../heuristic.h"

/**
 * \brief Ext3 evaluation heuristic
 * \author Janine Schneider
 * \date March, 2019
 */
class Ext3 : public Heuristic
{
public:
    Ext3(ByteContainer* rawData);
    ~Ext3();

    /**
     * \brief Heuristic evaluation of possbile block sequences representing files (active, inactive and unknown)
     * \param input Input image as block sequence
     * \return Vector of block sequences representing files
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);

private:
    /**
     * \brief Parses indirect block pointer
     * \param startAddress Block start address
     * \param times Number ob pointers
     * \param blockSize File system block size
     * \param input Input block sequence
     * \return Vector of blocks
     */
    std::vector<uint64_t> parseBlocks(uint32_t startAddress, uint32_t times, uint32_t blockSize, std::vector<uint64_t> input);

    /**
     * \brief Converts file system blocks to 512 byte blocks
     * \param blocks Blocks to be converted
     * \param blockSize File system block size
     * \return Vector of 512 byte blocks
     */
    std::vector<uint64_t> convertBlocks (std::vector<uint64_t> blocks, uint32_t blockSize);

    ByteContainer* m_rawData;
};

#endif // EXT3_H
