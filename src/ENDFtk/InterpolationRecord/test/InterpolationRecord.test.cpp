#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/InterpolationRecord.hpp"

// other includes
#include "range/v3/range/operations.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::function< InterpolationRecord() > makeTAB2 = [] () {

  return InterpolationRecord( 1., 2., 3, 4, { 4, 5, 6 }, { 1, 2, 3 } );
};

#include "ENDFtk/InterpolationRecord/test/ctor.test.hpp"
#include "ENDFtk/InterpolationRecord/test/C1.test.hpp"
#include "ENDFtk/InterpolationRecord/test/C2.test.hpp"
#include "ENDFtk/InterpolationRecord/test/L1.test.hpp"
#include "ENDFtk/InterpolationRecord/test/L2.test.hpp"
#include "ENDFtk/InterpolationRecord/test/NR.test.hpp"
#include "ENDFtk/InterpolationRecord/test/NZ.test.hpp"
#include "ENDFtk/InterpolationRecord/test/equality.test.hpp"
#include "ENDFtk/InterpolationRecord/test/print.test.hpp"
#include "ENDFtk/InterpolationRecord/test/rangeInterpolationScheme.test.hpp"
