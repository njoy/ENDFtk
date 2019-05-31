static auto
createMap( BufferIterator position, const BufferIterator& end, long& ln ){

  std::multimap< int, Material_t > materials;

  auto division = StructureDivision( position, end, ln );
  int lastMAT = division.tail.MAT();

  while ( not division.isTend() ) {
    if( lastMAT > division.tail.MAT() ){
      Log::error( "Material numbers (MAT) must be increasing." );
      Log::info( "Found material number: {}", division.tail.MAT() );
      Log::info( "Expected a material number >= {}", lastMAT );
      throw std::exception();
    }
    materials.emplace( division.tail.MAT(),
      Material_t( asHead( division ), position, position, end, ln ) );

    lastMAT = division.tail.MAT();
    division = StructureDivision( position, end, ln );
  }

  return materials;
}

static auto
createMap( BufferIterator position, const BufferIterator& end ){

  std::multimap< int, Material_t > materials;
  long ln{ 0 };

  auto division = StructureDivision( position, end, ln );

  while ( not division.isTend() ) {
    materials.emplace( division.tail.MAT(),
      Material_t( asHead( division ), position, position, end, ln ) );

    division = StructureDivision( position, end, ln );
  }

  return materials;
}
