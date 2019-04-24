namespace details {

template< int index >
constexpr const auto index_c = hana::llong_c<static_cast<long long>(index)>;

template< typename T >
constexpr const bool isOptional = false;

template< typename T >
constexpr const bool isOptional< std::optional< T > > = true;

#include "ENDFtk/file/details/src/fileOf.hpp"
#include "ENDFtk/file/details/src/sectionOf.hpp"
#include "ENDFtk/file/details/src/get.hpp"
}
