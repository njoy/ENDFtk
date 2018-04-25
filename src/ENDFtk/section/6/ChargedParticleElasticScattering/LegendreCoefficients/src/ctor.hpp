LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
  LegendreCoefficients( ListRecord( 0.0, energy, 2, 0,
                                    coefficients.size() - 1,
                                    std::move( coefficients ) ) ) {};

template< typename Iterator >
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  LegendreCoefficients( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
