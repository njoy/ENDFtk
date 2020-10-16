TabulatedDistribution( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
}

TabulatedDistribution( double energy, int lang,
                       std::vector< double >&& cosines,
                       std::vector< double >&& probabilities )
  try : TabulatedDistribution( ListRecord( 0.0, energy, lang, 0,
                                           cosines.size(),
                                           generateList( std::move( cosines ),
                                                         std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG={})", lang );
    throw;
  }

template< typename Iterator >
TabulatedDistribution( Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT )
  try : TabulatedDistribution( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG=12/14)" );
    throw;
  }
