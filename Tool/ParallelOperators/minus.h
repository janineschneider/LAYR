#ifndef MINUS_H
#define MINUS_H

#include "../parallel.h"

/**
 * \brief Minus operator
 * \author Janine Schneider
 * \date January, 2019
 */
class Minus : public Parallel
{
public:
    Minus(Heuristic* h1, Heuristic* h2) : Parallel(h1, h2) {}

    /**
     * \brief Minus operator function \n
     *        Removes the results of the h2 from the results of h1
     * \param res1 The results of h1
     * \param res2 The results of h2
     * \return Returns a set of heuristic evaluation results, without the results of another heuristic evaluation, as block sequences
     */
    std::vector<std::vector<uint64_t>> setOperator(std::vector<std::vector<uint64_t>> res1,
                                                   std::vector<std::vector<uint64_t>> res2);
};

#endif // MINUS_H
