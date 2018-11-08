Type( int MT, double zaid, double awr, long jp, long lct,
      std::vector< ReactionProduct >&& products ) :
  Base( zaid, awr, MT ), jp_( jp ), lct_( lct ),
  products_( std::move( products ) ) {}

template< typename Iterator >
Type( HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT )
  try:
    Base( head, MAT, 6 ), jp_( head.L1() ), lct_( head.L2() ),
    products_( readReactionProducts( begin, end, lineNumber,
                                     MAT, head.MF(), head.MT(), head.N1() ) ) {
    readSEND(begin, end, lineNumber, MAT, 6 );
  } catch( std::exception& e ) {
    Log::info( "Trouble while reading section {} of File 6 of Material {}",
               head.MT(), MAT );
    throw e;
  }

