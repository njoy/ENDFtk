template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  // lambdas for verifying
  auto verifyLANG = [LANG] ( const auto& value ) -> bool
                           { return value.LANG() == LANG; };
  auto sum = [] ( bool left, bool right ) -> bool
                { return left and right; };

  if ( ranges::accumulate(
         sequence | ranges::view::transform( verifyLANG ),
         true,
         sum ) == false ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={}", LANG );
    throw std::exception();
  }
}
