/**
 *  @class
 *  @brief No background is given for the channel
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT NoBackgroundRMatrix : 
  protected BaseBackgroundRMatrix< NoBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< NoBackgroundRMatrix >;

  /* auxiliary functions */

  static void
  verifyLBK( int LBK ) {

    if ( LBK != 0 ) {

      Log::error( "Encountered the wrong LBK value" );
      Log::info( "Expected LBK to be equal to 0" );
      Log::info( "LBK value: {}", LBK );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  NoBackgroundRMatrix( ControlRecord&& record ) :
    NoBackgroundRMatrix( record.L1() ) {

      verifyLBK( record.L2() );
    }

public:

  /* constructor */

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

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 0; }

  using BaseBackgroundRMatrix::LBK;
  using BaseBackgroundRMatrix::LCH;
  using BaseBackgroundRMatrix::channelIndex;

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  static constexpr long NC() { return 1; }

  /**
   *  @brief Print this MF2/MT151 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    ControlRecord( 0.0, 0.0, this->LCH(),
                   this->LBK(), 0, 0 ).print( it, MAT, MF, MT );
  }
};
