#ifndef ADDRESULTS_H
#define ADDRESULTS_H

#include "../../heuristic.h"

/**
 * \brief AddResults evaluation heuristic
 * \author Janine Schneider
 * \date March, 2019
 */
class AddResults : public Heuristic
{
public:
    /**
     * \brief Evaluation heuristic that adds some results \n
     *        Returns slightly changed Ext3 heuristic results
     * \remark For testing purposes only
     * \param input Input block sequence (not in use)
     * \return Vector of block sequences
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);
};

#endif // ADDRESULTS_H
