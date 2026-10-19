/**
 *  @class
 *  @brief A compact correlation matrix
 *
 *  This is the only instance where INTG records are used, so we decided to not
 *  implement INTG records as a base record. This class will handle the
 *  compression and decompression. Some assumptions will be made to do this so,
 *  as a result, this class may not reproduce an existing compact matrix
 *  exactly as it was originally given.
 *
 *  See ENDF102, section 0.6.4.9 and 32.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT CompactCorrelationMatrix {

  /* fields */

  int ndigit_;
  int nnn_;
  std::vector< unsigned int > i_;
  std::vector< unsigned int > j_;
  std::vector< double > correlations_;

  /* auxiliary functions */

  template< typename Iterator >
  static
  std::tuple< std::vector< unsigned int >,
              std::vector< unsigned int >,
              std::vector< double > >
  readMatrixElements( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT,
                      unsigned int ndigit,
                      unsigned int lines ) {

    // this code is not pretty, but the INTG records are just dumb so ...

    std::vector< unsigned int > is;
    std::vector< unsigned int > js;
    std::vector< double > correlations;

    auto process = [&is,&js,&correlations] ( auto&& record, int factor ) -> void {

      for ( unsigned int index = 0; index < record.K().size(); ++index  ) {

        long value = record.K()[index];
        if ( value != 0  ) {

          is.emplace_back( record.I() );
          js.emplace_back( record.J() + index );
          if ( value > 0 ) {

            correlations.emplace_back( ( static_cast< double >( value )
                                         + 0.5 ) / factor );
          }
          else {

            correlations.emplace_back( ( static_cast< double >( value )
                                         - 0.5 ) / factor );
          }
        }
      }
    };

    switch ( ndigit ) {

      case 2: {

        using INTG = record::IntegerBase< 2, 18 >;
        for ( unsigned int line = 0; line < lines; ++line ) {

          process( INTG( begin, end, lineNumber, MAT, MF, MT ), 100 );
        }

        break;
      }
      case 3: {

        using INTG = record::IntegerBase< 3, 13 >;
        for ( unsigned int line = 0; line < lines; ++line ) {

          process( INTG( begin, end, lineNumber, MAT, MF, MT ), 1000 );
        }

        break;
      }
      case 4: {

        using INTG = record::IntegerBase< 4, 11 >;
        for ( unsigned int line = 0; line < lines; ++line ) {

          process( INTG( begin, end, lineNumber, MAT, MF, MT ), 10000 );
        }

        break;
      }
      case 5: {

        using INTG = record::IntegerBase< 5, 9 >;
        for ( unsigned int line = 0; line < lines; ++line ) {

          process( INTG( begin, end, lineNumber, MAT, MF, MT ), 100000 );
        }

        break;
      }
      case 6: {

        using INTG = record::IntegerBase< 6, 8 >;
        for ( unsigned int line = 0; line < lines; ++line ) {

          process( INTG( begin, end, lineNumber, MAT, MF, MT ), 1000000 );
        }

        break;
      }
      default: {

        Log::error( "Encountered illegal NDIGIT value" );
        Log::info( "NDIGIT should be equal to 2, 3, 4, 5 or 6" );
        Log::info( "NDIGIT value: {}", ndigit );
        throw std::exception();
      }
    }

    return std::make_tuple( std::move( is ), std::move( js ),
                            std::move( correlations ) );
  }

  template < typename String >
  static unsigned int verifyUnsigned( int value, const String& name ) {

    if ( value < 0 ) {

      Log::error( "Encountered negative integer for {}, expected an unsigned integer",
                  name );
      Log::info( "{}: {}", name, value );
    }

    return static_cast< unsigned int >( value );
  }

  std::vector< std::tuple< unsigned int, unsigned int,
                           std::vector< int > > > compact() const {

    // this code is not pretty, but the INTG records are just dumb so ...

    std::vector< std::tuple< unsigned int, unsigned int,
                             std::vector< int > > > lines;
    if ( this->correlations_.size() != 0 ) {

      // the maximum number of values per line
      unsigned int n = 0;
      switch ( this->NDIGIT() ) {

        case 2: { n = 18; break; }
        case 3: { n = 13; break; }
        case 4: { n = 11; break; }
        case 5: { n =  9; break; }
        case 6: { n =  8; break; }
        default: { /* unreachable */ break; }
      }

      // conversion factor
      double factor = 1;
      switch ( this->NDIGIT() ) {

        case 2: { factor = 100; break; }
        case 3: { factor = 1000; break; }
        case 4: { factor = 10000; break; }
        case 5: { factor = 100000; break; }
        case 6: { factor = 1000000; break; }
        default: { /* unreachable */ break; }
      }

      // conversion function
      auto convert = [factor] ( double value ) -> int {

        value *= factor;
        if ( std::abs( value ) <= 1. ) {

          return 0;
        }
        if ( value > 0. ) {

          return std::floor( value );
        }
        else {

          return -std::floor( std::abs( value ) );
        }
      };

      // compact the correlation matrix
      lines.push_back( { this->i_[0], this->j_[0], { convert( this->correlations_[0] ) } } );
      unsigned int size = this->i_.size();
      for ( unsigned int i = 1; i < size; ++i ) {

        if ( ( this->i_[i] == std::get< 0 >( lines.back() ) ) &&
             ( std::get< 2 >( lines.back() ) ).size() < n ) {

          if ( this->j_[i] < std::get< 1 >( lines.back() ) + n ) {

            int pad = this->j_[i] - std::get< 1 >( lines.back() ) - std::get< 2 >( lines.back() ).size();
            if ( pad > 0 ) {

              std::get< 2 >( lines.back() ).insert( std::get< 2 >( lines.back() ).end(),
                                                    pad,
                                                    0 );
            }
            std::get< 2 >( lines.back() ).emplace_back( convert( this->correlations_[i] ) );
          }
          else {

            lines.emplace_back( std::make_tuple (
                                  this->i_[i],
                                  this->j_[i],
                                  std::vector< int >{ convert( this->correlations_[i] ) } ) );
          }
        }
        else {

          lines.emplace_back( std::make_tuple (
                                this->i_[i],
                                this->j_[i],
                                std::vector< int >{ convert( this->correlations_[i] ) } ) );
        }
      }
    }

    return lines;
  }

  static void
  verifyDigits( unsigned int n ) {

    if ( ( n < 2 ) || ( n > 6 ) ) {

      Log::error( "Encountered illegal NDIGIT value" );
      Log::info( "NDIGIT should be equal to 2, 3, 4, 5 or 6" );
      Log::info( "NDIGIT value: {}", n );
      throw std::exception();
    }
  }

  static void
  verifySize( unsigned int ni, unsigned int nj, unsigned int nc ) {

    if ( !( ( ni == nj ) && ( ni == nc ) ) ) {

      Log::error( "Encountered inconsistent number of i, j and correlation values" );
      Log::info( "i.size(): {}", ni );
      Log::info( "j.size(): {}", nj );
      Log::info( "correlations.size(): {}", nc );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  CompactCorrelationMatrix( unsigned int order,
                            std::tuple< std::vector< unsigned int >,
                                        std::vector< unsigned int >,
                                        std::vector< double > >&& data,
                            unsigned int ndigit ) :
    CompactCorrelationMatrix(
        order,
        std::move( std::get< 0 >( data ) ),
        std::move( std::get< 1 >( data ) ),
        std::move( std::get< 2 >( data ) ),
        ndigit ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CompactCorrelationMatrix( ControlRecord&& cont,
                            Iterator& begin,
                            const Iterator& end,
                            long& lineNumber,
                            int MAT, int MF, int MT ) :
    CompactCorrelationMatrix(
        verifyUnsigned( cont.L2(), "NNN" ),
        readMatrixElements( begin, end, lineNumber, MAT, MF, MT,
                            verifyUnsigned( cont.L1(), "NDIGIT" ),
                            verifyUnsigned( cont.N1(), "NM" ) ),
        verifyUnsigned( cont.L1(), "NDIGIT" ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CompactCorrelationMatrix() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] order          the order of the (square) correlation matrix
   *  @param[in] i              the i coordinates
   *  @param[in] j              the j coordinates
   *  @param[in] correlations   the correlation values
   *  @param[in] ndigit        the number of digits for compacting (default = 6)
   */
  CompactCorrelationMatrix( unsigned int order,
                            std::vector< unsigned int >&& i,
                            std::vector< unsigned int >&& j,
                            std::vector< double >&& correlations,
                            unsigned int ndigit = 6 )
    try : ndigit_( ndigit ), nnn_( order ), i_( std::move( i ) ), j_( std::move( j ) ),
          correlations_( std::move( correlations ) )
           {

      verifySize( this->i_.size(), this->j_.size(), this->correlations_.size() );
      verifyDigits( this->ndigit_ );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a compact correlation "
                 "matrix" );
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
  CompactCorrelationMatrix( Iterator& it, const Iterator& end, long& lineNumber,
                            int MAT, int MF, int MT ) :
    CompactCorrelationMatrix( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                              it, end, lineNumber, MAT, MF, MT ) {}

  /* methods */

  /**
   *  @brief Return the number of digits used for compacting
   */
  unsigned int NDIGIT() const { return this->ndigit_; }

  /**
   *  @brief Return the number of digits used for compacting
   */
  unsigned int numberDigits() const { return this->NDIGIT(); }

  /**
   *  @brief Return the order of the correlation matrix
   */
  unsigned int NNN() const { return this->nnn_; }

  /**
   *  @brief Return the order of the correlation matrix
   */
  unsigned int order() const { return this->NNN(); }

  /**
   *  @brief Return the i coordinates for which correlation values are
   *         available
   */
  auto I() const {

    using namespace njoy::tools;
    return std20::views::all( this->i_ );
  }

  /**
   *  @brief Return the j coordinates for which correlation values are
   *         available
   */
  auto J() const {

    using namespace njoy::tools;
    return std20::views::all( this->j_ );
  }

  /**
   *  @brief Return the correlation values
   */
  auto correlations() const {

    using namespace njoy::tools;
    return std20::views::all( this->correlations_ );
  }

  /**
   *  @brief Return the number of lines in this MF32 MT151 component
   */
  long NC() const {

    return 1 + this->compact().size();
  };

  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    // this code is not pretty, but the INTG records are just dumb so ...

    // compact the matrix
    auto lines = this->compact();

    // write the correlation matrix
    ControlRecord( 0., 0.,
                   this->NDIGIT(), this->NNN(),
                   lines.size(), 0 ).print( it, MAT, MF, MT );
    for ( auto& line : lines ) {

      switch ( this->NDIGIT() ) {

        case 2: { record::IntegerBase< 2, 18 >(
                      std::get< 0 >( line ),
                      std::get< 1 >( line ),
                      std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                  break; }
        case 3: { record::IntegerBase< 2, 13 >(
                      std::get< 0 >( line ),
                      std::get< 1 >( line ),
                      std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                  break; }
        case 4: { record::IntegerBase< 4, 11 >(
                      std::get< 0 >( line ),
                      std::get< 1 >( line ),
                      std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                  break; }
        case 5: { record::IntegerBase< 5, 9 >(
                      std::get< 0 >( line ),
                      std::get< 1 >( line ),
                      std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                  break; }
        case 6: { record::IntegerBase< 6, 8 >(
                      std::get< 0 >( line ),
                      std::get< 1 >( line ),
                      std::move( std::get< 2 >( line ) ) ).print( it, MAT, MF, MT );
                  break; }
        default: { /* unreachable */ break; }
      }
    }
  }
};
