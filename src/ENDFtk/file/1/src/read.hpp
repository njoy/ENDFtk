template< typename BufferIterator >
static section::Type< 1, 451 > read(
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber ) {

  auto& head = asHead( structureDivision );

  if ( head.MT() != 451 ){
    Log::error( "Illegal section number in File 1" );
    Log::info( "First section of File 1 must be Section 451");
    Log::info( "First section encountered: {}", head.MT() );
  }

  auto section451 = [&]{
    try{
      return section::Type< 1, 451 >( head, begin, end, lineNumber, head.MAT() );
    } catch( std::exception& e ) {
      Log::info( "Error while reading File 1 Section 451" );
      throw e;
    }
  }();

  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info( "Error while reading structure division following File 1 Section 451" );
    throw e;
  }

  return section451;
}

template< int SectionNo, typename BufferIterator >
static std::optional< section::Type< 1, SectionNo > >
read( StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT ) {
  const auto& head = asHead( structureDivision );

  if ( head.MT() != SectionNo ){ return std::nullopt; }

  auto section = [&]{
    try{
      return section::Type< 1, SectionNo >( head, begin, end, lineNumber, MAT );
    } catch( std::exception& e ) {
      Log::info( "Error while reading File 1 Section {}", SectionNo );
      throw e;
    }
  }();

  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info( "Error while reading structure division following File 1 Section {}",
               SectionNo );
    throw e;
  }

  return std::make_optional( std::move( section ) );
}
