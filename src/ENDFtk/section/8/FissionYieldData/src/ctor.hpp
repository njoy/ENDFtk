private:

/**
 *  @brief Private constructor
 */
FissionYieldData( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

  verifySize( ListRecord::NPL(), this->NFP() );
};

public:

/**
 *  @brief Constructor
 *
 *  @param[in] identifiers     the fission product identifiers (ZA identifier)
 *  @param[in] states          the isomeric state for each fission product
 *  @param[in] yields          the fission yield values and uncertainties
 *  @param[in] energy          the incident neutron energy (equal to zero for
 *                             energy independent yields)
 *  @param[in] interpolation   the interpolation type (equal to zero for
 *                             energy independent yields)
 */
FissionYieldData( std::vector< unsigned int >&& identifiers,
                  std::vector< unsigned int >&& states,
                  std::vector< std::array< double, 2 > >&& yields,
                  double energy = 0.0, int interpolation = 0 )
  try : FissionYieldData(
            ListRecord( energy, 0.0,
                        interpolation, 0, identifiers.size(),
                        generateList( std::move( identifiers ),
                                      std::move( states ),
                                      std::move( yields ) ) ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing fission yields" );
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
FissionYieldData( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT )
  try : FissionYieldData( ListRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing fission yields" );
    throw;
  }
