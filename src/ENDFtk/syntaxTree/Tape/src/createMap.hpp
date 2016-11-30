static Multimap createMap( std::vector< Material_t >& vector ){
  Multimap map;
  map.reserve( vector.size() );
  for ( auto& material : vector ){ map.insert( { material.MAT(), material } ); }
  return map;
}
