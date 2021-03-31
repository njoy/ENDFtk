static std::array< std::optional< EnergyReleaseComponent >, 9 >
generateTables( std::vector< EnergyReleaseComponent >&& tables ) {

  std::array< std::optional< EnergyReleaseComponent >, 9 > records = {

    std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
    std::nullopt, std::nullopt, std::nullopt, std::nullopt
  };

  if ( tables.size() == 0 ) {

    Log::error( "No tabulated energy release components are given" );
    throw std::exception();
  }

  for ( auto&& component : tables ) {

    if ( ( component.IFC() > 0 ) && ( component.IFC() < 10 ) ) {

      if ( ! records[ component.IFC() - 1 ] ) {

        records[ component.IFC() - 1 ] = std::move( component );
      }
      else {

        Log::error( "Encountered duplicate IFC value" );
        Log::info( "IFC value: {}", component.IFC() );
        throw std::exception();
      }
    }
    else {

      Log::error( "Encountered illegal IFC value" );
      Log::info( "IFC must be between 1 and 9" );
      Log::info( "IFC value: {}", component.IFC() );
      throw std::exception();
    }
  }

  return records;
}
