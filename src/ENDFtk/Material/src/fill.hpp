template< typename Int, typename Map >
static auto fill_( hana::true_, Int fileNo, Map& map ){
  static_assert( hana::contains( map, fileNo ),
		 "Required file missing from Material constructor call" );
  return hana::make_pair( fileNo, std::move( map[ fileNo ].get() ) );
}

template< typename Int, typename Map >
static auto fill_( hana::false_, Int fileNo, Map& map ){
  return
    hana::make_pair
    ( index, hana::contains( map, fileNo ) ?
             std::make_optional( std::move( map[ fileNo ].get() ) ) :
             std::nullopt );
}

template< typename Pair, typename Map >
static auto fill_( Pair&& p, Map& map ){
  return fill_( hana::first( std::forward< Pair >( p ) ),
		hana::second( std::forward< Pair >( p ) ), map );
}

template< typename... Files >
auto
static fill( Files&&... args ) const {
  auto map =
    hana::make_map
    ( hana::make_pair( hana::llong_c< args.MF() >, std::ref( args ) )... );

  return hana::unpack( files, [&]( auto&&... pairs ){
      return hana::make_map
	( fill_( std::forward< decltype( pairs ) >( pairs ), map )... ); } );
}

