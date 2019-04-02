private:
KalbachMann( ListRecord&& list ) :
  Base( std::move( list ) ) {

  verifyNA( this->NA() );
};

public:
KalbachMann( double energy, long nd, long na, long nep,
             std::vector< double >&& list )
  try : KalbachMann( ListRecord( 0.0, energy, nd, na, nep,
                                 std::move( list ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Kalbach-Mann distribution "
               "data (LAW=1 LANG=2)" );
    throw;
  }

KalbachMann( double energy, long nd, long nep,
             std::vector< std::array< double, 3 > >&& data )
  try : KalbachMann( ListRecord( 0.0, energy, nd, 1, nep,
                                 generateList( std::move( data ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Kalbach-Mann distribution "
               "data (LAW=1 LANG=2)" );
    throw;
  }

KalbachMann( double energy, long nd, long nep,
             std::vector< std::array< double, 4 > >&& data )
  try : KalbachMann( ListRecord( 0.0, energy, nd, 2, nep,
                                 generateList( std::move( data ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing Kalbach-Mann distribution "
               "data (LAW=1 LANG=2)" );
    throw;
  }

template< typename Iterator >
KalbachMann( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
  try : KalbachMann( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Kalbach-Mann distribution data "
               "(LAW=1 LANG=2)" );
    throw;
  }
