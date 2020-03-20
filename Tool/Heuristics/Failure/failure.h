#ifndef FAILURE_H
#define FAILURE_H

#include "../../heuristic.h"

/**
 * \brief Failure evaluation heuristic
 * \author Janine Schneider
 * \date March, 2019
 */
class Failure : public Heuristic
{
public:
    /**
     * \brief Evaluation heuristic that throws a runtime error
     * \remark For testing purposes only
     * \param input Input block sequence (not in use)
     * \return Nothing
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);
};

#endif // FAILURE_H
