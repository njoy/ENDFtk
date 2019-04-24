namespace details {

template< typename T >
static constexpr bool isOptional = false;

template< typename T >
static constexpr bool isOptional< std::optional< T > > = true;

#include "ENDFtk/file/details/src/get.hpp"
}
