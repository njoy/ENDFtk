private:
EnergyDistribution( TabulationRecord&& table ) :
  TabulationRecord( std::move( table ) ) {};

public:
EnergyDistribution( double cosine,
                    std::vector< long >&& boundaries,
                    std::vector< long >&& interpolants,
                    std::vector< double >&& energies,
                    std::vector< double >&& probabilities )
  try : EnergyDistribution(
          TabulationRecord( 0.0, cosine, 0, 0, std::move( boundaries ),
                            std::move( interpolants ), std::move( energies ),
                            std::move( probabilities ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing energy distribution data "
               "(LAW=7)" );
    throw;
  }

template< typename Iterator >
EnergyDistribution( Iterator& it, const Iterator& end,
                                  long& lineNumber,
                                  int MAT, int MF, int MT )
  try : EnergyDistribution( TabulationRecord( it, end, lineNumber,
                                              MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading energy distribution data "
               "(LAW=7)" );
    throw;
  }
