#ifndef OR_H
#define OR_H

#include "../heuristic.h"

/**
 * \brief Or operator
 * \author Janine Schneider
 * \date January, 2019
 */
class Or : public Heuristic
{
public:
    Or(Heuristic* h1, Heuristic* h2);
    ~Or();

    /**
     * \brief Or operator function \n
     *        Runs h2 if h1 fails
     * \param input Input block sequence
     * \return Vector of block sequences
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);

private:
    Heuristic* m_h1;
    Heuristic* m_h2;
};

#endif // OR_H
