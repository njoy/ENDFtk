static std::vector< std::optional< BackgroundRMatrix > >
makeBackgroundMatrices( unsigned int NCH,
                        std::vector< BackgroundRMatrix >&& channels ) {

  std::vector< std::optional< BackgroundRMatrix > >
  background( NCH, std::nullopt );

  for ( auto&& rmatrix : channels ) {

    int LCH = std::visit( [] ( const auto& variant )
                             { return variant.LCH(); },
                          rmatrix );
    if ( ( LCH <= 0 ) || ( LCH > NCH ) ) {

      Log::error( "Encountered illegal LCH value" );
      Log::info( "LCH must be between 1 and NCH" );
      Log::info( "NCH value: {}", NCH );
      Log::info( "LCH value: {}", LCH );
      throw std::exception();
    }

    if ( background[ LCH - 1 ] ) {

      Log::error( "Encountered duplicate LCH value" );
      Log::info( "LCH value: {}", LCH );
      throw std::exception();
    }
    background[ LCH - 1 ] = std::move( rmatrix );
  }
  return background;
}
