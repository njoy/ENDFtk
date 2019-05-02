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
}
