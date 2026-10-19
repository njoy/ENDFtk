/**
 *  @class
 *  @brief A tabulated complex function as a channel's background R-matrix
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedBackgroundRMatrix :
  protected BaseBackgroundRMatrix< TabulatedBackgroundRMatrix > {

  friend BaseBackgroundRMatrix< TabulatedBackgroundRMatrix >;

  /* fields */

  TabulationRecord real_;
  TabulationRecord imaginary_;

  /* auxiliary functions */

  template < typename Range >
  static std::vector< double >
  extractReal( const Range& values ) {

    using namespace njoy::tools;
    auto reals = values | std20::views::transform(
                            [] ( const auto& complex )
                               { return complex.real(); } );
    return { reals.begin(), reals.end() };
  }

  template < typename Range >
  static std::vector< double >
  extractImaginary( const Range& values ) {

    using namespace njoy::tools;
    auto imags = values | std20::views::transform(
                            [] ( const auto& complex )
                               { return complex.imag(); } );
    return { imags.begin(), imags.end() };
  }

  template < typename Range >
  static bool compare( const Range& left, const Range& right ) {

    return std::equal( left.begin(), left.end(), right.begin(), right.end() );
  }

  static void
  verify( const TabulationRecord& real, const TabulationRecord& imaginary ) {

    if ( ( real.NP() != imaginary.NP() ) || ( real.NR() != imaginary.NR() ) ) {

      Log::error( "Encountered inconsistent size for real and imaginary values" );
      Log::info( "real.NR: {}", real.NR() );
      Log::info( "imaginary.NR: {}", imaginary.NR() );
      Log::info( "real.NP: {}", real.NP() );
      Log::info( "imaginary.NP: {}", imaginary.NP() );
      throw std::exception();
    }

    if ( !compare( real.boundaries(), imaginary.boundaries() ) ) {

      Log::error( "Encountered different interpolation ranges between the real "
                  "and imaginary parts" );
    }

    if ( !compare( real.interpolants(), imaginary.interpolants() ) ) {

      Log::error( "Encountered different interpolation schemes between the real "
                  "and imaginary parts" );
    }

    if ( !compare( real.x(), imaginary.x() ) ) {

      Log::error( "Encountered different energies between the real and "
                  "imaginary parts" );
    }
  }

  static void
  verifyLBK( int LBK ) {

    if ( LBK != 1 ) {

      Log::error( "Encountered the wrong LBK value" );
      Log::info( "Expected LBK to be equal to 1" );
      Log::info( "LBK value: {}", LBK );
      throw std::exception();
    }
  }

  /* workaround for the removal of range-v3 */

  // the range-v3 implementation used zip_transform on RBR() and RBI() but the
  // replacement capability does not work the way it should so we generate a vector
  // at construction time instead
  std::vector< std::complex< double > > complex_;

  void generateComplexNumbers() {

    // generate the complex values
    std::vector< std::complex< double > > list;
    list.reserve( this->numberPoints() );
    for ( unsigned int i = 0; i < this->numberPoints(); ++i ) {

      list.emplace_back( this->real_.y()[i], this->imaginary_.y()[i] );
    }
    this->complex_ = list;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  TabulatedBackgroundRMatrix( int index,
                              TabulationRecord&& real,
                              TabulationRecord&& imaginary ) :
    BaseBackgroundRMatrix( index ),
    real_( std::move( real ) ),
    imaginary_( std::move( imaginary ) ) {

      verify( this->real_, this->imaginary_ );
      this->generateComplexNumbers();
    }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedBackgroundRMatrix() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] index           the channel index
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] real            the real values of the tabulated rmatrix
   *  @param[in] imaginary       the imaginary values of the tabulated rmatrix
   */
  TabulatedBackgroundRMatrix( int index,
                              std::vector< long >&& boundaries,
                              std::vector< long >&& interpolants,
                              std::vector< double >&& energies,
                              std::vector< double >&& real,
                              std::vector< double >&& imaginary ) :
    TabulatedBackgroundRMatrix(
        index,
        TabulationRecord( 0.0, 0.0, 0, 0,
                          std::vector< long >( boundaries ),
                          std::vector< long >( interpolants ),
                          std::vector< double >( energies ),
                          std::move( real ) ),
        TabulationRecord( 0.0, 0.0, 0, 0,
                          std::vector< long >( boundaries ),
                          std::vector< long >( interpolants ),
                          std::vector< double >( energies ),
                          std::move( imaginary ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] index           the channel index
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] rmatrix         the complex tabulated rmatrix values
   */
  TabulatedBackgroundRMatrix( int index,
                              std::vector< long >&& boundaries,
                              std::vector< long >&& interpolants,
                              std::vector< double >&& energies,
                              std::vector< std::complex< double > >&& rmatrix ) :
    TabulatedBackgroundRMatrix( index,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                extractReal( rmatrix ),
                                extractImaginary( rmatrix ) ) {}

  private:

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  TabulatedBackgroundRMatrix( int index,
                              TabulationRecord&& real,
                              Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) :
    TabulatedBackgroundRMatrix(
        index, std::move( real ),
        TabulationRecord( it, end, lineNumber, MAT, MF, MT ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  TabulatedBackgroundRMatrix( ControlRecord&& record,
                              Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT ) :
    TabulatedBackgroundRMatrix(
        record.L1(),
        TabulationRecord( it, end, lineNumber, MAT, MF, MT ),
        it, end, lineNumber, MAT, MF, MT ) {

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
  TabulatedBackgroundRMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                              int MAT, int MF, int MT )
    try : TabulatedBackgroundRMatrix( ControlRecord( it, end, lineNumber,
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
  static constexpr long representation() { return 1; }

  using BaseBackgroundRMatrix::LBK;
  using BaseBackgroundRMatrix::LCH;
  using BaseBackgroundRMatrix::channelIndex;

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int NP() const { return this->real_.NP(); }

  /**
   *  @brief Return the number of energy points.
   */
  unsigned int numberPoints() const { return this->NP(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  unsigned int NR() const { return this->real_.NR(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  unsigned int numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->real_.interpolants(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation range boundaries.
   */
  auto NBT() const { return this->real_.boundaries(); }

  /**
   *  @brief Return the interpolation boundaries.
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->real_.x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the real component of the R-matrix values
   */
  auto RBR() const { return this->real_.y(); }

  /**
   *  @brief Return the real component of the R-matrix values
   */
  auto real() const { return this->RBR(); }

  /**
   *  @brief Return the imaginary component of the R-matrix values
   */
  auto RBI() const { return this->imaginary_.y(); }

  /**
   *  @brief Return the imaginary component of the R-matrix values
   */
  auto imaginary() const { return this->RBI(); }

  /**
   *  @brief Return the complex R-matrix values
   */
  auto RB() const {

    // see note above about range-v3 removal workaround
    // using namespace njoy::tools;
    // return std23::views::zip_transform(
    //            [] ( double real, double imag ) -> std::complex< double >
    //               { return { real, imag }; },
    //            this->real_.y(),
    //            this->imaginary_.y() );
    using namespace njoy::tools;
    return this->complex_ | std20::views::all;
  }

  /**
   *  @brief Return the complex R-matrix values
   */
  auto rmatrix() const { return this->RB(); }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  long NC() const { return 1 + this->real_.NC() + this->imaginary_.NC(); }

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
    this->real_.print( it, MAT, MF, MT );
    this->imaginary_.print( it, MAT, MF, MT );
  }
};
