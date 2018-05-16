NuclearAmplitudeExpansion( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& list ) :
  NuclearAmplitudeExpansion( ListRecord( 0.0, energy, 1, 0,
                                         nl, std::move( list ) ) ) {};

NuclearAmplitudeExpansion( double energy, int nl,
                           std::vector< double >&& b,
                           std::vector< double >&& a_real,
                           std::vector< double >&& a_imag ) :
  NuclearAmplitudeExpansion( energy, nl,
                             generateList( nl, std::move ( b ),
                                               std::move ( a_real ),
                                               std::move ( a_imag ) ) ) {};

template< typename Iterator >
NuclearAmplitudeExpansion( Iterator& it, const Iterator& end, long& lineNumber,
                           int MAT, int MF, int MT ) :
  NuclearAmplitudeExpansion( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
