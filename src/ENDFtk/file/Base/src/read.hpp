template< long long SectionNo, typename BufferIterator >
static auto
read( hana::llong< SectionNo >,
      HeadRecord& head,
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT ) {

  auto section = [&] {

    try {

      return section::Type< Derived::MF(), SectionNo >( head, begin, end,
                                                        lineNumber, MAT );
    }
    catch( std::exception& e ) {

      Log::info( "Error while reading File {} Section {}", Derived::MF(), SectionNo );
      throw e;
    }
  }();

  try {

    structureDivision = StructureDivision( begin, end, lineNumber );
  }
  catch( std::exception& e ) {

    Log::info( "Error while reading structure division following File {} Section {}",
               Derived::MF(), SectionNo );
    throw e;
  }

  return section;
}

template< typename... SectionNos, typename... Args >
static auto
read( hana::tuple< SectionNos... > sectionNos,
      StructureDivision& structureDivision, Args&&... args ) {

  // compiler issue in gcc 6.4.0: need to capture the capture the actual
  // arguments because the compiler gets confused (leads to segmentation fault)
  // final failure is in disco when reading whitespace
  // required for this lambda and the next one
  auto readRequiredPair =
  [&structureDivision,
   &begin = hana::arg<1>( args... ),
   end = std::cref( hana::arg<2>( args... ) ),
   lineNumber = std::ref( hana::arg<3>( args... ) ),
   MAT = hana::arg<4>( args... ) ] ( hana::true_, hana::false_, auto sectionNo ) {

    auto& head = asHead( structureDivision );
    if ( head.MT() != sectionNo ) {

      Log::info( "Error while reading section from File {}", Derived::MF() );
      Log::info( "Expected MT: {}", sectionNo );
      Log::info( "Found MT: {}", head.MT() );
      throw std::exception();
    }

    return hana::make_pair( sectionNo,
                            read( sectionNo, head, structureDivision,
                                  begin, end.get(), lineNumber, MAT ) );
  };

  auto readOptionalPair =
  [&structureDivision,
   &begin = hana::arg<1>( args... ),
   end = std::cref( hana::arg<2>( args... ) ),
   lineNumber = std::ref( hana::arg<3>( args... ) ),
   MAT = hana::arg<4>( args... ) ] ( hana::false_, hana::true_, auto sectionNo ) {

    auto makeOptional  = [&] () {

      auto& head = asHead( structureDivision );
      return head.MT() == sectionNo ?
        std::make_optional( read( sectionNo, head, structureDivision,
                                  begin, end.get(), lineNumber, MAT ) ) :
        std::optional< section::Type< Derived::MF(), sectionNo.value > >{};
    };

    return hana::make_pair( sectionNo, makeOptional() );
  };

  auto readUnimplementedPair =
  [&structureDivision,
   &begin = hana::arg<1>( args... ),
   end = std::cref( hana::arg<2>( args... ) ),
   lineNumber = std::ref( hana::arg<3>( args... ) ),
   MAT = hana::arg<4>( args... ) ] ( hana::false_, hana::false_, auto sectionNo ) {

    auto& head = asHead( structureDivision );
    if ( head.MT() == sectionNo ) {

      read( sectionNo, head, structureDivision,
            begin, end.get(), lineNumber, MAT );
    }

    return hana::make_pair( sectionNo,
                            std::optional< section::Type< Derived::MF(),
                                                          sectionNo.value > >{} );
  };

  auto readPair_fn = hana::overload( readRequiredPair,
                                     readOptionalPair,
                                     readUnimplementedPair );

  auto append_fn = [&]( auto&& tuple, auto&& sectionNo ){
    return hana::unpack
           ( std::move( tuple ),
             [&] ( auto&&... pairs )
                 { return hana::make_tuple
                          ( std::move( pairs )... ,
                            readPair_fn( hana::contains (
                                           Derived::requiredSections(),
                                           sectionNo ),
                                         hana::contains (
                                           Derived::optionalSections(),
                                           sectionNo ),
                                         sectionNo ) ); } );
  };

  return hana::unpack( hana::fold( sectionNos, hana::make_tuple(), append_fn ),
                       []( auto&&... args )
                       { return hana::make_map( std::move(args)... ); } );
}
