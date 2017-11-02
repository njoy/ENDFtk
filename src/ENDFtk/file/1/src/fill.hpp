template< typename Int, typename Map >
static auto fill_( hana::true_, Int sectionNo, Map& map ){
  static_assert
    ( hana::contains( map, sectionNo ),
      "Required section missing from file::Type<1> constructor call" );
  return hana::make_pair( sectionNo, std::move( map[ sectionNo ].get() ) );
}

template< typename Int, typename Map >
static auto fill_( hana::false_, Int sectionNo, Map& map ){
  return
    hana::make_pair
    ( index, hana::contains( map, sectionNo ) ?
             std::make_optional( std::move( map[ sectionNo ].get() ) ) :
             std::nullopt );
}

template< typename Pair, typename Map >
static auto fill_( Pair&& p, Map& map ){
  return fill_( hana::first( std::forward< Pair >( p ) ),
		hana::second( std::forward< Pair >( p ) ), map );
}

template< typename... Sections >
static Map
fill( Sections&&... args ) const {
  auto map =
    hana::make_map
    ( hana::make_pair( hana::llong_c< args.MT() >, std::ref( args ) )... );

  return hana::unpack( sections, [&]( auto&&... pairs ){
      return hana::make_map
	( fill_( std::forward< decltype( pairs ) >( pairs ), map )... ); } );
}

