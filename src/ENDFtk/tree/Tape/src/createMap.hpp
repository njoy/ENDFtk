template < typename BufferIterator >
static auto
createMap( BufferIterator position, const BufferIterator& end, long& ln ){

  std::multimap< int, Material > materials;

  auto begin = position;
  auto division = StructureDivision( position, end, ln );

  while ( division.isHead() ) {

    materials.emplace(
      division.tail.MAT(),
      Material( asHead( division ), begin, position, end, ln ) );

    begin = position;
    division = StructureDivision( position, end, ln );
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

  long ln{ 0 };
  return createMap( position, end, ln );
}
