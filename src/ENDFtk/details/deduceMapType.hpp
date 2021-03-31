template< typename Required, typename Optional >
static constexpr auto deduceMapType( Required required, Optional optional) {

  auto files = hana::sort( hana::concat( required, optional ) );
  const auto isRequired = hana::partial( hana::contains, required );
  const auto makeRequired = RequiredFilePairType{};
  const auto makeOptional = OptionalFilePairType{};
  const auto makePair =
    hana::demux( hana::if_ )( isRequired, makeRequired, makeOptional );
  const auto makeMap = MapType{};
  return hana::unpack( files, hana::on( makeMap, makePair ) );
}

template<typename MF, typename Required, typename Optional>
static constexpr auto deduceMapType( MF, Required required, Optional optional ) {

  auto sections = hana::sort( hana::concat( required, optional ) );
  const auto isRequired = hana::partial(hana::contains, required);
  const auto makeRequired = RequiredSectionPairType< MF::value >{};
  const auto makeOptional = OptionalSectionPairType< MF::value >{};
  const auto makePair =
    hana::demux( hana::if_ )( isRequired, makeRequired, makeOptional );
  const auto makeMap = MapType{};
  return hana::unpack(sections, hana::on(makeMap, makePair));
}
