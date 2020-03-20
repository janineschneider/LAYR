#include "input.h"
#include <iostream>

std::vector<std::vector<uint64_t>> Input::evaluate(std::vector<uint64_t> input)
{
    std::vector<std::vector<uint64_t>> result;

    for (auto it = input.begin(); it != input.end(); ++it) {
        std::cout << *it << " ";
        result.push_back(input);
    }

    std::cout << std::endl;

    return result;
}
