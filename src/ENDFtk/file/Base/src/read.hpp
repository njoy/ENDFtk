template< long long SectionNo, typename BufferIterator >
static auto
read( hana::llong< SectionNo >,
      HeadRecord& head,
      StructureDivision& structureDivision,
      BufferIterator& begin,
      const BufferIterator& end,
      long& lineNumber,
      int MAT ) {

  auto section = [&]{
    try{
      return section::Type< Derived::MF(), SectionNo >( head, begin, end,
                                                      lineNumber, MAT );
    } catch( std::exception& e ) {
      Log::info( "Error while reading File {} Section {}", Derived::MF(), SectionNo );
      throw e;
    }
  }();

  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info( "Error while reading structure division following File {} Section {}",
               Derived::MF(), SectionNo );
    throw e;
  }

  return section;
}

template< typename... SectionNos, typename... Args >
static auto
read( hana::tuple< SectionNos... > sectionNos, StructureDivision& structureDivision, Args&&... args ) {

std::cout << "lineNumber=" << hana::arg<3>( args... ) << std::endl;
std::cout << "MAT=" << hana::arg<4>( args... ) << std::endl;

  auto readRequiredPair =
  [&] ( hana::true_, auto sectionNo ) {

    auto& head = asHead( structureDivision );
    if ( head.MT() != sectionNo ) {

      Log::info( "Error while reading section from File {}", Derived::MF() );
      Log::info( "Expected MT: {}", sectionNo );
      Log::info( "Found MT: {}", head.MT() );
      throw std::exception();
    }

    return hana::make_pair( sectionNo,
                            read( sectionNo, head, structureDivision,
                                  args... ) );
  };

  auto readOptionalPair =
  [&] ( hana::false_, auto sectionNo ) {

    auto makeOptional  = [&] () {

      auto& head = asHead( structureDivision );
      if ( head.MT() == sectionNo ) {
        auto result = read( sectionNo, head, structureDivision, args... );
        return std::make_optional( std::move(result) );
      }
      else {

        return std::optional< section::Type< Derived::MF(), sectionNo.value > >{};
      }
    };

    return hana::make_pair( sectionNo, makeOptional() );
  };

  auto readPair_fn = hana::overload( readRequiredPair, readOptionalPair );

  auto append_fn = [&]( auto&& tuple, auto&& sectionNo ){
    return hana::unpack( std::move( tuple ),
                         [&] ( auto&&... pairs )
                             { return hana::make_tuple(
                                        std::move( pairs )... ,
                                        readPair_fn( hana::contains( Derived::requiredSections(), sectionNo ), sectionNo ) ); } );
  };

  return hana::unpack( hana::fold( sectionNos, hana::make_tuple(), append_fn ),
                       []( auto&&... args )
                       { return hana::make_map( std::move(args)... ); } );
}

