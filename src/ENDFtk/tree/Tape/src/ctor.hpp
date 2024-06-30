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

    auto position = ranges::cpp20::begin( buffer );
    auto end = ranges::cpp20::end( buffer );
    this->tpid_ = TapeIdentification{ position, end, lineNumber };
    materials_ = fill( position, end, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info( "Trouble encountered while constructing a tape syntax tree." );
    throw e;
  }
