template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  auto lang = [LANG] ( const auto& value )
                     { return std::visit(
                                [LANG] ( const auto& variant )
                                       { return variant.LANG() == LANG; },
                                value ); };

  auto iter = std::find_if_not( sequence.begin(), sequence.end(),lang );

  if ( iter != sequence.end() ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={} for the subsection with index={}", LANG,
               std::distance( sequence.begin(), iter ) );
    throw std::exception();
  }
}
