template< typename Iterator >
static auto
readSubsections( Iterator& begin, const Iterator& end, long& lineNumber,
                 int MAT, int MT, int NK ){
  std::vector< TabulationRecord > tabulations;

  if ( NK < 1 ){
    Log::error("Encountered illegal NK value");
    Log::info("NK must be greater than 0");
    Log::info("NK value: {}", NK );
    Log::info("Line number: {}", lineNumber - 1 );
    throw std::runtime_error("section::Type<13> ctor");
  }

  tabulations.reserve( NK + NK > 1 );
  if ( NK > 1 ){
    tabulations.emplace_back( begin, end, lineNumber, MAT, 13, MT );
  }

  while( NK-- ){
    tabulations.emplace_back
      ( static_cast< TabulationRecord&& >
        ( Subsection{ begin, end, lineNumber, MAT, MT } ) );
  }

  return tabulations;
}
