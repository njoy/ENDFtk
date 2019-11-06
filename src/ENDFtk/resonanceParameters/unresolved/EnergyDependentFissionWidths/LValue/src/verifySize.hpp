static void
verifySize( unsigned int NE, const std::vector< JValue >& jvalues ) {

  auto iter = ranges::find_if_not( jvalues, hana::equal.to( NE ),
                                   &JValue::NE );

  if ( iter != ranges::end( jvalues ) ) {

    Log::error( "All fission width functions must have the same size" );
    Log::info( "Expected NE={} for the J value with index={}", NE,
               ranges::distance( ranges::begin( jvalues ), iter ) );
    throw std::exception();
  }
}
