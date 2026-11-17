/**
 *  @class
 *  @brief Thermal point evaluation for fission energy release components
 *
 *  The thermal point evaluation for fission energy release components uses
 *  analytical functions to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT ThermalPointComponents : protected ListRecord {

  /* auxiliary functions */

  static void verify( int NPL ) {

    if ( NPL != 18 ) {

      Log::error( "Encountered illegal NPL value" );
      Log::info( "NPL must be equal to 18" );
      Log::info( "NPL value: {}", NPL );
      throw std::exception();
    }
  }

public:

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ThermalPointComponents( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

      verify( ListRecord::NPL() );
    }

  public:

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ThermalPointComponents() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  Each of the arguments consist of the energy release value and the associated
   *  uncertainty.
   *
   *  @param[in] efr    the kinetic energy of the fission fragments
   *  @param[in] enp    the kinetic energy of the prompt fission neutrons
   *  @param[in] end    the kinetic energy of the delayed fission neutrons
   *  @param[in] egp    the energy release by prompt gammas
   *  @param[in] egd    the energy release by delayed gammas
   *  @param[in] eb     the energy release by delayed betas
   *  @param[in] enu    the energy release by neutrinos
   *  @param[in] er     the total energy release minus neutrinos
   *  @param[in] et     the total energy release
   */
  ThermalPointComponents( std::array< double, 2 >&& efr,
                          std::array< double, 2 >&& enp,
                          std::array< double, 2 >&& end,
                          std::array< double, 2 >&& egp,
                          std::array< double, 2 >&& egd,
                          std::array< double, 2 >&& eb,
                          std::array< double, 2 >&& enu,
                          std::array< double, 2 >&& er,
                          std::array< double, 2 >&& et )
    try : ThermalPointComponents(
            ListRecord( 0.0, 0.0, 0, 0, 9,
                        { efr[0], efr[1], enp[0], enp[1], end[0], end[1],
                          egp[0], egp[1], egd[0], egd[1], eb[0], eb[1],
                          enu[0], enu[1], er[0], er[1], et[0], et[1] } ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a thermal point "
                 "evaluation" );
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
  ThermalPointComponents( Iterator& begin, const Iterator& end,
                          long& lineNumber, int MAT, int MF, int MT )
    try : ThermalPointComponents(
              ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a thermal point "
                 "evaluation" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr bool LFC() { return false; }

  /**
   *  @brief Return the tabulated energy release flag
   */
  bool tabulatedEnergyRelease() const { return this->LFC(); }

  /**
   *  @brief Return the polynomial expansion order
   */
  static constexpr int NPLY() { return 0; }

  /**
   *  @brief Return the polynomial expansion order
   */
  int order() const { return this->NPLY(); }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  static constexpr int NFC() { return 0; }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  int numberTabulatedComponents() const { return this->NFC(); }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto E() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::chunk( 2 );
  }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto energyRelease() const { return this->E(); }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto EFR() const { return this->E()[0]; }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto fissionFragments() const { return this->EFR(); }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto ENP() const { return this->E()[1]; }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto promptNeutrons() const { return this->ENP(); }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto END() const { return this->E()[2]; }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto delayedNeutrons() const { return this->END(); }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto EGP() const { return this->E()[3]; }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto promptGammas() const { return this->EGP(); }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto EGD() const { return this->E()[4]; }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto delayedGammas() const { return this->EGD(); }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto EB() const  { return this->E()[5]; }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto delayedBetas() const  { return this->EB(); }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto ENU() const { return this->E()[6]; }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto neutrinos() const { return this->ENU(); }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto ER() const  { return this->E()[7]; }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto totalMinusNeutrinos() const  { return this->ER(); }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto ET() const  { return this->E()[8]; }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto total() const  { return this->ET(); }

  using ListRecord::NC;
  using ListRecord::print;
};
