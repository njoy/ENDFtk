#ifndef NJOY_ENDFTK_FILE_DETAILS
#define NJOY_ENDFTK_FILE_DETAILS

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

namespace file {
namespace details {

  template< int i >
  using index = hana::llong<static_cast<long long>(i)>;

  template< int i >
  constexpr const auto index_c = index<i>{};

  template< typename T >
  constexpr const bool isOptional = false;

  template< typename T >
  constexpr const bool isOptional< std::optional< T > > = true;

  #include "ENDFtk/file/details/src/fileOf.hpp"
  #include "ENDFtk/file/details/src/sectionOf.hpp"
  #include "ENDFtk/file/details/src/get.hpp"

} // details namespace
} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
