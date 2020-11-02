template< int MF, int MT, typename... Sections >
static auto
fill( section::Type< MF, MT >&& section, Sections&&... sections ) {

  {
    constexpr auto fileNumbers =
      decltype
      ( hana::make_tuple( njoy::ENDFtk::details::fileOf( section ),
                          njoy::ENDFtk::details::fileOf( sections )... ) ){};
    constexpr auto compare =
      hana::equal.to( njoy::ENDFtk::details::index_c< Derived::MF() > );
    static_assert( hana::all_of( fileNumbers, compare ),
                   "Constructing a file::Type with section::Type arguments "
                   "that have a different MF number is not allowed" );

    constexpr auto isLValue = hana::trait< std::is_lvalue_reference >;
    auto types = hana::make_tuple( hana::type_c< Sections >... );
    static_assert( hana::none_of( types, isLValue ),
                   "Constructing a file::Type with section::Type arguments "
                   "that are lvalue references is not allowed" );

    constexpr auto sectionNumbers =
      decltype
      ( hana::make_set( njoy::ENDFtk::details::sectionOf( section ),
                        njoy::ENDFtk::details::sectionOf( sections )... ) ){};
    constexpr auto isInArguments = hana::partial( hana::contains, sectionNumbers );

    static_assert( hana::all_of( Derived::requiredSections(), isInArguments ),
                   "Not all required sections are present" );
  }

  auto content =
    hana::make_map
    ( hana::make_pair( njoy::ENDFtk::details::sectionOf( section ),
                       std::ref( section ) ),
      hana::make_pair( njoy::ENDFtk::details::sectionOf( sections ),
                       std::ref( sections ) )... );

  auto makeFull = [ &content ] ( hana::true_, auto index ) {

    const auto makeRequiredPair = [&] ( hana::true_, auto&& section ) {

      return hana::make_pair( index, std::move( section ) );
    };
    const auto makeOptionalPair = [&] ( hana::false_, auto&& section ) {

      return hana::make_pair( index,
                              std::make_optional( std::move( section ) ) );
    };

    auto makePair = hana::overload( makeRequiredPair, makeOptionalPair );

    return makePair( hana::contains( Derived::requiredSections(), index ),
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

  return hana::unpack( Derived::sections(),
                       [&] ( auto... indices )
                           { return hana::make_map( get( indices )... ); } );
}
