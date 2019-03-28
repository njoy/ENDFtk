LegendreCoefficients( ListRecord&& list ) : Base( std::move( list ) ) {}

LegendreCoefficients( double energy, long nd, long na, long nep,
                      std::vector< double >&& list ) :
  Base( energy, nd, na, nep, std::move( list ) ) {}

template< typename Iterator >
LegendreCoefficients( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  Base( it, end, lineNumber, MAT, MF, MT ) {}

LegendreCoefficients( double energy, long nd, long na, long nep,
                      std::vector< double > energies,
                      std::vector< std::vector< double > >&& coefficients ) :
 Base( energy, nd, na, nep,
       generateList( na, std::move( energies ), std::move( coefficients ) ) ) {}
