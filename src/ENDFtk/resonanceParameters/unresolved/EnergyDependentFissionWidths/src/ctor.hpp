private:
/**
 *  @brief Private intermediate constructor
 */
EnergyDependentFissionWidths( ListRecord&& energies,
                              std::vector< LValue >&& lvalues ) :
  UnresolvedBaseWithoutSpin( std::move( lvalues ) ),
  energies_( std::move( energies ) ) {

    verifySize( this->energies_.NPL(), this->lValues() );
  }

public:
/**
 *  @brief Constructor
 *
 *  @param[in] spi        the target spin value
 *  @param[in] ap         the scattering radius
 *  @param[in] lssf       the self-shielding only flag
 *  @param[in] energies   the energy values for which fission widths are given
 *  @param[in] lvalues    the l values and the resonance parameters
 */
EnergyDependentFissionWidths( double spi, double ap, bool lssf,
                              std::vector< double >&& energies,
                              std::vector< LValue >&& lvalues )
  try : EnergyDependentFissionWidths( ListRecord( spi, ap, lssf,
                                                  0, lvalues.size(),
                                                  std::move( energies ) ),
                                      std::move( lvalues ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing unresolved resonance "
               "parameters in the Single Level Breit-Wigner representation "
               "with energy dependent fission widths" );
    throw;
  }

private:
/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
EnergyDependentFissionWidths(
      ListRecord&& list,
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ) :
  EnergyDependentFissionWidths( std::move( list ),
                                readSequence< LValue >(
                                    it, end, lineNumber,
                                    MAT, MF, MT, list.N2() ) ) {}

public:
/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 *  @param[in] MF           the expected MF number
 *  @param[in] MT           the expected MT number
 */
template< typename Iterator >
EnergyDependentFissionWidths(
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT )
  try : EnergyDependentFissionWidths(
            ListRecord( it, end, lineNumber, MAT, MF, MT ),
            it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing unresolved resonance "
               "parameters in the Single Level Breit-Wigner representation "
               "with energy dependent fission widths" );
    throw;
  }
