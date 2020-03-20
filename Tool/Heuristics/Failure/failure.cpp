#include "failure.h"
#include <exception>
#include <string>

std::vector<std::vector<uint64_t> > Failure::evaluate(std::vector<uint64_t> input)
{
    throw std::runtime_error(std::string("Runtime error (Thrown by class Failure)"));
}
