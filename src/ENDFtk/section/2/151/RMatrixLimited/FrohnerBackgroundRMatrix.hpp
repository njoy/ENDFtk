/**
 *  @class
 *  @brief Frohner parametrisation as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT FrohnerBackgroundRMatrix : 
  protected BaseBackgroundRMatrix< FrohnerBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< FrohnerBackgroundRMatrix >;

  /* fields */

  std::array< double, 5 > data_;

  /* auxiliary functions */

  static std::array< double, 5 >
  extract( ListRecord&& record ) {

    using namespace njoy::tools;

    std::array< double, 5 > values;

    if ( record.NPL() != 3 ) {

      Log::info( "Expected NPL = 3 for the Frohner parametrisation" );
      Log::info( "Found NPL value: {}", record.NPL() );
      throw std::exception();
    }

    auto list = record.list();
    values[0] = record.C1();
    values[1] = record.C2();
    std::copy_n( std20::begin( list ), 3, values.begin() + 2 );

    return values;
  }

  static void
  verifyLBK( int LBK ) {

    if ( LBK != 3 ) {

      Log::error( "Encountered the wrong LBK value" );
      Log::info( "Expected LBK to be equal to 3" );
      Log::info( "LBK value: {}", LBK );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  FrohnerBackgroundRMatrix( int index,
                            std::array< double, 5 >&& array ) :
    BaseBackgroundRMatrix( index ), data_( std::move( array ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  FrohnerBackgroundRMatrix() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] index    the channel index
   *  @param[in] ed       the down energy parameter
   *  @param[in] eu       the up energy parameter
   *  @param[in] r0       the r0 parameter
   *  @param[in] s0       the s0 parameter
   *  @param[in] ga       the ga parameter
   */
  FrohnerBackgroundRMatrix( int index, double ed, double eu,
                            double r0, double s0, double ga ) :
    FrohnerBackgroundRMatrix( index, { ed, eu, r0, s0, ga } ) {}

  private:

  /**
   *  @brief Private intermediate constructor
   */
  FrohnerBackgroundRMatrix( int index,
                          ListRecord&& list ) :
    FrohnerBackgroundRMatrix( index, extract( std::move( list ) ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  FrohnerBackgroundRMatrix( ControlRecord&& record,
                          Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT ) :
    FrohnerBackgroundRMatrix(
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
  FrohnerBackgroundRMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT )
    try : FrohnerBackgroundRMatrix( ControlRecord( it, end, lineNumber,
                                                 MAT, MF, MT ),
                                  it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing channel background" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the background R-matrix representation
   */
  static constexpr long representation() { return 3; }

  using BaseBackgroundRMatrix::LBK;
  using BaseBackgroundRMatrix::LCH;
  using BaseBackgroundRMatrix::channelIndex;

  /**
   *  @brief Return the energy down parameter in the SAMMY parametrisation
   */
  double ED() const { return this->data_[0]; }

  /**
   *  @brief Return the energy up parameter in the SAMMY parametrisation
   */
  double EU() const { return this->data_[1]; }

  /**
   *  @brief Return the R0 parameter in the SAMMY parametrisation
   */
  double R0() const { return this->data_[2]; }

  /**
   *  @brief Return the S0 parameter in the SAMMY parametrisation
   */
  double S0() const { return this->data_[3]; }

  /**
   *  @brief Return the GA parameter in the SAMMY parametrisation
   */
  double GA() const { return this->data_[4]; }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  static constexpr long NC() { return 3; }

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
    ListRecord( this->ED(), this->EU(), 0 ,0, 0,
                { this->R0(), this->S0(),
                  this->GA() } ).print( it, MAT, MF, MT );
  }
};
