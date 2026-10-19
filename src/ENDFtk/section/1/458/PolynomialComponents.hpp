/**
 *  @class
 *  @brief Polynomial evaluation for fission energy release components
 *
 *  The polynomial evaluation for fission energy release components uses
 *  a polynomial expansion to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT PolynomialComponents {

  /* workaround for the removal of range-v3 */

  // using transform with more ranges operations in the transform causes issues
  // on the Python side. we just rearrange the underlying array at construction
  // time to solve it. As a result, this no longer inherits from ListRecord.
  int nply_;
  std::vector< double > values_;

  /* auxiliary functions */

  static std::vector< double >
  generateList( std::vector< std::array< double, 2 > >&& efr,
                std::vector< std::array< double, 2 > >&& enp,
                std::vector< std::array< double, 2 > >&& end,
                std::vector< std::array< double, 2 > >&& egp,
                std::vector< std::array< double, 2 > >&& egd,
                std::vector< std::array< double, 2 > >&& eb,
                std::vector< std::array< double, 2 > >&& enu,
                std::vector< std::array< double, 2 > >&& er,
                std::vector< std::array< double, 2 > >&& et ) {

    std::vector< double > list;

    unsigned int size = efr.size();
    if ( ( enp.size() != size ) || ( end.size() != size ) ||
         ( egp.size() != size ) || ( egd.size() != size ) ||
         ( eb.size() != size ) || ( enu.size() != size ) ||
         ( er.size() != size ) || ( et.size() != size ) ) {

      Log::info( "The polynomial order each energy release component is not "
                 "consistent" );
      Log::info( "NPLY value: {}", size - 1 );
      Log::info( "efr.size(): {}", efr.size() );
      Log::info( "enp.size(): {}", enp.size() );
      Log::info( "end.size(): {}", end.size() );
      Log::info( "egp.size(): {}", egp.size() );
      Log::info( "egd.size(): {}", egd.size() );
      Log::info( "eb.size(): {}", eb.size() );
      Log::info( "enu.size(): {}", enu.size() );
      Log::info( "er.size(): {}", er.size() );
      Log::info( "et.size(): {}", et.size() );
      throw std::exception();
    }

    auto fill = [] ( const auto& component, auto& values ) {

      for ( auto&& entry : component ) {

        values.push_back( entry[0] );
        values.push_back( entry[1] );
      }
    };

    fill( efr, list );
    fill( enp, list );
    fill( end, list );
    fill( egp, list );
    fill( egd, list );
    fill( eb, list );
    fill( enu, list );
    fill( er, list );
    fill( et, list );

    return list;
  }

  static std::vector< double >
  generateList( const ListRecord& list ) {

    std::vector< double > values;

    if ( list.L2() < 0 ) {

      Log::error( "Encountered illegal NPLY value" );
      Log::info( "NPL must be larger than or equal to zero" );
      Log::info( "NPL value: {}", list.L2() );
      throw std::exception();
    }

    std::size_t npl = list.NPL();
    std::size_t nply = list.L2();
    if ( npl != ( nply + 1 ) * 18 ) {

      Log::error( "Encountered illegal NPL value" );
      Log::info( "NPL must be equal to {}", ( nply + 1 ) * 18 );
      Log::info( "NPL value: {}", npl );
      throw std::exception();
    }

    for ( std::size_t j = 0; j < 9; ++j ) {

      for ( std::size_t i = 0; i < nply + 1; ++i ) {

        values.push_back( list.list()[ i * 18 + j * 2 ] );
        values.push_back( list.list()[ i * 18 + j * 2 + 1 ] );
      }
    }
    return values;
  }

public:

  /* constructor */

  /**
   *  @brief Private constructor
   */
  PolynomialComponents( int nply, std::vector< double >&& list ) :
    nply_( nply ), values_( std::move( list ) ) {}

  /**
   *  @brief Private constructor
   */
  PolynomialComponents( std::vector< double >&& list ) :
    PolynomialComponents( list.size() / 18 - 1, std::move( list ) ) {}

  /**
   *  @brief Private constructor
   */
  PolynomialComponents( ListRecord&& list ) :
    PolynomialComponents( generateList( list ) ) {}

  public:

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  PolynomialComponents() = default;
  #endif

  /**
   *  @brief Constructor
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
  PolynomialComponents( std::vector< std::array< double, 2 > >&& efr,
                        std::vector< std::array< double, 2 > >&& enp,
                        std::vector< std::array< double, 2 > >&& end,
                        std::vector< std::array< double, 2 > >&& egp,
                        std::vector< std::array< double, 2 > >&& egd,
                        std::vector< std::array< double, 2 > >&& eb,
                        std::vector< std::array< double, 2 > >&& enu,
                        std::vector< std::array< double, 2 > >&& er,
                        std::vector< std::array< double, 2 > >&& et )
    try : PolynomialComponents(
            generateList( std::move( efr ), std::move( enp ), std::move( end ),
                          std::move( egp ), std::move( egd ), std::move( eb ),
                          std::move( enu ), std::move( er ), std::move( et ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a polynomial evaluation" );
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
  PolynomialComponents( Iterator& begin, const Iterator& end,
                        long& lineNumber, int MAT, int MF, int MT )
    try : PolynomialComponents(
              ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a polynomial evaluation" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the tabulated energy release flag
   */
  static constexpr int LFC() { return 0; }

  /**
   *  @brief Return the tabulated energy release flag
   */
  bool tabulatedEnergyRelease() const { return this->LFC(); }

  /**
   *  @brief Return the polynomial expansion order
   */
  int NPLY() const { return this->nply_; }

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
    return this->values_ | std23::views::chunk( 2 )
                         | std23::views::chunk( this->order() + 1 );
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
  auto EB() const { return this->E()[5]; }

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
  auto ER() const { return this->E()[7]; }

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

  /**
   *  @brief Return the number of lines in this MF1/MT458 component
   */
  long NC() const {

    return 1 + ( this->order() + 1 ) * 3;
  }

  /**
   *  @brief Print the MF1/MT458 component
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

    std::vector< double > values;
    values.reserve( 18 * ( this->order() + 1 ) );
    for ( std::size_t i = 0; i < static_cast< std::size_t >( this->order() ) + 1; ++i ) {

      for ( std::size_t j = 0; j < 9; ++j ) {

        values.push_back( this->energyRelease()[j][i][0] );
        values.push_back( this->energyRelease()[j][i][1] );
      }
    }

    ListRecord( 0., 0., 0, this->order(), ( this->order() + 1 ) * 9,
                std::move( values ) ).print( it, MAT, MF, MT );
  }
};
