template< typename BufferIterator >
static std::map< int, Section >
createMap
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::map< int, Section > sections;

  // read the first HEAD record (we need a structure division)
  --lineNumber;
  position = begin;
  auto division = StructureDivision( position, end, lineNumber );

  // continue reading sections for the same mf
  auto mf = head.MF();
  while ( division.isHead() && ( division.tail.MF() == mf ) ) {

    // check for duplicate mt
    if ( sections.count( division.tail.MT() ) ) {

      Log::error( "Found a duplicate section for MT{}", division.tail.MT() );
      Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                 division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                 lineNumber );
      throw std::exception();
    }

    // add the section
    sections.emplace( division.tail.MT(),
                      Section( asHead( division ),
                               begin, position, end, lineNumber ) );

    // check for end of stream
    if ( position >= end ) {

      Log::error( "Encountered the end of stream before a FEND record was found" );
      throw std::exception();
    }

    // skip any duplicate SEND records
    begin = position;
    division = StructureDivision( position, end, lineNumber );

    while ( division.isSend() ) {

      begin = position;
      division = StructureDivision( position, end, lineNumber );
      if ( position >= end ) {

        break;
      }
    }
  }

  // warn for missing FEND record
  if ( !division.isFend() ) {

    position = begin;
    Log::info( "The FEND record for MF{} appears to be missing", mf );
    Log::info( "Current position: MAT{} MF{} MT{} at line {}",
               division.tail.MAT(), division.tail.MF(), division.tail.MT(),
               lineNumber );
  }

  return sections;
}
