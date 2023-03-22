template< typename Iterator >
static auto
read( StructureDivision& division,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber ) {

  std::vector< Section > sections;
  while ( not division.isFend() ) {

    sections.emplace_back( Derived::readSection( division, begin, end, lineNumber ) );
    division = StructureDivision( begin, end, lineNumber );
  }
  verifyFEND( division, lineNumber );
  return fill( std::move( sections ) );
}
