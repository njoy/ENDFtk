private:

/**
 *  @brief Private constructor
 */
Tape( Tape&& other,
      ranges::difference_type_t< Buffer > offset,
      ranges::iterator_t< Buffer > start ) :
  buffer_( std::move( other.buffer_ ) ),
  tpid( std::move( other.tpid ) ),
  materials_(
    ranges::cpp20::begin( this->buffer_ ) == start
    ? std::move( other.materials_ )
    : createMap(
      ranges::cpp20::next( ranges::cpp20::begin( this->buffer_ ), offset ),
      ranges::cpp20::end( this->buffer_ ) ) ) {}

public:

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

/**
 *  @brief Constructor (copy)
 *
 *  @param[in] other   the tape to be copied
 */
Tape( const Tape& other )
  try:

    buffer_( other.buffer_ ),
    tpid( other.tpid ),
    materials_(
      ranges::cpp20::begin( this->buffer_ ) == ranges::cpp20::begin( other.buffer_ )
      ? other.materials_
      : createMap( ranges::cpp20::next( ranges::cpp20::begin( this->buffer_ ),
                                        ranges::cpp20::distance(
                                          ranges::cpp20::begin( other.buffer_ ),
                                          ranges::front( other ).buffer().begin() ) ),
                   ranges::cpp20::end( this->buffer_ ) ) ) {}
  catch( std::exception& ) {

    Log::info( "Trouble encountered while "
               "copy constructing a syntaxTree::Tape." );
    throw;
  }

/**
 *  @brief Constructor (move)
 *
 *  @param[in] other   the tape to be moved
 */
Tape( Tape&& other )
  try: Tape( std::move( other ),
             ranges::cpp20::distance(
               ranges::cpp20::begin( other.buffer_ ),
               ranges::front( other ).buffer().begin() ),
             ranges::cpp20::begin( other.buffer_ ) ) {}
  catch( std::exception& ) {

    Log::info( "Trouble encountered while "
               "move constructing a syntaxTree::Tape." );
    throw;
  }
