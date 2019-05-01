template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  // lambdas for verifying
  auto verifyLANG = [LANG] ( const auto& value ) -> bool
                           { return value.LANG() == LANG; };

  auto verify = sequence | ranges::view::transform( verifyLANG );

  auto iter = ranges::find_if_not( verify, hana::equal.to( true ) );

  if ( iter != ranges::end( verify ) ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={} for the subsection with index={}", LANG,
               std::distance( ranges::begin( verify ), iter ) );
    throw std::exception();
  }
}
