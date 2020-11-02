template< int MF, typename... Files >
static auto
fill( file::Type< MF >&& file, Files&&... files ) {

  {
    constexpr auto fileNumbers =
      decltype
      ( hana::make_tuple( details::fileOf( file ),
                          details::fileOf( files )... ) ){};

    constexpr auto isLValue = hana::trait< std::is_lvalue_reference >;
    auto types = hana::make_tuple( hana::type_c< Files >... );
    static_assert( hana::none_of( types, isLValue ),
                   "Constructing a Material with file::Type arguments "
                   "that are lvalue references is not allowed" );

    constexpr auto isInArguments = hana::partial( hana::contains, fileNumbers );

    static_assert( hana::all_of( Material::requiredFiles(), isInArguments ),
                   "Not all required files are present" );
  }

  auto content =
    hana::make_map
    ( hana::make_pair( details::fileOf( file ), std::ref( file ) ),
      hana::make_pair( details::fileOf( files ), std::ref( files ) )... );

  auto makeFull = [ &content ] ( hana::true_, auto index ) {

    const auto makeRequiredPair = [&] ( hana::true_, auto&& file ) {

      return hana::make_pair( index, std::move( file ) );
    };
    const auto makeOptionalPair = [&] ( hana::false_, auto&& file ) {

      return hana::make_pair( index,
                              std::make_optional( std::move( file ) ) );
    };

    auto makePair = hana::overload( makeRequiredPair, makeOptionalPair );

    return makePair( hana::contains( Material::requiredFiles(), index ),
                     std::move( content[ index ].get() ) );
  };

  auto makeEmpty = [] ( hana::false_,  auto index ) {

    using Section = section::Type< MF, index.value >;
    return hana::make_pair( index, std::optional< Section >{} );
  };

  auto makePair = hana::overload( makeFull, makeEmpty );

  auto get = [ &makePair, &content ] ( auto index ) {

    return makePair( hana::contains( content, index ), index);
  };

  return hana::unpack( Material::files(),
                       [&] ( auto... indices )
                           { return hana::make_map( get( indices )... ); } );
}
