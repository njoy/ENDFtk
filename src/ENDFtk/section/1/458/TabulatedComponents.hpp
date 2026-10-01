/**
 *  @class
 *  @brief Tabulated evaluation for fission energy release components
 *
 *  The tabulated evaluation for fission energy release components uses
 *  a thermal point evaluation for the energy release components, with in
 *  addition some tabulated components.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedComponents {

public:

  /* type aliases */

  using OptionalEnergyReleaseComponent = std::optional< EnergyReleaseComponent >;

private:

  /* fields */

  int nfc_;
  ThermalPointComponents values_;
  std::array< OptionalEnergyReleaseComponent, 9 > components_;

  /* auxiliary functions */

  static std::array< std::optional< EnergyReleaseComponent >, 9 >
  generateTables( std::vector< EnergyReleaseComponent >&& tables ) {

    std::array< std::optional< EnergyReleaseComponent >, 9 > records = {

      std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
      std::nullopt, std::nullopt, std::nullopt, std::nullopt
    };

    if ( tables.size() == 0 ) {

      Log::error( "No tabulated energy release components are given" );
      throw std::exception();
    }

    for ( auto&& component : tables ) {

      if ( ( component.IFC() > 0 ) && ( component.IFC() < 10 ) ) {

        if ( ! records[ component.IFC() - 1 ] ) {

          records[ component.IFC() - 1 ] = std::move( component );
        }
        else {

          Log::error( "Encountered duplicate IFC value" );
          Log::info( "IFC value: {}", component.IFC() );
          throw std::exception();
        }
      }
      else {

        Log::error( "Encountered illegal IFC value" );
        Log::info( "IFC must be between 1 and 9" );
        Log::info( "IFC value: {}", component.IFC() );
        throw std::exception();
      }
    }

    return records;
  }

  template< typename Iterator >
  static std::array< std::optional< EnergyReleaseComponent >, 9 >
  readTables( Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT,
              int NFC ) {

    std::array< std::optional< EnergyReleaseComponent >, 9 > records = {

        std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
        std::nullopt, std::nullopt, std::nullopt, std::nullopt
      };

    if ( NFC < 0 ) {

      Log::error( "The number of tabulated energy release components NFC value "
                  "cannot be negative" );
      Log::info( "NFC value: {}", NFC );
      throw std::exception();
    }

    while( NFC-- ) {

      EnergyReleaseComponent component(begin, end, lineNumber, MAT, MF, MT);
      if ( ( component.IFC() > 0 ) && ( component.IFC() < 10 ) ) {

        if ( ! records[ component.IFC() - 1 ] ) {

          records[ component.IFC() - 1 ] = std::move( component );
        }
        else {

          Log::error( "Encountered duplicate IFC value" );
          Log::info( "IFC value: {}", component.IFC() );
          Log::info( "Line number: {}", lineNumber - component.NC() );
          throw std::exception();
        }
      }
      else {

        Log::error( "Encountered illegal IFC value" );
        Log::info( "IFC must be between 1 and 9" );
        Log::info( "IFC value: {}", component.IFC() );
        Log::info( "Line number: {}", lineNumber - component.NC() );
        throw std::exception();
      }
    }

    return records;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  TabulatedComponents(
      int nfc,
      ThermalPointComponents&& thermal,
      std::array< std::optional< EnergyReleaseComponent >, 9 >&& components ) :
    nfc_( nfc ), values_( std::move( thermal ) ),
    components_( std::move( components ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedComponents() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] thermal    the thermal point evaluation of the energy release
   *  @param[in] tables     the tabulated components
   */
  TabulatedComponents( ThermalPointComponents&& thermal,
                       std::vector< EnergyReleaseComponent >&& tables )
    try : TabulatedComponents( tables.size(), std::move( thermal ),
                               generateTables( std::move( tables ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated evaluation" );
      throw;
    }

  private:

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  TabulatedComponents( int NFC,
                       ThermalPointComponents&& thermal,
                       Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT ) :
    TabulatedComponents(
        NFC, std::move( thermal ),
        readTables( begin, end, lineNumber, MAT, MF, MT, NFC ) ) {}

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
  TabulatedComponents( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       int NFC )
    try : TabulatedComponents(
              NFC,
              ThermalPointComponents( begin, end, lineNumber, MAT, MF, MT ),
              begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated evaluation" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr int LFC() { return 1; }

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
  int NFC() const { return this->nfc_; }

  /**
   *  @brief Return the number of tabulated energy release components
   */
  int numberTabulatedComponents() const { return this->NFC(); }

  /**
   *  @brief Return the thermal point values
   */
  const ThermalPointComponents& thermalPointValues() const {

    return this->values_;
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const std::array< OptionalEnergyReleaseComponent, 9 >& tabulated() const {

    return this->components_;
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const OptionalEnergyReleaseComponent& tabulatedEFR() const {

    return std::get< 0 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the fission fragments
   */
  const OptionalEnergyReleaseComponent& tabulatedFissionFragments() const {

    return this->tabulatedEFR();
  }

  /**
   *  @brief Return the tabulated kinetic energy of the prompt fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedENP() const {

    return std::get< 1 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the prompt fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedPromptNeutrons() const {

    return this->tabulatedENP();
  }

  /**
   *  @brief Return the tabulated kinetic energy of the delayed fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedEND() const {

    return std::get< 2 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated kinetic energy of the delayed fission neutrons
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedNeutrons() const {

    return this->tabulatedEND();
  }

  /**
   *  @brief Return the tabulated energy release by prompt gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedEGP() const {

    return std::get< 3 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by prompt gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedPromptGammas() const {

    return this->tabulatedEGP();
  }

  /**
   *  @brief Return the tabulated energy release by delayed gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedEGD() const {

    return std::get< 4 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by delayed gammas
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedGammas() const {

    return this->tabulatedEGD();
  }

  /**
   *  @brief Return the tabulated energy release by delayed betas
   */
  const OptionalEnergyReleaseComponent& tabulatedEB() const {

    return std::get< 5 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by delayed betas
   */
  const OptionalEnergyReleaseComponent& tabulatedDelayedBetas() const {

    return this->tabulatedEB();
  }

  /**
   *  @brief Return the tabulated energy release by neutrinos
   */
  const OptionalEnergyReleaseComponent& tabulatedENU() const {

    return std::get< 6 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated energy release by neutrinos
   */
  const OptionalEnergyReleaseComponent& tabulatedNeutrinos() const {

    return this->tabulatedENU();
  }

  /**
   *  @brief Return the tabulated total energy release minus the neutrino energy
   */
  const OptionalEnergyReleaseComponent& tabulatedER() const {

    return std::get< 7 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated total energy release minus the neutrino energy
   */
  const OptionalEnergyReleaseComponent& tabulatedTotalMinusNeutrinos() const {

    return this->tabulatedER();
  }

  /**
   *  @brief Return the tabulated total energy release
   */
  const OptionalEnergyReleaseComponent& tabulatedET() const {

    return std::get< 8 >( this->components_ );
  }

  /**
   *  @brief Return the tabulated total energy release
   */
  const OptionalEnergyReleaseComponent& tabulatedTotal() const {

    return this->tabulatedET();
  }

  /**
   *  @brief Return the number of lines in this MF1/MT458 section
   */
  long NC() const {

    long NC = this->values_.NC();
    for ( auto& entry : this->components_ ) {
      if ( entry ) { NC += entry->NC(); }
    }
    return NC;
  }

  /**
   *  @brief Print the MF1/MT458 section (includes SEND record)
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    this->values_.print( it, MAT, MF, MT );
    for ( auto& entry : this->components_ ) {
      if ( entry ) { entry->print( it, MAT, MF, MT ); }
    }
  }
};
