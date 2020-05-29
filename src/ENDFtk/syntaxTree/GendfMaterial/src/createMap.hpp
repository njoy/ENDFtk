/*
 * @brief Utility routine for use in constructor to create map of Sections.
 */
static std::map< MFMT, Section_t > createMap(
    const HeadRecord& head,
    BufferIterator begin,
    BufferIterator& position,
    const BufferIterator& end,
    long& lineNumber ) {

  std::map< MFMT, Section_t > sections;

  // emplace first section
  auto idx = MFMT( head.MF(), head.MT() );
  sections.emplace( idx,
                    Section_t(head, begin, position, end, lineNumber) );

  // read next card
  begin = position;
  auto division = StructureDivision( position, end, lineNumber );

  // loop until MEND is found
  while( division.isHead() ){

    // map index
    idx = MFMT( division.tail.MF(), division.tail.MT() );

    // read section
    Section_t new_section( asHead(division), begin,
                           position, end, lineNumber );

    // map index already present
    if ( sections.count(idx) ) {
      Log::info("Warning: MFD{}, MT{} is already present in GENDF file.  "
                "Skipping redundant section.",
                division.tail.MF(), division.tail.MT() );
    }

    // emplace next section
    else {
      sections.emplace(idx, new_section);
    }

    // read next card
    if( position >= end ){
      Log::error( "Material encountered end of stream before reading "
                  "MEND record" );
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

  return sections;

}
