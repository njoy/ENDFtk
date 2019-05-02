private:

  template<int MF>
  struct RequiredPairType {
    template<typename Index>
    constexpr auto operator()(Index) const {
      return hana::type_c<hana::pair
                         <Index, section::Type<MF, Index::value>>>;
    }
  };

  template<int MF>
  struct OptionalPairType {
    template<typename Index>
    constexpr auto operator()(Index) const {
      return hana::type_c
             <hana::pair
              <Index, std::optional<section::Type<MF, Index::value>>>>;
    }
  };

  struct MapType {
    template< typename... Pairs >
    constexpr auto operator()( Pairs... ) const {

      using Map_t = decltype(hana::make_map(std::declval<typename Pairs::type>()...));
      return hana::type_c< Map_t >;
    }
  };

protected:

  template<typename MF,
           typename Required,
           typename Optional>
  static constexpr auto deduceMapType(MF, Required required, Optional optional){
    auto sections = hana::sort(hana::concat(required, optional));
    const auto isRequired =
      hana::partial(hana::contains, required);
    const auto makeRequired = RequiredPairType<MF::value>{};
    const auto makeOptional = OptionalPairType<MF::value>{};
    const auto makePair =
      hana::demux(hana::if_)(isRequired, makeRequired, makeOptional);
    const auto makeMap = MapType{};
    return hana::unpack(sections, hana::on(makeMap, makePair));
  }

