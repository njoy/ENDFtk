BetaValue( TabulationRecord&& alphas,
           std::vector< ListRecord >&& temperatures ) :
  alphas_( std::move( alphas ) ), temperatures_( std::move( temperatures ) ) {}

BetaValue( double beta,
           std::vector< long >&& boundaries,
           std::vector< long >&& interpolants,
           std::vector< double >&& alphas,
           std::vector< long >&& li,
           std::vector< double >&& temperatures,
           std::vector< std::vector< double > >&& s ) :
  BetaValue( TabulationRecord( temperatures[0], beta,
                               temperatures.size() - 1, 0,
                               std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( alphas ),
                               std::move( s[0] ) ),
             generateTemperatures( beta,
                                   std::move( temperatures ),
                                   std::move( li ),
                                   std::move( s ) ) ) {}

private:
template< typename Iterator >
BetaValue( TabulationRecord&& alphas,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT ) :
  BetaValue( std::move( alphas ),
             readTemperatures( begin, end, lineNumber,
                               MAT, MF, MT, alphas.L1() ) ) {}

public:
template< typename Iterator >
BetaValue( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT ) :
  BetaValue( TabulationRecord( begin, end, lineNumber, MAT, MF, MT ),
             begin, end, lineNumber, MAT, MF, MT ) {}

