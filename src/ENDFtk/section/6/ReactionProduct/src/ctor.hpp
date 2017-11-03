template< typename Iterator >
ReactionProduct ( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MT )
  try : multiplicity_( begin, end, lineNumber, MAT, 6, MT ),
        law_( readDistribution( begin, end, lineNumber, MAT, MT, 
                                this->multiplicity_.LAW() ) ) {}
  catch (std::exception& e) {
    Log::info( "Something went wrong while reading reaction product data" );
    Log::info( "See line {}", lineNumber );
    throw std::exception();
  }

