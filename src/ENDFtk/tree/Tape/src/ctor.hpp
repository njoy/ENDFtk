/**
 *  @brief Constructor
 *
 *  @param[in] buffer       the buffer from which a buffer can be constructed
 *  @param[in] lineNumber   the line numbers
 */
template< typename BufferArg,
          std::enable_if_t<
            std::is_constructible< Buffer, BufferArg >::value, bool > = true >
Tape( BufferArg&& buffer, long lineNumber = 0 )
  try : buffer_( std::forward< BufferArg >( buffer ) ) {

    auto position = ranges::cpp20::begin( this->buffer_ );
    auto end = ranges::cpp20::end( this->buffer_ );
    this->tpid = TapeIdentification{ position, end, lineNumber };
    materials_ = createMap( position, end, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info( "Trouble encountered while constructing a tape syntax tree." );
    throw e;
  }
