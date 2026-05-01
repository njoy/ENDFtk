template< typename BufferIterator >
static std::list< GFile >
fill
( const HEAD& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber ){

  std::list< GFile > files;
  std::vector< GSection > sections;

  auto compare = [] ( auto&& left, auto&& right ) {

    if ( left.MF() < right.first ) {

      return true;
    }
    else if ( left.MF() == right.first ) {

      return left.MT() < right.second;
    }
    else {

      return false;
    }
  };

  // read the first HEAD record (we need a structure division)
  --lineNumber;
  position = begin;
  auto division = StructureDivision( position, end, lineNumber );

  // continue reading sections for the same mf
  auto mat = head.MAT();
  while ( division.isHead() && ( division.tail.MAT() == mat ) ) {

    auto iter = std::lower_bound( sections.begin(), sections.end(),
                                  std::make_pair( division.tail.MF(), division.tail.MT() ),
                                  compare );

    // check for duplicate mf,mt
    if ( ( iter != sections.end() ) &&
         ( iter->fileNumber() == division.tail.MF() ) &&
         ( iter->sectionNumber() == division.tail.MT() ) ) {

      Log::info( "Found a duplicate section for MF{} MT{}, skipping section",
                 division.tail.MF(), division.tail.MT() );
      Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                 division.tail.MAT(), division.tail.MF(), division.tail.MT(),
                 lineNumber );

      //just skip the section
      GSection( asHead( division ), begin, position, end, lineNumber );
    }
    else {

      // add the section
      sections.emplace( iter, asHead( division ), begin, position, end, lineNumber );
    }

    // check for end of stream
    if ( position >= end ) {

      Log::error( "Encountered the end of stream before an END record was found" );
      throw std::exception();
    }

    // get the next HEAD record
    begin = position;
    division = StructureDivision( position, end, lineNumber );
    if ( ! division.isHead() && division.isFend() ) {

      begin = position;
      division = StructureDivision( position, end, lineNumber );
    }
  }

  // subdivide into files
  auto iter = sections.begin();
  auto upper = std::upper_bound( sections.begin(), sections.end(), iter->fileNumber(),
                                 [] ( auto&& left, auto&& right )
                                    { return left < right.fileNumber(); } );
  while ( iter != sections.end() ) {

    files.emplace_back( iter->materialNumber(), iter->fileNumber(),
                        std::list< GSection >( iter, upper ) );

    iter = upper;
    upper = std::upper_bound( iter, sections.end(), iter->fileNumber(),
                              [] ( auto&& left, auto&& right )
                                 { return left < right.fileNumber(); } );
  }

  return files;
}
