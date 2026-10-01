/**
 *  @class
 *  @brief Scattering law constants
 *
 *  The ScatteringLawConstants class stores the data from the first ListRecord
 *  of an MF7/MT4 section of the ENDF file. It stores a single flag to indicate
 *  the representation type of the S(a,b) (either as S or ln(S) values) and the
 *  B array containing the  constants required for the scattering law data of
 *  the principal scatterer and the analytic representations for the
 *  non-principal scattering atoms (if any).
 *
 *  See ENDF102, section 7.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT ScatteringLawConstants : protected ListRecord {

  /* auxiliary functions */

  static std::vector< double >
  generateList( unsigned int ns,
                double epsilon, double emax,
                std::vector< double >&& crossSections,
                std::vector< double >&& weightRatios,
                std::vector< unsigned int >&& numberAtoms,
                std::vector< unsigned int >&& functionTypes ) {

    if ( crossSections.size() != ns + 1 ) {

      Log::info( "The number of cross section values must be equal to NS + 1" );
      Log::info( "NS value: {}", ns );
      Log::info( "crossSections.size(): {}", crossSections.size() );
      throw std::exception();
    }
    if ( weightRatios.size() != ns + 1 ) {

      Log::info( "The number of weight ratio values must be equal to NS + 1" );
      Log::info( "NS value: {}", ns );
      Log::info( "weightRatios.size(): {}", weightRatios.size() );
      throw std::exception();
    }
    if ( numberAtoms.size() != ns + 1 ) {

      Log::info( "The number of atoms for each type must be equal to NS + 1" );
      Log::info( "NS value: {}", ns );
      Log::info( "numberAtoms.size(): {}", numberAtoms.size() );
      throw std::exception();
    }
    if ( functionTypes.size() != ns ) {

      Log::info( "The number of function types must be equal to NS" );
      Log::info( "NS value: {}", ns );
      Log::info( "functionTypes.size(): {}", functionTypes.size() );
      throw std::exception();
    }

    std::vector< double > list( 6 * ( ns + 1 ) );
    list[0] = crossSections[0];
    list[1] = epsilon;
    list[2] = weightRatios[0];
    list[3] = emax;
    list[4] = 0.0;
    list[5] = numberAtoms[0];
    for ( unsigned int i = 1; i <= ns; ++i ) {

      list[6*i+0] = functionTypes[i-1];
      list[6*i+1] = crossSections[i];
      list[6*i+2] = weightRatios[i];
      list[6*i+3] = 0.0;
      list[6*i+4] = 0.0;
      list[6*i+5] = numberAtoms[i];
    }
    return list;
  }

  static void
  verifySize( int NI, int NS ) {

    if ( NS > 3 ) {

      Log::error( "Encountered illegal NS value" );
      Log::info( "NS must be smaller than or equal to 3" );
      Log::info( "NS value: {}", NS );
      throw std::exception();
    }

    if ( NI != 6 * ( NS + 1 ) ) {

      Log::error( "Encountered illegal NI and NS values" );
      Log::info( "NI must be equal to 6*(NS + 1)" );
      Log::info( "NI value: {}", NI );
      Log::info( "NS value: {}", NS );
      throw std::exception();
    }
  }

  static void
  checkLLN( int value ) {

    if ( ( value != 0 ) and ( value != 1 ) ) {

      Log::error( "Encountered illegal LLN value" );
      Log::info( "LLN must be equal to 0 or 1" );
      Log::info( "LLN value: {}", value );
      throw std::exception();
    }
  }

  /* workaround for the removal of range-v3 */

  // using transform with more ranges operations in the transform causes issues
  // on the Python side. we just generate the underlying array at construction
  // time to solve it.
  std::vector< double > sigma_;

  void generateSigma() {

    this->sigma_.clear();
    this->sigma_.reserve( this->NS() + 1 );
    this->sigma_.push_back( ListRecord::list()[0] );

    auto ns = this->NS();
    for ( unsigned int i = 0; i < ns; ++i ) {

      this->sigma_.push_back( ListRecord::list()[ 7 + i * 6 ] );
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   *
   *  The number of values in the list are checked against the number of
   *  non-principal scatterers ns (the N2 value on the ListRecord).
   */
  ScatteringLawConstants( ListRecord&& list ) :
    ListRecord( std::move( list ) ) {

    verifySize( this->NI(), this->NS() );
    checkLLN( this->LLN() );
    this->generateSigma();
  };

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ScatteringLawConstants() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  The size of list array is checked against ns for consistency.
   *
   *  @param[in] lln    the LLN flag - store S or ln(S)
   *  @param[in] ns     the number non-principal scatterers
   *  @param[in] list   the B array values as given in the ENDF manual (6*ns + 1
   *                    values)
   */
  ScatteringLawConstants( int lln, int ns,
                          std::vector< double >&& list )
    try : ScatteringLawConstants( ListRecord( 0.0, 0.0, lln, 0, ns,
                                              std::move( list ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing thermal scattering "
                 "constants" );
      throw;
    }

  /**
   *  @brief Constructor (only for principal scatterer)
   *
   *  This constructor can be used for a ScatteringLawConstants that only has a
   *  principal scatterer and no secondary scatterers (ns = 0)
   *
   *  @param[in] lln       the LLN flag - store S or ln(S)
   *  @param[in] epsilon   B(2) - the E/kT ratio
   *  @param[in] emax      B(4) - the maximum energy
   *  @param[in] xs        B(1) - the total free atom cross section
   *  @param[in] awr       B(3) - the atomic weight ratio in neutron mass units
   *  @param[in] natoms    B(6) - the number of principal scatterer atoms
   */
  ScatteringLawConstants( int lln, double epsilon, double emax,
                          double xs, double awr,
                          unsigned int natoms ) :
    // this can never fail, try-catch would be unreachable
    ScatteringLawConstants(
          ListRecord( 0.0, 0.0, lln, 0, 0,
                      { xs, epsilon, awr, emax, 0.0, double( natoms ) } ) ) {}

  /**
   *  @brief Constructor
   *
   *  This constructor can be used for constructing a ScatteringLawConstants using
   *  individual arrays for the data type needed for each scatterer, wether or not
   *  there are secondary scatterers. The size of each array is checked for
   *  consistency.
   *
   *  @param[in] lln       the LLN flag - store S or ln(S)
   *  @param[in] ns        the number non-principal scatterers
   *  @param[in] epsilon   B(2) - the E/kT ratio
   *  @param[in] emax      B(4) - the maximum energy
   *  @param[in] xs        the total free atom cross section for each scatterer
   *                       (ns + 1 values)
   *  @param[in] awr       the atomic weight ratios for each scatterer
   *                       (ns + 1 values)
   *  @param[in] natoms    the number of atoms for each scatterer (ns + 1 values)
   *  @param[in] types     the function type for each secondary scatterer
   *                       (ns values)
   */
  ScatteringLawConstants( int lln, int ns, double epsilon, double emax,
                          std::vector< double >&& xs,
                          std::vector< double >&& awr,
                          std::vector< unsigned int >&& natoms,
                          std::vector< unsigned int >&& types )
    try : ScatteringLawConstants(
            ListRecord( 0.0, 0.0, lln, 0, ns,
                        generateList( ns, epsilon, emax,
                                      std::move( xs ),
                                      std::move( awr ),
                                      std::move( natoms ),
                                      std::move( types ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing thermal scattering "
                 "constants" );
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
  ScatteringLawConstants( Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT )
    try : ScatteringLawConstants( ListRecord( it, end, lineNumber,
                                              MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading thermal scattering "
                 "constants" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  int LLN() const { return ListRecord::L1(); }

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  int sabStorageType() const { return this->LLN(); }

  /**
   *  @brief Return the size of the B array, equal to 6*(NS+1)
   */
  long NI() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the size of the B array, equal to 6*(NS+1)
   */
  long numberConstants() const { return this->NI(); }

  /**
   *  @brief Return the number of non-principal scattering atom types
   */
  long NS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of non-principal scattering atom types
   */
  long numberNonPrincipalScatterers() const { return this->NS(); }

  /**
   *  @brief Return the value of epsilon = E/kT, stored in B(2)
   */
  double epsilon() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the upper energy limit of the thermal scattering law,
             stored in B(4)
   */
  double EMAX() const { return ListRecord::list()[3]; }

  /**
   *  @brief Return the upper energy limit of the thermal scattering law,
             stored in B(4)
   */
  double upperEnergyLimit() const { return this->EMAX(); }

  /**
   *  @brief Return the total free atom cross section for each scattering atom
   *         type, stored in B(1), B(8) and B(14)
   */
  auto MSIGMA() const {

    using namespace njoy::tools;
    return std20::views::all( this->sigma_ );
  }

  /**
   *  @brief Return the total free atom cross section for each scattering atom
   *         type, stored in B(1), B(8) and B(14)
   */
  auto totalFreeCrossSections() const { return this->MSIGMA(); }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto AWR() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 2 )
             | std23::views::stride( 6 ); }

  /**
   *  @brief Return the ratio of the atomic weight to the neutron mass for each
   *         scattering atom type, stored in B(3), B(9) and B(15)
   */
  auto atomicWeightRatios() const {

    return this->AWR();
  }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto M() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 5 )
             | std23::views::stride( 6 )
             | std20::views::transform( [] ( auto&& value ) -> int
                                           { return std::round( value ); } );
  }

  /**
   *  @brief Return the number of atoms for each scattering atom type present in
   *         the molecule or unit cell, stored in B(6), B(12) and B(18)
   */
  auto numberAtoms() const {

    return this->M();
  }

  /**
   *  @brief Return the analytical function type for each non-principal
   *         scattering atom type, stored in B(7), B(13) and B(19)
   */
  auto analyticalFunctionTypes() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 6 )
             | std23::views::stride( 6 )
             | std20::views::transform( [] ( auto&& value ) -> int
                                           { return std::round( value ); } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
