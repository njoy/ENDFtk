NuclearPlusInterference( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifyLTP( this->L1() );
    verifySize( this->NW(), this->NL() );
};

NuclearPlusInterference( double energy, int ltp,
                         std::vector< double >&& values ) :
  NuclearPlusInterference( ListRecord( 0.0, energy, ltp, 0,
                                    values.size() / 2,
                                    std::move( values ) ) ) {};

template< typename Iterator >
NuclearPlusInterference( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT ) :
  NuclearPlusInterference( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
