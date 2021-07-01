template< typename BufferIterator >
static std::map< int, File >
createMap
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::map< int, File > files;

  files.emplace( head.MF(), File( head, begin, position, end, lineNumber ) );

  begin = position;
  auto division = StructureDivision( position, end, lineNumber );

  while( division.isHead() ){
    if ( files.count( division.tail.MF() ) ){
      Log::error( "Files specified with redundant file numbers (MF)" );
      Log::info
      ( "Within an ENDF Material, files are required to specify a unique MF" );
      Log::info( "Encountered redundant MF: {} at line number: {}",
                  division.tail.MF(), lineNumber );
      throw std::exception();
    }
    files.emplace(
        division.tail.MF(),
        File( asHead(division), begin, position, end, lineNumber ) );

    if( position >= end ){
      Log::error
      ( "Material encountered end of stream before reading MEND record" );
      throw std::exception();
    }
    begin = position;
    division = StructureDivision( position, end, lineNumber );
  }

  if( not division.isMend() ){
    Log::error( "MEND record is misformatted" );
    utility::echoErroneousLine(begin, begin, end, lineNumber );
    throw std::exception();
  }
  return files;
}
