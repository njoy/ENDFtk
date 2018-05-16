NuclearPlusInterference( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& values ) :
  NuclearPlusInterference( ListRecord( 0.0, energy, ltp, 0,
                                    values.size() / 2,
                                    std::move( values ) ) ) {};

NuclearPlusInterference( double energy, long ltp,
                         std::vector< double >&& cosines,
                         std::vector< double >&& probabilities ) :
  NuclearPlusInterference( energy, ltp, generateList( std::move( cosines ), 
                                                      std::move( probabilities ) ) ) {};

template< typename Iterator >
NuclearPlusInterference( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
  NuclearPlusInterference( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
