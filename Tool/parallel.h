#ifndef PARALLEL_H
#define PARALLEL_H

#include "heuristic.h"

/**
 * \brief Parallel operator base class
 * \inherits Heuristic
 * \author Janine Schneider
 * \date January, 2019
 */
class Parallel : public Heuristic
{
public:
    Parallel();
    Parallel(Heuristic* h1, Heuristic* h2) : m_h1(h1), m_h2(h2){};
    virtual ~Parallel() noexcept {}

    /**
     * \brief Set operator function (union, intersection, minus)
     * \param res1 The results of h1
     * \param res2 The results of h2
     * \return Vector of block sequences
     */
    virtual std::vector<std::vector<uint64_t>> setOperator(std::vector<std::vector<uint64_t>> res1,
                                                           std::vector<std::vector<uint64_t>> res2) = 0;

    /**
     * @brief Heuristic combination operator
     * @param input Input block sequence
     * @return Vector of block sequences
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input) {
        return setOperator(m_h1->evaluate(input), m_h2->evaluate(input));};

private:
    Heuristic* m_h1;
    Heuristic* m_h2;
};

#endif // PARALLEL_H
