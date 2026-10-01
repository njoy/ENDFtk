/**
 *  @class
 *  @brief Continuous decay spectrum
 *
 *  The ContinuousSpectrum class is used to represent the continuous part of the
 *  spectrum for a specific decay radiation type (designated by STYP) of
 *  MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT ContinuousSpectrum : protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] chain           the ENDF decay chain
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] spectrum        the spectral values
   */
  ContinuousSpectrum( double chain,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& energies,
                      std::vector< double >&& spectrum )
    try : TabulationRecord( chain, 0.0, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( spectrum ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing continuum spectrum data" );
      throw;
    }

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
  ContinuousSpectrum( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading continuum spectrum data" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double RTYP() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the decay chain responsible for this spectrum
   */
  double decayChain() const { return this->RTYP(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the spectral values
   */
  auto RP() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the spectral values
   */
  auto spectralValues() const { return this->RP(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
