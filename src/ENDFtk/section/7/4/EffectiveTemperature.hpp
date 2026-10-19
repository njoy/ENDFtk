/**
 *  @class
 *  @brief Effective temperatures for the short collision-time approximation
 *
 *  The EffectiveTemperature class is used to represent the temperature
 *  dependent effective temperature for a scattering atom (both principal or
 *  secondary).
 *
 *  See ENDF102, section 7.5 for more information.
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
   *  @param[in] tmod            the moderator temperature values
   *  @param[in] teff            the effective temperature values
   */
  EffectiveTemperature( std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< double >&& tmod,
                        std::vector< double >&& teff )
    try : TabulationRecord( 0.0, 0.0, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( tmod ),
                            std::move( teff ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing effective temperature "
                 "data" );
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

      Log::info( "Encountered error while reading effective temperature "
                 "data" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the number of temperature values
   */
  long NT() const { return TabulationRecord::NP(); }

  /**
   *  @brief Return the number of temperature values
   */
  long numberTemperatures() const { return this->NT(); }

  /**
   *  @brief Return the moderator temperatures
   */
  auto TMOD() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the moderator temperatures
   */
  auto moderatorTemperatures() const { return this->TMOD(); }

  /**
   *  @brief Return the effective temperatures
   */
  auto TEFF() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the effective temperatures
   */
  auto effectiveTemperatures() const { return this->TEFF(); }

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
