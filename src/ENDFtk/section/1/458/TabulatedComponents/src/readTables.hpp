template< typename Iterator >
static std::array< std::optional< EnergyReleaseComponent >, 9 >
readTables( Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT,
            int MF,
            int MT,
            int NFC ) {

  std::array< std::optional< EnergyReleaseComponent >, 9 > records = {

      std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
      std::nullopt, std::nullopt, std::nullopt, std::nullopt
    };

  if ( NFC < 0 ) {

    Log::error( "The number of tabulated energy release components NFC value "
                "cannot be negative" );
    Log::info( "NFC value: {}", NFC );
    throw std::exception();
  }

  while( NFC-- ) {

    EnergyReleaseComponent component(begin, end, lineNumber, MAT, MF, MT);
    if ( ( component.IFC() > 0 ) && ( component.IFC() < 10 ) ) {

      if ( ! records[ component.IFC() - 1 ] ) {

        records[ component.IFC() - 1 ] = std::move( component );
      }
      else {

        Log::error( "Encountered duplicate IFC value" );
        Log::info( "IFC value: {}", component.IFC() );
        Log::info( "Line number: {}", lineNumber - component.NC() );
        throw std::exception();
      }
    }
    else {

      Log::error( "Encountered illegal IFC value" );
      Log::info( "IFC must be between 1 and 9" );
      Log::info( "IFC value: {}", component.IFC() );
      Log::info( "Line number: {}", lineNumber - component.NC() );
      throw std::exception();
    }
  }

  return records;
}
