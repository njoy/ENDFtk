KalbachMann( ListRecord&& list ) :
  Base( std::move( list ) ) {

  verifyNA( this->NA() );
};

KalbachMann( double energy, long nd, long na, long nep,
             std::vector< double >&& list ) :
  KalbachMann( ListRecord( 0.0, energy, nd, na, nep,
                           std::move( list ) ) ) {};

KalbachMann( double energy, long nd, long nep,
             std::vector< std::array< double, 3 > >&& data ) :
  KalbachMann( energy, nd, 1, nep,
               generateList( std::move( data ) ) ) {};

KalbachMann( double energy, long nd, long nep,
             std::vector< std::array< double, 4 > >&& data ) :
  KalbachMann( energy, nd, 2, nep,
               generateList( std::move( data ) ) ) {};

template< typename Iterator >
KalbachMann( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  KalbachMann( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
