#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../parallel.h"

/**
 * \brief Intersection operator
 * \author Janine Schneider
 * \date January, 2019
 */
class Intersection : public Parallel
{
public:
    Intersection(Heuristic* h1, Heuristic* h2) : Parallel(h1, h2) {}

    /**
     * \brief Intersection operator function \n
     *        Returns all storage objects that two heuristics return in their result
     * \param res1 The results of h1
     * \param res2 The results of h2
     * \return Returns the intersection of two heuristic results as block sequences
     */
    std::vector<std::vector<uint64_t>> setOperator(std::vector<std::vector<uint64_t>> res1,
                                                   std::vector<std::vector<uint64_t>> res2);
};

#endif // INTERSECTION_H
