template< typename BufferIterator >
static std::map< int, File >
createMap
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::map< int, File > files;

  // read the first HEAD record (we need a structure division)
  --lineNumber;
  position = begin;
  auto division = StructureDivision( position, end, lineNumber );

  // continue reading sections for the same mf
  auto mat = head.MAT();
  while ( division.isHead() && ( division.tail.MAT() == mat ) ) {

    // check for duplicate mf
    if ( files.count( division.tail.MF() ) ) {

      Log::error( "Found a duplicate section for MF{}", division.tail.MF() );
      Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                 division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                 lineNumber );
      throw std::exception();
    }

    // add the file
    files.emplace( division.tail.MF(),
                   File( asHead( division ),
                         begin, position, end, lineNumber ) );

    // check for end of stream
    if ( position >= end ) {

      Log::error( "Encountered the end of stream before a MEND record was found" );
      throw std::exception();
    }

    // skip any duplicate FEND records
    begin = position;
    division = StructureDivision( position, end, lineNumber );

    while ( division.isFend() ) {

      begin = position;
      division = StructureDivision( position, end, lineNumber );
      if ( position >= end ) {

        break;
      }
    }
  }

  // warn for missing MEND record
  if ( !division.isMend() ) {

    position = begin;
    Log::info( "The MEND record for MAT{} appears to be missing", mat );
    Log::info( "Current position: MAT{} MF{} MT{} at line {}",
               division.tail.MAT(), division.tail.MF(), division.tail.MT(),
               lineNumber );
  }

  return files;
}
