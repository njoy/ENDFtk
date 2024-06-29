/**
 *  @brief Empty tape constructor
 *
 *  @param[in] id    the tape identifier
 */
Tape( TapeIdentification&& id ) : tpid_( std::move( id ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] buffer       the buffer from which a buffer can be constructed
 *  @param[in] lineNumber   the line numbers
 */
template< typename Buffer >
Tape( const Buffer& buffer, long lineNumber = 0 )
  try {

    using namespace njoy::tools;
    auto position = std20::begin( buffer );
    auto end = std20::end( buffer );
    this->tpid_ = TapeIdentification{ position, end, lineNumber };
    materials_ = createMap( position, end, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info( "Trouble encountered while constructing a tape syntax tree." );
    throw e;
  }
