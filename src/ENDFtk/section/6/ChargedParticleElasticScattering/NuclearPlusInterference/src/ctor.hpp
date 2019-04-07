NuclearPlusInterference( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& values )
  try : NuclearPlusInterference( ListRecord( 0.0, energy, ltp, 0,
                                             values.size() / 2,
                                             std::move( values ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear plus interference "
               "data (LAW=5 LTP=3)" );
    throw;
  }

NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& cosines,
                         std::vector< double >&& probabilities )
  try : NuclearPlusInterference(
          ListRecord( 0.0, energy, ltp, 0, cosines.size(),
                      generateList( std::move( cosines ), 
                                    std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear plus interference "
               "data (LAW=5 LTP=3)" );
    throw;
  }

template< typename Iterator >
NuclearPlusInterference( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
  try : NuclearPlusInterference( ListRecord( it, end, lineNumber,
                                             MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading nuclear plus interference "
               "data (LAW=5 LTP=3)" );
    throw;
  }
