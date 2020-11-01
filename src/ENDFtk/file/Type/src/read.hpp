template< typename BufferIterator >
static auto
read( StructureDivision& division,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber ) {

  std::map< int, Section > sectionMap;
  auto insert_fn = hana::partial( insert{}, std::ref( sectionMap ) );
  while ( not division.isFend() ) {

    insert_fn( Section( asHead( division ), begin, end,
                        lineNumber, division.tail.MAT() ) );
    division = StructureDivision( begin, end, lineNumber );
  }
  return sectionMap;
}
