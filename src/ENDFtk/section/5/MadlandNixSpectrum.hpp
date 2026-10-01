/**
 *  @class
 *  @brief The Madland Nix fission neutron spectrum (LF=12)
 *
 *  See ENDF102, section 5.1.1.6 and 5.2.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT MadlandNixSpectrum : protected TabulationRecord {

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  MadlandNixSpectrum() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] efl             the light fission fragment kinetic energy
   *  @param[in] efh             the heavy fission fragment kinetic energy
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] temperatures    the maximum temperature values
   */
  MadlandNixSpectrum( double efl, double efh,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& energies,
                      std::vector< double >&& temperatures )
    try : TabulationRecord( efl, efh, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( temperatures ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing a Madland-Nix spectrum" );
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
  MadlandNixSpectrum( Iterator& begin, const Iterator& end,
                      long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading a Madland-Nix spectrum" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 12; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double EFL() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the average kinetic energy of the average light
   *         fission fragment (the EFL value)
   */
  double lightFragmentEnergy() const { return this->EFL(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double EFH() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the average kinetic energy of the average heavy
   *         fission fragment (the EFL value)
   */
  double heavyFragmentEnergy() const { return this->EFH(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the maximum temperature parameter values
   */
  auto TM() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the maximum temperature parameter values
   */
  auto maximumTemperatureValues() const { return this->TM(); }

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
