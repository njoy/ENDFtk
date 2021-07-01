template< typename BufferIterator >
static std::map< int, Section >
createMap
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::map< int, Section > sections;

  sections.emplace(
      head.MT(),
      Section( head, begin, position, end, lineNumber ) );

  begin = position;
  auto division = StructureDivision( position, end, lineNumber );

  while( division.isHead() ){

    if ( sections.count( division.tail.MT() ) ){
      Log::error( "Sections specified with redundant section numbers (MT)" );
      Log::info
      ( "Within an ENDF File, sections are required to specify a unique MT" );
      Log::info( "Encountered redundant MT: {}", division.tail.MT() );
      throw std::exception();
    }

    sections.emplace(
      division.tail.MT(),
      Section( asHead( division ), begin, position, end, lineNumber ) );

    if( position >= end ){
      Log::error( "File encountered end of stream before reading FEND record" );
      throw std::exception();
    }

    begin = position;
    division = StructureDivision( position, end, lineNumber );
  }

  if( not division.isFend() ){
    Log::error( "FEND record is misformatted" );
    utility::echoErroneousLine(begin, begin, end, lineNumber );
    throw std::exception();
  }

  return sections;
}
