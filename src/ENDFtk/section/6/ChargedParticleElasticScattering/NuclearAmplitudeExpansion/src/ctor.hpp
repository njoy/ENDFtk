NuclearAmplitudeExpansion( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& a ) :
  NuclearAmplitudeExpansion( ListRecord( 0.0, energy, 1, 0,
                                         nl, std::move( a ) ) ) {};

template< typename Iterator >
NuclearAmplitudeExpansion( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT ) :
  NuclearAmplitudeExpansion( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
