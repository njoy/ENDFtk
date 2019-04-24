template < typename Derived >
class Base {

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

  static constexpr auto sections(){
    return hana::sort(hana::concat(Derived::requiredSections(),
                                   Derived::optionalSections()));
  }

public:

  /* get methods */

  /**
   *  @brief Return the MF number of the file
   */
  constexpr int MF() const {

    return static_cast< const Derived* >( this )->fileNumber();
  }

  /**
   *  @brief Verify if a given section (defined by the MT number) is defined
   *
   *  @param mt   the MT number of the section to be verified
   */
  template< typename Index >
  constexpr bool hasMT( Index mt ) const {

    return static_cast< const Derived* >( this )->hasSection( mt );
  }

  /**
   *  @brief Retrieve a specific MT section
   *
   *  @param mt   the MT number of the section to be retrieved
   */
  template< typename Index >
  constexpr decltype( auto ) MT( Index sectionNo ) const {

    return static_cast< const Derived* >( this )->section( sectionNo );
  }

  /**
   *  @brief Retrieve a specific MT section
   *
   *  @param mt   the MT number of the section to be retrieved
   */
  template< typename Index > constexpr decltype( auto ) MT( Index sectionNo ) {

    return static_cast< const Derived* >( this )->section( sectionNo );
  }

  #include "ENDFtk/file/Base/src/section.hpp"
};

