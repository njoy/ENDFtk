#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/TabulationRecord.hpp"

// other includes
#include "range/v3/algorithm/equal.hpp"
#include "range/v3/range/operations.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::function< TabulationRecord() > makeTAB1 = [] () {

  return TabulationRecord ( 1., 2., 3, 4,
                            { 4, 5, 6 }, { 1, 2, 3 },
                            { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
                            { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );
};

#include "ENDFtk/TabulationRecord/test/ctor.test.hpp"
#include "ENDFtk/TabulationRecord/test/C1.test.hpp"
#include "ENDFtk/TabulationRecord/test/C2.test.hpp"
#include "ENDFtk/TabulationRecord/test/L1.test.hpp"
#include "ENDFtk/TabulationRecord/test/L2.test.hpp"
#include "ENDFtk/TabulationRecord/test/NR.test.hpp"
#include "ENDFtk/TabulationRecord/test/NP.test.hpp"
#include "ENDFtk/TabulationRecord/test/equality.test.hpp"
#include "ENDFtk/TabulationRecord/test/pairs.test.hpp"
#include "ENDFtk/TabulationRecord/test/print.test.hpp"
#include "ENDFtk/TabulationRecord/test/regions.test.hpp"
#include "ENDFtk/TabulationRecord/test/x.test.hpp"
#include "ENDFtk/TabulationRecord/test/y.test.hpp"
#include "ENDFtk/TabulationRecord/test/rangeInterpolationScheme.test.hpp"
