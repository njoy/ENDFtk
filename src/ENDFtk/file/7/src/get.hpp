template< typename T >
struct isOptional_t {
  static constexpr bool value = false;
};

template< typename T >
struct isOptional_t< std::optional< T > > {
  static constexpr bool value = true;
};

template< typename T >
static constexpr bool isOptional = isOptional_t< T >::value;

template< typename T,
          std::enable_if_t< not isOptional< std::decay_t< T > >, bool > = true >
static decltype(auto) get( T&& t ){ return std::forward< T >(t); }

template< typename T,
          std::enable_if_t< isOptional< std::decay_t< T > >, bool > = true >
static decltype(auto) get( T&& t ){ return std::forward< T >( t ).value(); }
