protected:

Tape( Buffer&& buffer, 
      TapeIdentification&& tpid,
      BufferIterator& it, BufferIterator& end, 
      long& lineNumber ):
  buffer_( std::move( buffer ) ),
  tpid( std::move( tpid ) ),
  materialVector( createVector( it, end, lineNumber ) ),
  materialMap( createMap( this->materialVector ) )
{}

Tape( Buffer&& buffer, 
      BufferIterator&& it, BufferIterator&& end, 
      long& ln ):
  Tape( std::move( buffer ), 
        TapeIdentification{ it, end, ln },
        it, end, ln )
{ }

public: 
Tape( Buffer&& buffer, long ln = 0 )
try:
  Tape( std::move( buffer ), 
        ranges::begin( buffer ), ranges::end( buffer ), ln )
{ }
catch ( std::exception& e ){
  Log::info( "Trouble encountered while constructing a tape syntax tree." );
  throw e;
}

Tape( const Tape& other ) 
try:
  buffer_( other.buffer_ ),
  tpid( other.tpid ),
  materialVector( other.materialVector ),
  materialMap( createMap( this->materialVector ) ){}
catch( std::exception& ){
  Log::info( "Trouble copy constructing a syntaxTree::Tape." );
  throw;
}


Tape( Tape&& other ) noexcept = default;
