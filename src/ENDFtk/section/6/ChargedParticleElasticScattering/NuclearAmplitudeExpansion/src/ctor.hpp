NuclearAmplitudeExpansion( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
}

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& list )
  try : NuclearAmplitudeExpansion( ListRecord( 0.0, energy, 1, 0,
                                               nl, std::move( list ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
  }

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& b,
                           std::vector< double >&& a_real,
                           std::vector< double >&& a_imag )
  try : NuclearAmplitudeExpansion(
          ListRecord( 0.0, energy, 1, 0, nl, 
                      generateList( nl, std::move ( b ),
                                    std::move ( a_real ),
                                    std::move ( a_imag ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
  }

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& b,
                           std::vector< std::complex< double > >&& a )
  try : NuclearAmplitudeExpansion( 
          ListRecord( 0.0, energy, 1, 0, nl, 
                      generateList( nl, std::move ( b ),
                                    std::move ( a ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing nuclear amplitude "
               "expansion data (LAW=5 LTP=1)" );
    throw;
  }

template< typename Iterator >
NuclearAmplitudeExpansion( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT )
  try : NuclearAmplitudeExpansion( ListRecord( it, end, lineNumber,
                                               MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading nuclear amplitude expansion "
               "data (LAW=5 LTP=1)" );
    throw;
  }
