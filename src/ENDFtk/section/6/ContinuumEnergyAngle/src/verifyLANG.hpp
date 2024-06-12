template< typename Array >
static void
verifyLANG( int LANG, const Array& sequence ) {

  auto compare = [LANG] ( const auto& variant )
                        { return std::visit( [] ( const auto& entry )
                                                { return entry.LANG(); },
                                             variant ) == LANG; };

  auto iter = std::find_if_not( sequence.begin(), sequence.end(), compare );

  if ( iter != sequence.end() ) {

    Log::error( "All subsections must use the same LANG format option" );
    Log::info( "Expected LANG={} for the subsection with index={}", LANG,
               ranges::cpp20::distance( sequence.begin(), iter ) );
    throw std::exception();
  }
}
