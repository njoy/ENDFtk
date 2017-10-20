template< typename... Sections >
static Map
fill( section::Type<1, 451> >&& section451, Sections&&... args ) const {
  auto map =
    hana::make_map
    ( hana::make_pair( hana::int_c< args.MT() >, std::ref( args ) )... );

  auto get = [&]( auto index ){
    hana::if_
    ( hana::contains( map, index ),
      hana::make_pair
      ( index, std::make_optional( std::move( map[index].get() ) ) ),
      hana::make_pair
      ( index, std::optional< section::Type< 1, index.value > >{} ) ) };

  return hana::unpack( optionalSections, [&]( auto... indices ){
      return hana::make_map( hana::make_pair( 451_c, std::move( section451 ) ),
                             get(indices)... );
    } );
}

