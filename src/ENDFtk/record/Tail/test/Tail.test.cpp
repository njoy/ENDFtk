#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/record/Tail.hpp"
#include "ENDFtk/record/TailVerifying.hpp"

// other includes
#include <functional>

// convenience typedefs
using namespace njoy::ENDFtk::record;

constexpr int mat = 125;
constexpr int mf = 4;
constexpr int mt = 2;

#include "ENDFtk/record/Tail/test/Tail.test.hpp"
#include "ENDFtk/record/Tail/test/TailVerifiers.test.hpp"
