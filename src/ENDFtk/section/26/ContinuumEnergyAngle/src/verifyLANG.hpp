template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  auto lang = [] ( const auto& entry )
                 { return entry.LANG(); };

  auto iter = ranges::cpp20::find_if_not( sequence, hana::equal.to( LANG ), lang );

  if ( iter != ranges::cpp20::end( sequence ) ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={} for the subsection with index={}", LANG,
               ranges::cpp20::distance(
                   ranges::cpp20::begin( sequence ), iter ) );
    throw std::exception();
  }
}
