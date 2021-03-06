template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  auto lang = [] ( const auto& variant )
                 { return std::visit( [] ( const auto& entry )
                                         { return entry.LANG(); },
                                      variant ); };

  auto iter = ranges::find_if_not( sequence, hana::equal.to( LANG ), lang );

  if ( iter != ranges::end( sequence ) ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={} for the subsection with index={}", LANG,
               ranges::distance( ranges::begin( sequence ), iter ) );
    throw std::exception();
  }
}
