/**
 *  @class
 *  @brief The evaporation spectrum (LF=9)
 *
 *  See ENDF102, section 5.1.1.4 and 5.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT EvaporationSpectrum : protected EffectiveTemperature {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  EvaporationSpectrum() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] thetas          the theta values
   */
  EvaporationSpectrum( std::vector< long >&& boundaries,
                       std::vector< long >&& interpolants,
                       std::vector< double >&& energies,
                       std::vector< double >&& thetas )
    try : EffectiveTemperature( std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( thetas ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing an evaporation spectrum" );
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
  EvaporationSpectrum( Iterator& begin, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
    try : EffectiveTemperature( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading an evaporation spectrum" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 9; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  using EffectiveTemperature::E;
  using EffectiveTemperature::energies;
  using EffectiveTemperature::thetas;
  using EffectiveTemperature::NP;
  using EffectiveTemperature::numberPoints;
  using EffectiveTemperature::NR;
  using EffectiveTemperature::numberInterpolationRegions;
  using EffectiveTemperature::INT;
  using EffectiveTemperature::interpolants;
  using EffectiveTemperature::NBT;
  using EffectiveTemperature::boundaries;
  using EffectiveTemperature::NC;
  using EffectiveTemperature::print;
};
