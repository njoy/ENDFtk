// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/record/Zipper.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk::record;

#include "ENDFtk/record/Zipper/test/expandReferencePack.test.hpp"
#include "ENDFtk/record/Zipper/test/makeIteratorTuple.test.hpp"
#include "ENDFtk/record/Zipper/test/process.test.hpp"
#include "ENDFtk/record/Zipper/test/readLine.test.hpp"
#include "ENDFtk/record/Zipper/test/readPartialLine.test.hpp"
#include "ENDFtk/record/Zipper/test/reserve.test.hpp"
#include "ENDFtk/record/Zipper/test/unzip.test.hpp"
