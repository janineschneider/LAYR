#ifndef UNION_H
#define UNION_H

#include "../parallel.h"

/**
 * \brief Union operator
 * \author Janine Schneider
 * \date January, 2019
 */
class Union : public Parallel
{
public:
    Union(Heuristic* h1, Heuristic* h2) : Parallel(h1, h2) {}

    /**
     * \brief Union operator function \n
     *        Combines the results of two heuristics by joining them together
     * \param res1 The results of h1
     * \param res2 The results of h2
     * \return Returns the union of two heuristic results as block sequences
     */
    std::vector<std::vector<uint64_t>> setOperator(std::vector<std::vector<uint64_t>> res1,
                                                   std::vector<std::vector<uint64_t>> res2);
};

#endif // UNION_H
