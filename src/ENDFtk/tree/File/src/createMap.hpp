template< typename BufferIterator >
static std::list< Section >
createMap
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::list< Section > sections;

  auto compare = [] ( auto&& left, auto&& right )
                    { return left.sectionNumber() < right; };

  // read the first HEAD record (we need a structure division)
  --lineNumber;
  position = begin;
  auto division = StructureDivision( position, end, lineNumber );

  // continue reading sections for the same mf
  auto mf = head.MF();
  while ( division.isHead() && ( division.tail.MF() == mf ) ) {

    auto iter = std::lower_bound( sections.begin(), sections.end(), division.tail.MT(), compare );

    // check for duplicate mt
    if ( iter != sections.end() ) {

      if ( iter->sectionNumber() == division.tail.MT() ) {

        Log::error( "Found a duplicate section for MT{}", division.tail.MT() );
        Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                   division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                   lineNumber );
        throw std::exception();
      }
    }

    // add the section
    sections.emplace( iter,
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
