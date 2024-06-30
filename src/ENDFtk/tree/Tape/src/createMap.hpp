template < typename BufferIterator >
static auto
createMap( BufferIterator position, const BufferIterator& end,
           long& lineNumber ) {

  std::list< Material > materials;

  auto compare = [] ( auto&& left, auto&& right )
                    { return left < right.materialNumber(); };

  auto begin = position;
  auto division = StructureDivision( position, end, lineNumber );

  while ( division.isHead() ) {

    auto iter = std::upper_bound( materials.begin(), materials.end(), division.tail.MAT(), compare );

    materials.emplace(
      iter,
      Material( asHead( division ), begin, position, end, lineNumber ) );

    begin = position;
    division = StructureDivision( position, end, lineNumber );

    while ( division.isMend() ) {

      begin = position;
      division = StructureDivision( position, end, lineNumber );
      if ( position >= end ) {

        break;
      }
    }
  }

  if ( not division.isTend() ) {

    Log::error( "Did not find a valid TEND record in the tape" );
    throw std::exception();
  }

  return materials;
}

template < typename BufferIterator >
static auto
createMap( BufferIterator position, const BufferIterator& end ){

  long lineNumber{ 0 };
  return createMap( position, end, lineNumber );
}
