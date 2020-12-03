static auto
fill( std::vector< Section >&& sections ) {

  std::map< int, Section > sectionMap;
  for ( auto&& section : sections ) {

    insert{}( sectionMap, std::move( section ) );
  }
  return sectionMap;
}
