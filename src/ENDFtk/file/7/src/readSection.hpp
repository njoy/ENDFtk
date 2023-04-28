template< typename Iterator >
static SectionVariant
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  switch ( division.tail.MT() ) {

    case 2 : return section::Type< 7, 2 >( asHead( division ), begin, end,
                                           lineNumber, division.tail.MAT() );
    case 4 : return section::Type< 7, 4 >( asHead( division ), begin, end,
                                           lineNumber, division.tail.MAT() );
    default : throw std::exception();
  }
}
