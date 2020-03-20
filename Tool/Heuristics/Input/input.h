#ifndef INPUT_H
#define INPUT_H

#include "../../heuristic.h"

/**
 * \brief Input evaluation heuristic
 * \author Janine Schneider
 * \date March, 2019
 */
class Input : public Heuristic
{
public:
    /**
     * \brief Evaluation heuristic that adds some results \n
     *        Prints the passed input block sequence to cout
     * \remark For testing purposes only
     * \param input Input block sequence
     * \return Nothing
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);
};

#endif // INPUT_H
