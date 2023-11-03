template< typename Iterator >
static SectionVariant
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  switch ( division.tail.MT() ) {

    case 451 : return section::Type< 1, 451 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 452 : return section::Type< 1, 452 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 455 : return section::Type< 1, 455 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 456 : return section::Type< 1, 456 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 458 : return section::Type< 1, 458 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 460 : return section::Type< 1, 460 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    default : throw std::exception();
  }
}
