template< long long FileNo, typename BufferIterator >
static auto
read( hana::llong< FileNo >,
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber ) {

  auto file = [&] {

    try{

      return file::Type< FileNo >( structureDivision, begin, end, lineNumber );
    }
		catch( std::exception& e ) {

      Log::info( "Error while reading File {}", FileNo );
      throw e;
    }
  }();

  try {

    structureDivision = StructureDivision( begin, end, lineNumber );
  }
	catch( std::exception& e ) {

    Log::info( "Error while reading structure division following File {}",
               FileNo );
    throw e;
  }

  return file;
}

template< typename... FileNos, typename... Args >
static auto
read( hana::tuple< FileNos... > fileNos,
      StructureDivision& structureDivision, Args&&... args ) {

  // compiler issue in gcc 6.4.0: need to capture the capture the actual
  // arguments because the compiler gets confused (leads to segmentation fault)
  // final failure is in disco when reading whitespace
  // required for this lambda and the next one
  auto readRequiredPair =
  [ &structureDivision,
    &begin = hana::arg<1>( args... ),
    end = std::cref( hana::arg<2>( args... ) ),
    lineNumber = std::ref( hana::arg<3>( args... ) ) ]
  ( hana::true_, hana::false_, auto fileNo ) {

    if ( structureDivision.tail.MF() != fileNo ) {

      Log::info( "Error while reading material {}", structureDivision.tail.MAT() );
      Log::info( "Expected MF: {}", fileNo );
      Log::info( "Found MF: {}", structureDivision.tail.MF() );
      throw std::exception();
    }

    return hana::make_pair( fileNo,
                            read( fileNo, structureDivision,
                                  begin, end.get(), lineNumber ) );
  };

  auto readOptionalPair =
  [ &structureDivision,
    &begin = hana::arg<1>( args... ),
    end = std::cref( hana::arg<2>( args... ) ),
    lineNumber = std::ref( hana::arg<3>( args... ) ) ]
  ( hana::false_, hana::true_, auto fileNo ) {

    auto makeOptional  = [&] () {

      return structureDivision.tail.MF() == fileNo ?
        std::make_optional( read( fileNo, structureDivision,
                                  begin, end.get(), lineNumber ) ) :
        std::optional< file::Type< fileNo.value > >{};
    };

    return hana::make_pair( fileNo, makeOptional() );
  };

  auto readUnimplementedPair =
  [ &structureDivision,
    &begin = hana::arg<1>( args... ),
    end = std::cref( hana::arg<2>( args... ) ),
    lineNumber = std::ref( hana::arg<3>( args... ) ) ]
  ( hana::false_, hana::false_, auto fileNo ) {

    while ( fileNo.value == structureDivision.tail.MF() ) {

      structureDivision = StructureDivision( begin, end.get(), lineNumber );
    }

    return hana::make_pair( fileNo,
                            std::optional< file::Type< fileNo.value > >{} );
  };

  auto readPair_fn = hana::overload( readRequiredPair,
                                     readOptionalPair,
                                     readUnimplementedPair );

  auto append_fn = [&]( auto&& tuple, auto&& fileNo ){
    return hana::unpack
           ( std::move( tuple ),
             [&] ( auto&&... pairs )
                 { return hana::make_tuple
                          ( std::move( pairs )... ,
                            readPair_fn( hana::contains(
                                           requiredFiles(),
                                           fileNo ),
                                         hana::contains(
                                           optionalFiles(),
                                           fileNo ),
 																				 fileNo ) ); } );
  };

  return hana::unpack( hana::fold( fileNos, hana::make_tuple(), append_fn ),
                       []( auto&&... args )
                       { return hana::make_map( std::move(args)... ); } );
}
