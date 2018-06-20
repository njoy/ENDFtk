ScatteringLawConstants( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verifySize( this->NI(), this->NS() );
};

ScatteringLawConstants( int lln, int ns,
                        std::vector< double >&& coefficients ) :
  ScatteringLawConstants( ListRecord( 0.0, 0.0, lln, 0, ns,
                                      std::move( coefficients ) ) ) {};

ScatteringLawConstants( int lln, int ns, double epsilon, double emax,
                        double crossSection, double weightRatio, 
                        unsigned int numberAtoms ) :
  ScatteringLawConstants( ListRecord( 0.0, 0.0, lln, 0, ns,
                                      { crossSection, epsilon, weightRatio,
                                        emax, 0.0, double( numberAtoms ) } ) ) {};

ScatteringLawConstants( int lln, int ns, double epsilon, double emax,
                        std::vector< double >&& crossSections,
                        std::vector< double >&& weightRatios,
                        std::vector< unsigned int >&& numberAtoms,
                        std::vector< unsigned int >&& functionTypes ) :
  ScatteringLawConstants(
    ListRecord( 0.0, 0.0, lln, 0, ns,
                std::move( generateList( ns, epsilon, emax,
                                         std::move( crossSections ),
                                         std::move( weightRatios ),
                                         std::move( numberAtoms ),
                                         std::move( functionTypes ) ) ) ) ) {};

template< typename Iterator >
ScatteringLawConstants( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT ) :
  ScatteringLawConstants( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
