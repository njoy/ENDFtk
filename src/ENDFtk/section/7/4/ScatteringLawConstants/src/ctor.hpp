private:
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
