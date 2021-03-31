#ifndef NJOY_ENDFTK_DETAILS
#define NJOY_ENDFTK_DETAILS

// system includes
#include <string>

// other includes
#include "boost/hana.hpp"

namespace njoy {
namespace ENDFtk {

  // hana namespace declaration inside ENDFtk
  namespace hana = boost::hana;
  inline namespace literals { using namespace hana::literals; }

  // forward declarations
  namespace section { template< int MF, int... OptionalMT > class Type; }
  namespace file { template< int MF > class Type; }

namespace details {

  template< int i >
  using index = hana::llong<static_cast<long long>(i)>;

  template< int i >
  constexpr const auto index_c = index< i >{};

  /* components for detecting std::optional types */
  template< typename T >
  constexpr const bool isOptional = false;

  template< typename T >
  constexpr const bool isOptional< std::optional< T > > = true;

  /* material and file mapping components */
  struct RequiredFilePairType {

    template < typename Index >
    constexpr auto operator()( Index ) const {
      return hana::type_c<
                 hana::pair< Index,
                             file::Type< Index::value > > >;
    }
  };

  struct OptionalFilePairType {

    template< typename Index >
    constexpr auto operator()( Index ) const {
      return hana::type_c<
                 hana::pair< Index,
                             std::optional< file::Type< Index::value > > > >;
    }
  };

  template< int MF >
  struct RequiredSectionPairType {

    template< typename Index >
    constexpr auto operator()( Index ) const {
      return hana::type_c<
                 hana::pair< Index,
                             section::Type< MF, Index::value >>>;
    }
  };

  template< int MF >
  struct OptionalSectionPairType {

    template< typename Index >
    constexpr auto operator()( Index ) const {
      return hana::type_c <
                 hana::pair< Index,
                             std::optional< section::Type< MF, Index::value > > > >;
    }
  };

  struct MapType {

    template< typename... Pairs >
    constexpr auto operator()( Pairs... ) const {

      using Map_t = decltype( hana::make_map( std::declval< typename Pairs::type >()... ) );
      return hana::type_c< Map_t >;
    }
  };

  /* auxiliary functions */
  #include "ENDFtk/details/get.hpp"
  #include "ENDFtk/details/fileOf.hpp"
  #include "ENDFtk/details/sectionOf.hpp"
  #include "ENDFtk/details/deduceMapType.hpp"

} // details namespace
} // ENDFtk namespace
} // njoy namespace

#endif
