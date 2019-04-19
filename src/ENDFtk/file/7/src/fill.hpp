template< int sectionNo, typename... Sections >
static Map
fill( section::Type< 7, sectionNo >&& section, Sections&&... sections ) {

  auto map =
    hana::make_map
    ( hana::make_pair( hana::llong_c< static_cast< long long >( sectionNo ) >, std::ref( section ) ),
      hana::make_pair( hana::llong_c< static_cast< long long >( sections.sectionNumber() ) >, std::ref( sections ) )... );

  auto get = [&]( auto index ) {

    auto makeFull = [&] ( auto ) { 
      return 
        hana::make_pair
        ( index, std::make_optional( std::move( map[index].get() ) ) );
    };

    auto makeEmpty = [&] ( auto ) { 
      return
        hana::make_pair
        ( index, std::optional< section::Type< 7, index.value > >{} ); 
    };

    return hana::eval_if( hana::contains( map, index ), makeFull, makeEmpty );
  };

  return hana::unpack( optionalSections(), [&]( auto... indices ) {
      return hana::make_map( get(indices)... );
    } );
}
