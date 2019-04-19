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
      return section::Type< 8, SectionNo >( head, begin, end, lineNumber, MAT );
    } catch( std::exception& e ) {
      Log::info( "Error while reading File 7 Section {}", SectionNo );
      throw e;
    }
  }();

  try{
    structureDivision = StructureDivision( begin, end, lineNumber );
  } catch( std::exception& e ) {
    Log::info( "Error while reading structure division following File 7 Section {}",
               SectionNo );
    throw e;
  }

  return section;
}

template< long long MT, typename... Args >
static auto
read( hana::llong< MT > sectionNo,
      StructureDivision& structureDivision,
      Args&&... args ){
  auto& head = asHead( structureDivision );
  return head.MT() == sectionNo ?
    std::make_optional( read( sectionNo, head, structureDivision,
                              std::forward<Args>(args)... ) ) :
    std::nullopt;
}

template< typename... SectionNos, typename... Args >
static auto
read( hana::tuple< SectionNos... > sectionNos, Args&&... args ) {
  auto readPair_fn = [&]( auto&& sectionNo ){
    return hana::make_pair
           ( sectionNo, read( sectionNo, std::forward<Args>(args)... ) );
  };

  auto pack_fn = [&]( auto&&... pairs ){
    return hana::make_tuple( std::move(pairs)... );
  };

  auto append_fn = [&]( auto&& tuple, auto&& sectionNo ){
    return hana::unpack( tuple,
                         [&]( auto&&... pairs )
                         { return pack_fn( pairs...,
                                           readPair_fn( sectionNo ) ); } );
  };

  return hana::unpack( hana::fold( sectionNos, hana::make_tuple(), append_fn ),
                       []( auto&&... args )
                       { return hana::make_map( std::move(args)... ); } );

}
