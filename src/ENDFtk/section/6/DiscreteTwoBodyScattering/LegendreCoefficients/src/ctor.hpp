LegendreCoefficients( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
};

LegendreCoefficients( double energy, std::vector< double >&& coefficients ) :
  LegendreCoefficients( ListRecord( 0.0, energy, 0, 0,
                                    coefficients.size(),
                                    std::move( coefficients ) ) ) {};

template< typename Iterator >
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  LegendreCoefficients( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
