#include "seqcomp.h"
#include <algorithm>

SeqComp::SeqComp(Heuristic* h1, Heuristic* h2, Choose chooser) : m_h1(h1), m_h2(h2), m_chooser(chooser)
{
    //TODO Check for empty pointer
}

SeqComp::~SeqComp()
{
    if (m_h1 != nullptr) {
        delete m_h1;
    }

    if (m_h2 != nullptr) {
        delete m_h2;
    }
}

std::vector<std::vector<uint64_t>> SeqComp::evaluate(std::vector<uint64_t> input)
{
    std::vector<std::vector<uint64_t>> h1_res = m_h1->evaluate(input);
    std::vector<std::vector<uint64_t>> choices = m_chooser(h1_res);
    std::vector<std::vector<uint64_t>> final_res;

    for (auto it = choices.begin(); it != choices.end(); ++it) {
        std::vector<std::vector<uint64_t>> h2_res = m_h2->evaluate(*it);
        final_res.insert(final_res.end(), h2_res.begin(), h2_res.end());
    }
    std::sort(final_res.begin(), final_res.end());
    std::unique(final_res.begin(), final_res.end());

    return final_res;
}
