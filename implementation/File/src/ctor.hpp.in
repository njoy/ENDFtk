
template< typename BufferIterator >
File( ENDFtk::implementation::StructureDivision& division,
      BufferIterator& begin, BufferIterator end, long& lineNumber){

  while( not division.isFend() ){
    sections_.emplace_back(asHead(division), begin, end, lineNumber,
                           division.tail.MAT());

    if( sectionMap_.count( division.tail.MT() ) ){
      LOG(ERROR) << "Sections specified with redundant section numbers (MT)";
      LOG(INFO)  <<
        "Within an ENDF File, sections are required to specify a unique MT";
      LOG(INFO)  << "Encountered redundant MT: " << division.tail.MT();
      throw std::exception();
    }
    sectionMap_.insert( { division.tail.MT(), sections_.back() } );

    division = StructureDivision(begin, end, lineNumber);
  }

}
