protected:
Tape( Tape&& other,
      ranges::difference_type_t< Buffer > offset,
      ranges::iterator_t< Buffer > start ) :
  buffer_( std::move( other.buffer_ ) ),
  tpid( std::move( other.tpid ) ),
  materials_(
    ranges::begin( this->buffer_ ) == start
    ? std::move( other.materials_ )
    : createMap(
      ranges::next( ranges::begin( this->buffer_ ), offset ),
      ranges::end( this->buffer_ )
    )
  )
{ }

public:
template< typename BufferArg,
  std::enable_if_t<
    std::is_constructible< Buffer, BufferArg >::value, bool > = true
        >
Tape( BufferArg&& buffer, long ln = 0 )
try:
  buffer_( std::forward< BufferArg >( buffer ) )
{
  auto position = ranges::begin( this->buffer_ );
  auto end = ranges::end( this->buffer_ );
  this->tpid = TapeIdentification{ position, end, ln };
  materials_ = createMap( position, end, ln );
}
catch ( std::exception& e ){
  Log::info( "Trouble encountered while constructing a tape syntax tree." );
  throw e;
}

Tape( const Tape& other )
try:
  buffer_( other.buffer_ ),
  tpid( other.tpid ),
  materials_(
    ranges::begin( this->buffer_ ) == ranges::begin( other.buffer_ )
    ? other.materials_
    : createMap(
      ranges::next( ranges::begin( this->buffer_ ),
                    ranges::distance(
                      ranges::begin( other.buffer_ ),
                      ranges::front( other ).buffer().begin()
                    )
                  ),
      ranges::end( this->buffer_ )
    )
  )
{ }
catch( std::exception& ){
  Log::info( "Trouble encountered while "
             "copy constructing a syntaxTree::Tape." );
  throw;
}

Tape( Tape&& other )
try:
  Tape( std::move( other ),
        ranges::distance(
          ranges::begin( other.buffer_ ),
          ranges::front( other ).buffer().begin()
        ),
        ranges::begin( other.buffer_ )
      )
{ }
catch( std::exception& ){
  Log::info( "Trouble encountered while "
             "move constructing a syntaxTree::Tape." );
  throw;
}
