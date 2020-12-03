//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
MixedElastic() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] coherent      the coherent elastic data
 *  @param[in] incoherent    the incoherent elastic data
 */
MixedElastic( CoherentElastic&& coherent,
              IncoherentElastic&& incoherent ) :
  coherent_( std::move( coherent ) ), incoherent_( std::move( incoherent ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
MixedElastic( CoherentElastic&& coherent,
              Iterator& begin, const Iterator& end,
              long& lineNumber, int MAT, int MF, int MT ) :
  MixedElastic( std::move( coherent ),
                IncoherentElastic( begin, end, lineNumber, MAT, MF, MT ) ) {}

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
MixedElastic( Iterator& begin, const Iterator& end,
              long& lineNumber, int MAT, int MF, int MT )
  try : MixedElastic( CoherentElastic( begin, end, lineNumber, MAT, MF, MT ),
                      begin, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while reading mixed elastic scattering "
               "data" );
    throw;
  }
