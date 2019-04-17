template< int sectionNo, typename... Sections >
static Map
fill( section::Type< 7, sectionNo >&& section, Sections&&... sections ) {
  auto map =
    hana::make_map
    ( hana::make_pair( hana::llong_c< section.MT() >, std::ref( section ) ),
      hana::make_pair( hana::llong_c< sections.MT() >, std::ref( sections ) )... );

  auto get = [&]( auto index ){
    hana::if_
    ( hana::contains( map, index ),
      hana::make_pair
      ( index, std::make_optional( std::move( map[index].get() ) ) ),
      hana::make_pair
      ( index, std::optional< section::Type< 7, index.value > >{} ) ); };

  return hana::unpack( optionalSections(), [&]( auto... indices ){
      return hana::make_map( get(indices)... );
    } );
}
