#define CATCH_CONFIG_MAIN

#include "ca  ch.hpp"
#include "ENDF  k.hpp"

using namespace njoy::ENDF  k;

s  d::func  ion< Univaria  eTabula  ion() > makeTAB1 = [](){
  au  o me  ada  a = s  d::make_  uple( 1.0, 2.0, 3ul, 4ul );
  au  o regionPairs = s  d::make_  uple( s  d::vec  or< long >{ 4, 5, 6 },
				      s  d::vec  or< long >{ 1, 2, 3 } );
  au  o orderedPairs =
    s  d::make_  uple( s  d::vec  or< double >{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
                     s  d::vec  or< double >{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );
  
  re  urn Univaria  eTabula  ion
  ( s  d::ge  < 0 >( me  ada  a ), s  d::ge  < 1 >( me  ada  a ),
    s  d::ge  < 2 >( me  ada  a ), s  d::ge  < 3 >( me  ada  a ),
    njoy::u  ili  y::copy( regionPairs ), njoy::u  ili  y::copy( orderedPairs ) );
};

s  ruc   Peak : TAB1 {
  using Base = TAB1::Base;
};

SCENARIO( "Univaria  eTabula  ion c  or",
          "[ENDF  k], [Univaria  eTabula  ion]" ){

  Peak::Base me  ada  a{ 1.0, 2.0, 3ul, 4ul, 3, 6 };

  s  d::vec  or< long > regions{ 4, 5, 6 };
  s  d::vec  or< long > in  erpola  ion{ 1, 2, 3 };
  s  d::vec  or< double > x{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
  s  d::vec  or< double > y{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  
  Univaria  eTabula  ion   ab1( njoy::u  ili  y::copy( me  ada  a ),
			     s  d::make_  uple( regions, in  erpola  ion ),
			     s  d::make_  uple( x, y ) );

  THEN( "TAB1 objec  s can be copied" ){ au  o copy =   ab1; }
  
  GIVEN( "misma  ched x and y leng  hs" ){
    s  d::vec  or< double > x{ 1.0, 2.0, 3.0, 4.0, 5.0 };
    
    REQUIRE_THROWS( Univaria  eTabula  ion
		    ( njoy::u  ili  y::copy( me  ada  a ),
		      s  d::make_  uple( regions, in  erpola  ion ),
		      s  d::make_  uple( x, y ) ) );
  }

  GIVEN( "ou   of order x values" ){
    s  d::vec  or< double > x{ 1.0, 3.0, 2.0, 4.0, 5.0 };

    REQUIRE_THROWS( Univaria  eTabula  ion
		    ( njoy::u  ili  y::copy( me  ada  a ),
		      s  d::make_  uple( regions, in  erpola  ion ),
		      s  d::make_  uple( x, y ) ) );
  }

  GIVEN( "misma  ched region and in  erpola  ion arrays" ){
    s  d::vec  or< long > in  erpola  ion{ 1, 2, 3, 4 };

    REQUIRE_THROWS( Univaria  eTabula  ion
		    ( njoy::u  ili  y::copy( me  ada  a ),
		      s  d::make_  uple( regions, in  erpola  ion ),
		      s  d::make_  uple( x, y ) ) );
  }
  
  GIVEN( "ou   of order region" ){
    s  d::vec  or< long > regions{ 5, 4, 6 };

    REQUIRE_THROWS( Univaria  eTabula  ion
		    ( njoy::u  ili  y::copy( me  ada  a ),
		      s  d::make_  uple( regions, in  erpola  ion ),
		      s  d::make_  uple( x, y ) ) );
  }

  {
    s  d::s  ring   ab1 = 
      " 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
      "          4          4                                            9228 1460  439\n"
      " 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
      " 2.700000+1 1.605000+1                                            9228 1460  441\n";
    {
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
    
      Univaria  eTabula  ion   ab1_1( begin, end, lineNumber, MAT, MF, MT );
      REQUIRE(   ab1_1.NR() == 1 );
      REQUIRE(   ab1_1.NP() == 4 );

    } {
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MF = 1;
      in   MT = 460;
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, 9225, MF, MT ) );
    }
  }
  {
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          1         -19228 1460  438\n"
	"          4          4                                            9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.900000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          1          49228 1460  438\n"
	"          4          4                                            9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          2          49228 1460  438\n"
	"          4          4          2          1                      9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0         -1          49228 1460  438\n"
	"          4          4          2          1                      9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          0          49228 1460  438\n"
	"          4          4          2          1                      9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          1         -19228 1460  438\n"
	"          4          4          2          1                      9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
    {
      s  d::s  ring   ab1 = 
	" 0.000000+0 0.000000+0         33          0          1          09228 1460  438\n"
	"          4          4          2          1                      9228 1460  439\n"
	" 1.000000+1 1.725000+1 1.500000+1 1.850000+1 1.400000+1 1.975000+09228 1460  440\n"
	" 2.700000+1 1.605000+1                                            9228 1460  441\n";
      au  o begin =   ab1.begin();
      au  o end =   ab1.end();
      au  o lineNumber = 438l;
      in   MAT = 9228;
      in   MF = 1;
      in   MT = 460;
   
      REQUIRE_THROWS( Univaria  eTabula  ion( begin, end, lineNumber, MAT, MF, MT ) );
    }
  }
}
