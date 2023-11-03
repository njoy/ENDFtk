/**
 *  @brief Constructor
 *
 *  @param[in] i    the i coordinate
 *  @param[in] j    the j coordinate
 *  @param[in] k    the k values
 */
IntegerBase( unsigned int i, unsigned int j, std::vector< int >&& k ) :
  i_( i ), j_( j ), k_( std::move( k ) ) {

    verifySize( this->k_.size() );
  }

private:

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
IntegerBase( int i, int j,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  IntegerBase( verifyUnsigned( i, "I" ), verifyUnsigned( j, "K" ),
               readIntegers( it, end ) ) {

    tail( MAT, MF, MT, it, end, lineNumber );
  }

/**
 *  @brief Private intermediate constructor
 */
template< typename Iterator >
IntegerBase( int i,
             Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  IntegerBase( i,
               record::Integer< 5 >::Parser::read( it, end ),
               it, end, lineNumber, MAT, MF, MT ) {}

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
IntegerBase( Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT )
  try: IntegerBase( record::Integer< 5 >::Parser::read( it, end ),
                    it, end, lineNumber, MAT, MF, MT ) {}
  catch ( int nPosition ) {

    Log::info( "Error in position {}", nPosition );
    Log::info( "Error encountered while parsing INTG record" );
    throw std::exception();
  }
  catch ( std::exception& e ) {

    Log::info( "Error encountered while parsing INTG record" );
    throw e;
  }
