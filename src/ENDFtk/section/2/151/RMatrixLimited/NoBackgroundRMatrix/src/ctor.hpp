//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
NoBackgroundRMatrix() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] index    the channel index
 */
NoBackgroundRMatrix( int index ) : BaseBackgroundRMatrix( index ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
NoBackgroundRMatrix( ControlRecord&& record ) :
  NoBackgroundRMatrix( record.L1() ) {

    verifyLBK( record.L2() );
  }

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
NoBackgroundRMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
  try : NoBackgroundRMatrix( ControlRecord( it, end, lineNumber,
                             MAT, MF, MT ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing channel background" );
    throw;
  }
