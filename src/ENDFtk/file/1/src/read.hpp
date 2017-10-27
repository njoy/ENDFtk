template< typename BufferIterator >
static section::Type< 1, 451 > read(
      decltype(451_c),
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber ) {

  auto& head = asHead( structureDivision );

  if ( head.MT() != 451 ){
    Log::error( "Illegal section number in File 1" );
    Log::info( "First section of File 1 must be Section 451");
    Log::info( "First section encountered: {}", head.MT() );
    Log::info( "Line number: {}", lineNumber - 1 );
    throw std::exception();
  }

  //! @todo why use a lambda here? - no need to catch or log info message (log message done in mt451 constructor)
  auto section451 = [&]{
    return section::Type< 1, 451 >( head, begin, end, lineNumber, head.MAT() );
  }();

  structureDivision = StructureDivision( begin, end, lineNumber );

  return section451;
}

template< long long int SectionNo, typename BufferIterator >
static std::optional< section::Type< 1, (int)SectionNo > >
read( hana::llong< SectionNo >,
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT ) {
  const auto& head = asHead( structureDivision );

  if ( head.MT() != SectionNo ){ return std::nullopt; }

  //! @todo why use a lambda here? - no need to catch or log info message (log message done in mt4xx constructor)
  auto section = [&]{
    return section::Type< 1, (int)SectionNo >( head, begin, end, lineNumber, MAT );
  }();

  structureDivision = StructureDivision( begin, end, lineNumber );

  return std::make_optional( std::move( section ) );
}
