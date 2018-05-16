Tabulated( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
};

Tabulated( double energy, int ltp, std::vector< double >&& values ) :
  Tabulated( ListRecord( 0.0, energy, ltp, 0,
                         values.size() / 2,
                         std::move( values ) ) ) {};

Tabulated( double energy, int ltp,
           std::vector< double >&& cosines,
           std::vector< double >&& probabilities ) :
  Tabulated( energy, ltp, generateList( std::move( cosines ), 
             std::move( probabilities ) ) ) {};

template< typename Iterator >
Tabulated( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
  Tabulated( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
