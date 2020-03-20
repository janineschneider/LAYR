#include "or.h"
#include <exception>

Or::Or(Heuristic* h1, Heuristic* h2) : m_h1(h1), m_h2(h2)
{
    //TODO Check for empty pointer
}

Or::~Or()
{
    if (m_h1 != nullptr) {
        delete m_h1;
    }

    if (m_h2 != nullptr) {
        delete m_h2;
    }
}

std::vector<std::vector<uint64_t>> Or::evaluate(std::vector<uint64_t> input)
{
    std::vector<std::vector<uint64_t>> res;

    try {
        res = m_h1->evaluate(input);
    } catch (std::exception& e) {
        res = m_h2->evaluate(input);
    }

    return res;
}

