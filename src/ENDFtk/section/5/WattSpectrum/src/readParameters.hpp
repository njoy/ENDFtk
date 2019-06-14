template< typename Iterator >
static std::array< Parameter, 2 >
readParameters( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) {

  auto makeParameter = [&] ( auto&& message ) {

    try {

      return Parameter( begin, end, lineNumber, MAT, MF, MT );
    }
    catch ( ... ) {

      Log::info( message );
      throw;
    }
  };

  auto a = makeParameter( "Encountered error while reading the a parameter" );
  auto b = makeParameter( "Encountered error while reading the b parameter" );
  return std::array< Parameter, 2 >{{ std::move( a) , std::move( b ) }};
}

