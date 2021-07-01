template< typename Array >
static void
verifyTemperatures( int NP, const Array& temperatures ) {

  auto iter = ranges::cpp20::find_if_not( temperatures, hana::equal.to( NP ),
                                          &ListRecord::NPL );

  if ( iter != ranges::cpp20::end( temperatures ) ) {

    Log::error( "All S(E,T) functions must have the same size" );
    Log::info( "Expected NP={} for the temperature with index={}", NP,
               ranges::cpp20::distance(
                   ranges::cpp20::begin( temperatures ), iter ) );
    throw std::exception();
  }
}
