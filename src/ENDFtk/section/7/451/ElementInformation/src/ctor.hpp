private:

/**
 *  @brief Private constructor
 */
ElementInformation( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( ListRecord::NPL(), this->NI() );
};

public:

/**
 *  @brief Constructor
 *
 *  @param[in] atoms          the number of atoms in the molecule or unit cell
 *  @param[in] identifiers    the isotope identifiers (ZA identifier)
 *  @param[in] states         the isomeric state for each isotope
 *  @param[in] abundances     the isotope abundances
 *  @param[in] weights        the atomic weight ratios
 *  @param[in] xs             the free atom scattering cross sections
 */
ElementInformation( unsigned int atoms,
                    std::vector< unsigned int >&& identifiers,
                    std::vector< unsigned int >&& states,
                    std::vector< double >&& abundances,
                    std::vector< double >&& weights,
                    std::vector< double >&& xs )
  try : ElementInformation(
            ListRecord( 0.0, 0.0,
                        atoms, 0, identifiers.size(),
                        generateList( std::move( identifiers ),
                                      std::move( states ),
                                      std::move( abundances ),
                                      std::move( weights ),
                                      std::move( xs ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing thermal scattering "
               "element information" );
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
ElementInformation( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT )
  try : ElementInformation( ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing fission yields" );
    throw;
  }
