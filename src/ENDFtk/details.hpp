#ifndef NJOY_ENDFTK_DETAILS
#define NJOY_ENDFTK_DETAILS

// system includes
#include <string>

// other includes
#include "boost/hana.hpp"

namespace njoy {
namespace ENDFtk {

  namespace hana = boost::hana;
  inline namespace literals {

  using namespace hana::literals;
  }

namespace details {

  template< int i >
  using index = hana::llong<static_cast<long long>(i)>;

  template< int i >
  constexpr const auto index_c = index< i >{};

  template< typename T >
  constexpr const bool isOptional = false;

  template< typename T >
  constexpr const bool isOptional< std::optional< T > > = true;

  #include "ENDFtk/details/get.hpp"

  #include "ENDFtk/details/fileOf.hpp"
  #include "ENDFtk/details/sectionOf.hpp"

} // details namespace
} // ENDFtk namespace
} // njoy namespace

#endif
