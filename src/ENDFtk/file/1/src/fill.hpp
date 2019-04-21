template< typename... Sections >
static Map
fill( section::Type< 1, 451 >&& section451, Sections&&... sections ) {

  auto map =
    hana::make_map
    ( // using std::decay_t<decltype(sections)>:: instead of sections.sectionNumber() to overcome clang compiler issue/bug
      hana::make_pair( hana::llong_c< static_cast< long long >( std::decay_t<decltype(sections)>::sectionNumber() ) >, std::ref( sections ) )... );

  auto makeFull = [&map] ( hana::true_, auto index ) {
    return
    hana::make_pair
    ( index, std::make_optional( std::move( map[index].get() ) ) );
  };

  auto makeEmpty = [] ( hana::false_,  auto index ) {

    using Section = section::Type< 1, index.value >;
    return hana::make_pair( index, std::optional< Section >{} );
  };

  auto makePair = hana::overload( makeFull, makeEmpty );

  auto get = [&makePair, &map] ( auto index ) {

    return makePair( hana::contains( map, index ), index);
  };

  return hana::unpack( optionalSections(),
                       [&] ( auto... indices )
                           { return hana::make_map(
                              hana::make_pair( 451_c, std::move( section451 ) ),
                              get( indices )... ); } );
}

