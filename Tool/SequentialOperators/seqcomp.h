#ifndef SEQCOMP_H
#define SEQCOMP_H

#include "../heuristic.h"
#include <functional>

//Typedef of choose function
using Choose = std::function<std::vector<std::vector<uint64_t>> (std::vector<std::vector<uint64_t>>)>;

/**
 * \brief Sequential composition operator
 * \author Janine Schneider
 * \date January, 2019
 */
class SeqComp : public Heuristic
{
public:
    SeqComp(Heuristic* h1, Heuristic* h2, Choose chooser);
    ~SeqComp();

    /**
     * \brief Sequential composition operator function \n
     *        Evaluates a h1, chooses a subset of the result, evaluates h2 on all storage objects from the chosen subset, combines the results
     * \param input Input block sequence
     * \return Vector of block sequences
     */
    std::vector<std::vector<uint64_t>> evaluate(std::vector<uint64_t> input);

private:
    Heuristic* m_h1;
    Heuristic* m_h2;
    Choose m_chooser;
};

#endif // SEQCOMP_H
