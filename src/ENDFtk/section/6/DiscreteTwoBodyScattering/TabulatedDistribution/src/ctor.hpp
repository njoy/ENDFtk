Tabulated( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
}

Tabulated( double energy, int lang, std::vector< double >&& values )
  try : Tabulated( ListRecord( 0.0, energy, lang, 0,
                               values.size() / 2,
                               std::move( values ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG={})", lang );
    throw;
  }

Tabulated( double energy, int lang,
           std::vector< double >&& cosines,
           std::vector< double >&& probabilities )
  try : Tabulated( ListRecord( 0.0, energy, lang, 0,
                               cosines.size(),
                               generateList( std::move( cosines ), 
                                             std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG={})", lang );
    throw;
  }

template< typename Iterator >
Tabulated( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
  try : Tabulated( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=2 LANG=12/14)" );
    throw;
  }
