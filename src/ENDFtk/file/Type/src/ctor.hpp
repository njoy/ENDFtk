Type( std::vector< Section >&& sections ) :
  sectionVector( std::move( sections ) ),
  sectionMap( collectMap( this->sectionVector ) ) {

  auto mt = [] ( const Section& section ) { return section.MT(); };

  if ( not ranges::is_sorted( this->sectionVector, hana::less, mt ) ) {

    ranges::sort( this->sectionVector, hana::less, mt );
    sectionMap = collectMap( this->sectionVector );
  }
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
