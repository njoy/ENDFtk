/**
 *  @brief Private constructor
 */
PolynomialComponents( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verify( ListRecord::NPL(), this->NPLY() );
  }

/**
 *  @brief Private constructor
 */
PolynomialComponents( std::vector< double >&& list ) :
  ListRecord( 0.0, 0.0, 0, list.size() / 18 - 1, list.size() / 2,
              std::move( list ) ) {}

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
