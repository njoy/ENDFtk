Type( std::vector< Section > sections ) :
  sectionVector( sections ),
  sectionMap( collectMap( this->sectionVector ) ) {

  ranges::sort( this->sectionVector,
                [] ( const auto& left, const auto& right )
                   { return left.MT() < right.MT(); } );
}

template< typename BufferIterator > 
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber )
  try:
    sectionVector( collectVector( division, begin, end, lineNumber ) ),
    sectionMap( collectMap( this->sectionVector ) ){
  } catch ( std::exception& e ){
    Log::info("Encountered error while generating file::Type<{}>", FileNumber );
    throw e;  
  }

Type( const Type& other ) :
  sectionVector( other.sectionVector ),
  sectionMap( collectMap( this->sectionVector ) ){}

Type( Type&& other ) noexcept = default;
