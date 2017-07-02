template< typename BufferIterator >
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber ){
  while( not division.isFend() ){
    this->sectionVector.emplace_back( asHead(division),
                                      begin, end, lineNumber,
                                      division.tail.MAT() );
    if( this->sectionMap.count( division.tail.MT() ) ){
      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
        ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", division.tail.MT() );
      throw std::exception();
    }
    this->sectionMap.insert( { division.tail.MT(), this->sectionVector.back() } );
    division = StructureDivision( begin, end, lineNumber );
  }
}
