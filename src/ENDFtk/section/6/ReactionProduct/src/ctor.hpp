ReactionProduct( Multiplicity&& multiplicity,
                 Distribution&& distribution ) :
  multiplicity_( multiplicity ), law_( distribution ) {}

template< typename Iterator >
ReactionProduct( Iterator& begin, const Iterator& end,
                 long& lineNumber, int MAT, int MF, int MT )
  try : multiplicity_( begin, end, lineNumber, MAT, MF, MT ),
        law_( readDistribution( begin, end, lineNumber, MAT, MT, 
                                this->multiplicity_.LAW() ) ) {}
  catch (std::exception& e) {
    Log::info( "Something went wrong while reading reaction product data" );
    Log::info( "See line {}", lineNumber );
    throw std::exception();
  }

