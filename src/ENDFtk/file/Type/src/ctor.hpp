template< typename BufferIterator > 
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber )
  try:
    sectionVector( collectVector( division, begin, end, lineNumber ) ),
    sectionMap( collectMap( this->sectionVector ) ) {
  } catch ( std::exception& e ){
    Log::info( "Error while reading File {}", FileNumber );
    throw e;  
  }

Type( const Type& other ) :
  sectionVector( other.sectionVector ),
  sectionMap( collectMap( this->sectionVector ) ) {}

Type( Type&& other ) noexcept = default;
