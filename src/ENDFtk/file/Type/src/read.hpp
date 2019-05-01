template< typename BufferIterator >
static std::map< int, Section > read( StructureDivision& division,
                                      BufferIterator& begin,
                                      const BufferIterator& end,
                                      long& lineNumber ) {

  std::vector< Section > sections;
  while ( not division.isFend() ) {

    sections.emplace_back( asHead( division ), begin, end,
                           lineNumber, division.tail.MAT() );
    division = StructureDivision( begin, end, lineNumber );
  }
  return fill( std::move( sections ) );
}
