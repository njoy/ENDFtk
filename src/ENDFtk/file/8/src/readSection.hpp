template< typename Iterator >
static SectionVariant
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  switch ( division.tail.MT() ) {

    case 454 : return section::Type< 8, 454 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 457 : return section::Type< 8, 457 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 459 : return section::Type< 8, 459 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    default : throw std::exception();
  }
}
