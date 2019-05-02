LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
  // this can never fail, try-catch would be unreachable
  LegendreCoefficients( ListRecord( 0.0, energy, 2, 0,
                                    coefficients.size() - 1,
                                    std::move( coefficients ) ) ) {}

template< typename Iterator >
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT )
  try : LegendreCoefficients( ListRecord( it, end, lineNumber,
                                          MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading Legendre coefficients "
               "(LAW=5 LTP=2)" );
    throw;
  }
