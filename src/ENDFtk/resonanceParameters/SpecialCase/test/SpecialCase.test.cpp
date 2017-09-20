#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Testing SpecialCase (LRU=0)" ){
  GIVEN( "valid 'special case' input" ){
    std::string ENDF = 
      " 5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n";
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    resonanceParameters::Base base( 1.0, 2.0, 0, 0, 0, 0 );
    THEN( "a SpecialCase can be constructed" ){
      resonanceParameters::SpecialCase
        sc( base, begin, end, lineNumber, MAT, MF, MT );

      REQUIRE( 1.0 == Approx( sc.EL() ) );
      REQUIRE( 2.0 == sc.EH() );
      REQUIRE( 0.5 == sc.SPI() );
      REQUIRE( 1.276553 == sc.AP() );
      REQUIRE( 0 == sc.LRU() );
      REQUIRE( 0 == sc.LRF() );
      REQUIRE( 0 == sc.NRO() );
      REQUIRE( 0 == sc.NAPS() );
      REQUIRE( 0 == sc.NLS() );
      REQUIRE( 2 == sc.NC() );

      SECTION( "print" ){
        std::string buffer;
        auto output = std::back_inserter( buffer );
        sc.print( output, MAT, MF, MT );

        std::string reference =
          " 1.000000+0 2.000000+0          0          0          0          0 125 2151     \n"
          " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n";

        REQUIRE( buffer == reference );
      }
    }
  }
  
  GIVEN( "invalid ENDF input" ){
    std::string ENDF = 
      " 5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n";
    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    WHEN( "LRU != 0" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 1, 0, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "LRF != 0" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 1, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "NRO != 0" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 1, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "NAPS != 0" ){
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 0, 1 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
  }
  GIVEN( "invalid ENDF input" ){
    WHEN( "L1 != 0" ){
      std::string ENDF = 
        " 5.000000-1 1.276553+0          1          0          0          0 125 2151    4\n";
      auto begin = ENDF.begin();
      auto end = ENDF.end();
      long lineNumber = 0;
      int MAT = 125;
      int MF = 2;
      int MT = 151;

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "L2 != 0" ){
      std::string ENDF = 
        " 5.000000-1 1.276553+0          0          1          0          0 125 2151    4\n";
      auto begin = ENDF.begin();
      auto end = ENDF.end();
      long lineNumber = 0;
      int MAT = 125;
      int MF = 2;
      int MT = 151;

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "N1 != 0" ){
      std::string ENDF = 
        " 5.000000-1 1.276553+0          0          0          1          0 125 2151    4\n";
      auto begin = ENDF.begin();
      auto end = ENDF.end();
      long lineNumber = 0;
      int MAT = 125;
      int MF = 2;
      int MT = 151;

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
    WHEN( "N2 != 0" ){
      std::string ENDF = 
        " 5.000000-1 1.276553+0          0          0          0          1 125 2151    4\n";
      auto begin = ENDF.begin();
      auto end = ENDF.end();
      long lineNumber = 0;
      int MAT = 125;
      int MF = 2;
      int MT = 151;

      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( 
            resonanceParameters::SpecialCase( 
                resonanceParameters::Base(1.0, 2.0, 0, 0, 0, 0 ),
                begin, end, lineNumber, MAT, MF, MT ) );
      }
    }
  }
}

