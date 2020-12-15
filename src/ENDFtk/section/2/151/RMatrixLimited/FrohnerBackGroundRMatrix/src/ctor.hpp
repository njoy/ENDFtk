private:

/**
 *  @brief Private intermediate constructor
 */
FrohnerBackGroundRMatrix( int index,
                        std::array< double, 5 >&& array ) :
  BaseBackGroundRMatrix( index ), data_( std::move( array ) ) {}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
FrohnerBackGroundRMatrix() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param[in] index           the channel index
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] real            the real values of the tabulated rmatrix
 *  @param[in] imaginary       the real values of the tabulated rmatrix
 */
FrohnerBackGroundRMatrix( int index,
                        double ed, double eu, double r0, double s0, double ga ) :
  FrohnerBackGroundRMatrix( index, { ed, eu, r0, s0, ga } ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
FrohnerBackGroundRMatrix( int index,
                        ListRecord&& list ) :
  FrohnerBackGroundRMatrix( index, extract( std::move( list ) ) ) {}

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
FrohnerBackGroundRMatrix( ControlRecord&& record,
                        Iterator& it, const Iterator& end, long& lineNumber,
                        int MAT, int MF, int MT ) :
  FrohnerBackGroundRMatrix(
      record.L1(),
      ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {

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
FrohnerBackGroundRMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT )
  try : FrohnerBackGroundRMatrix( ControlRecord( it, end, lineNumber,
                                               MAT, MF, MT ),
                                it, end, lineNumber, MAT, MF, MT ) {}
  catch ( std::exception& e ) {

    Log::info( "Encountered error while constructing channel background" );
    throw;
  }
