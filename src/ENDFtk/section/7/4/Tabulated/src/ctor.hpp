Tabulated( std::vector< long >&& boundaries,
           std::vector< long >&& interpolants,
           std::vector< BetaValue >&& betas ) :
  data_( InterpolationRecord( 0.0, 0.0, 0, 0,
                              std::move( boundaries ),
                              std::move( interpolants ) ),
                              std::move( betas ) ) {};

template< typename Iterator >
Tabulated( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT ) :
  data_( begin, end, lineNumber, MAT, MF, MT  ) {}

