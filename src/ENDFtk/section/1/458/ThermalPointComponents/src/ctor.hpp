/**
 *  @brief Private constructor
 */
ThermalPointComponents( ListRecord&& list ) :
  ListRecord( std::move( list ) ) {

    verify( ListRecord::NPL() );
  }

public:

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
