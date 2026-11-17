/**
 *  @class
 *  @brief The effective temperature of an evaporation spectrum
 *
 *  The effective temperature is used to describe the secondary
 *  energy distribution for evaporation spectra (LF=5,7,9).
 *
 *  See ENDF102, section 5 for more information.
 */
class ENDFTK_PYTHON_EXPORT EffectiveTemperature : protected TabulationRecord {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  EffectiveTemperature() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] thetas          the theta values
   */
  EffectiveTemperature( std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< double >&& energies,
                        std::vector< double >&& thetas )
    try : TabulationRecord( 0.0, 0.0, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( thetas ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing an effective "
                 "temperature function" );
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
  EffectiveTemperature( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing an effective "
                 "temperature function" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the effective temperature values
   */
  auto thetas() const { return TabulationRecord::y(); }

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
