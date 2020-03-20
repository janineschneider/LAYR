#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "bytecontainer.h"
#include <cstdint>

/**
 * \brief Heuristic base class
 * \author Janine Schneider
 * \date January, 2019
 */
class Heuristic
{
public:
    Heuristic() {};
    Heuristic(ByteContainer* rawData) : m_rawData(rawData) {};
    virtual ~Heuristic() noexcept {}

    /**
     * \brief Heuristic evaluation of possbile block sequences representing files (active, inactive and unknown)
     * \param input Input block sequence
     * \return Vector of block sequences
     */
    virtual std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input) = 0;

private:
    ByteContainer* m_rawData;
};

#endif // HEURISTIC_H
