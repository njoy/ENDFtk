/**
 *  @brief Constructor
 *
 *  @param[in] energy   the photon energy
 *  @param[in] level    the energy of the level from which the photon
 *                      originates
 */
IsotropicDiscretePhoton( double energy, double level ) :
    // no need for a try ... catch: nothing can go wrong here
    eg_( energy ), es_( level ) {}

private:
/**
 *  @brief Private intermediate constructor
 */
IsotropicDiscretePhoton( ControlRecord&& cont ) :
  IsotropicDiscretePhoton( cont.C1(), cont.C2() ) {}

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
IsotropicDiscretePhoton( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
  try : IsotropicDiscretePhoton(
            ControlRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing the isotropic angular "
               "distribution for a discrete photon" );
    throw;
  }
