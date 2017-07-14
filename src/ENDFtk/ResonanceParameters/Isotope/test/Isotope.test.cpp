#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk.hpp"

using namespace njoy::ENDFtk;

SCENARIO( "Isotope" ){
  WHEN( "Negative NER" ){
    std::string ENDF = 
      " 1.001000+3 9.991673-1          0          0         -1          0 125 2151    1\n";

    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    REQUIRE_THROWS(
      ResonanceParameters::Isotope( begin, end, lineNumber, MAT, MF, MT )
    );
  }
  
  WHEN( "LRU=0" ){
    std::string ENDF = 
      " 1.001000+3 1.000000+0          0          0          1          0 125 2151    2\n"
      " 1.000000-5 1.000000+5          0          0          0          0 125 2151    3\n"
      " 5.000000-1 1.276553+0          0          0          0          0 125 2151    4\n";

    auto begin = ENDF.begin();
    auto end = ENDF.end();
    long lineNumber = 0;
    
    int MAT = 125;
    int MF = 2;
    int MT = 151;

    THEN( "a SpecialCase can be constructed" ){
      ResonanceParameters::Isotope iso( begin, end, lineNumber, MAT, MF, MT );

      REQUIRE( 1 == iso.energyRanges().size() );
      REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::SpecialCase >
                       ( iso.energyRanges().back() ) );
      
      const auto& sc = std::experimental::get< ResonanceParameters::SpecialCase >
        ( iso.energyRanges().back() );
      
      REQUIRE( 1E-5 == Approx( sc.EL() ) );
      REQUIRE( 1E5 == sc.EH() );
      REQUIRE( 0.5 == sc.SPI() );
      REQUIRE( 1.276553 == sc.AP() );
    }
    
    WHEN( "LRU=1" ){
      WHEN( "there is only one SLBW range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
          " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
          " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
          " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n";

        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        ResonanceParameters::Isotope iso( begin, end, lineNumber, MAT, MF, MT );

        REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::Resolved::SLBW >
                         ( iso.energyRanges().back() ) );
        REQUIRE( 1 == iso.energyRanges().size() );
      }
      
      WHEN( "there is only one MLBW range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          2          0          06153 2151    3\n"
          " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
          " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
          " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n";

        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        ResonanceParameters::Isotope iso( begin, end, lineNumber, MAT, MF, MT );

        REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::Resolved::MLBW >
                         ( iso.energyRanges().back() ) );
        REQUIRE( 1 == iso.energyRanges().size() );
      }

      WHEN( "there is only one Reich-Moore range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          3          0          06153 2151    3\n"
          " 6.000000+0 6.380900-1          0          0          1          16153 2151    4\n"
          " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
          " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n";

        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        ResonanceParameters::Isotope iso( begin, end, lineNumber, MAT, MF, MT );

        REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::Resolved::ReichMoore >
                         ( iso.energyRanges().back() ) );
        REQUIRE( 1 == iso.energyRanges().size() );
      }

      WHEN( "there is only one Adler-Adler range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          4          0          06153 2151    3\n";

        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        REQUIRE_THROWS(
          ResonanceParameters::Isotope( begin, end, lineNumber, MAT, MF, MT )
        );
      }

      WHEN( "there is one Rmatrix-Limited range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          7          0          06153 2151    3\n";

        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        REQUIRE_THROWS(
          ResonanceParameters::Isotope( begin, end, lineNumber, MAT, MF, MT )
        );
      }
      
      WHEN( "there is more than one range in the Isotope" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          2          06153 2151    2\n"
          " 1.000000-5 1.000000+0          1          1          0          06153 2151    3\n"
          " 6.000000+0 6.380900-1          0          0          1          06153 2151    4\n"
          " 1.466470+2 0.000000+0          0          0          6          16153 2151    5\n"
          " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151    6\n"
          " 1.000000-5 1.000000+0          1          3          0          06153 2151    7\n"
          " 6.000000+0 6.380900-1          0          0          1          16153 2151    8\n"
          " 1.466470+2 0.000000+0          0          0          6          16153 2151    9\n"
          " 1.690000-1 6.000000+0 8.018800-2 5.880000-4 7.960000-2 0.000000+06153 2151   10\n";
        
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;

        ResonanceParameters::Isotope iso( begin, end, lineNumber, MAT, MF, MT );
        REQUIRE( 2 == iso.energyRanges().size() );

        REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::Resolved::SLBW >
                         ( iso.energyRanges().front() ) );
        REQUIRE_NOTHROW( std::experimental::get< ResonanceParameters::Resolved::ReichMoore >
                         ( iso.energyRanges().back() ) );
      }
    }
  }

  GIVEN( "not implemented input" ){
    WHEN( "LRU=2" ){
      THEN( "an exception is thrown" ){
        std::string ENDF =
          " 6.114800E4 1.000000+0          0          0          1          06153 2151    2\n"
          " 1.000000-5 1.000000+0          2          1          0          06153 2151    3\n";
        auto begin = ENDF.begin();
        auto end = ENDF.end();
        long lineNumber = 0;
        int MAT = 6153;
        int MF = 2;
        int MT = 151;
        REQUIRE_THROWS(
          ResonanceParameters::Isotope( begin, end, lineNumber, MAT, MF, MT )
        );
      }
    }
  }
}
