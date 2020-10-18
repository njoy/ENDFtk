private:
TabulatedDistribution( int lang, ListRecord&& list ) :
  Base( std::move( list ) ), lang_( lang ) {

  checkLANG( this->LANG() );
};

public:
TabulatedDistribution( int lang, double energy, long nd, long na, long nep,
                       std::vector< double >&& energies,
                       std::vector< double >&& totalEmissionProbabilities,
                       std::vector< std::vector< double > >&& cosines,
                       std::vector< std::vector< double > >&& probabilities )
  try : TabulatedDistribution(
            lang,
            ListRecord( 0.0, energy, nd, na, nep,
                        generateList( na,
                                      std::move( energies ),
                                      std::move( totalEmissionProbabilities ),
                                      std::move( cosines ),
                                      std::move( probabilities ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing tabulated distribution "
               "data (LAW=1 LANG={})", lang );
    throw;
  }

template< typename Iterator >
TabulatedDistribution( int lang, Iterator& it, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
  try : TabulatedDistribution( lang, ListRecord( it, end, lineNumber,
                                                 MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading tabulated distribution data "
               "(LAW=1 LANG={})", lang );
    throw;
  }
