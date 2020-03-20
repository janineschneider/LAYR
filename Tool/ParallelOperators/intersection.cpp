#include "intersection.h"
#include <algorithm>

std::vector<std::vector<uint64_t>> Intersection::setOperator(std::vector<std::vector<uint64_t>> res1,
                                                             std::vector<std::vector<uint64_t>> res2)
{
    std::vector<std::vector<uint64_t>> res;
    std::set_intersection(res1.begin(), res1.end(), res2.begin(), res2.end(), std::back_inserter(res));

    return res;
}
