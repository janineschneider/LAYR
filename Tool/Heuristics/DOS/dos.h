#ifndef DOS_H
#define DOS_H

#include "../../heuristic.h"

/**
 * \brief DOS evaluation heuristic
 * \author Janine Schneider
 * \date March, 2019
 */
class DOS : public Heuristic
{
public:
    DOS(ByteContainer* rawData);
    ~DOS();

    /**
     * \brief Heuristic evaluation of possbile block sequences representing DOS partitions
     * \param input Input image as block sequence
     * \return Vector of block sequences representing DOS partitions
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);

private:
    /**
     * \brief Extended partition handling function
     * \param offset Partition offset in sectors
     * \param input Extended partition as block sequence
     * \return Vector of block sequences representing DOS partitions
     */
    std::vector<std::vector<uint64_t>> handleExtended(uint32_t offset, std::vector<uint64_t> input);

    ByteContainer* m_rawData;
};

#endif // DOS_H
