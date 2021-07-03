template < typename BufferIterator >
static auto
createMap( BufferIterator position, const BufferIterator& end, long& ln ){

  std::multimap< int, Material > materials;

  auto begin = position;
  auto division = StructureDivision( position, end, ln );

  while ( not division.isTend() ) {

    materials.emplace( division.tail.MAT(),
      Material( asHead( division ), begin, position, end, ln ) );

    begin = position;
    division = StructureDivision( position, end, ln );
  }

  return materials;
}

template < typename BufferIterator >
static auto
createMap( BufferIterator position, const BufferIterator& end ){

  long ln{ 0 };
  return createMap( position, end, ln );
}
