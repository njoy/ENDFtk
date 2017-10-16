template< typename T >
static constexpr bool isOptional = false;

template< typename T >
static constexpr bool isOptional< std::optional<T> > = true;

template< typename T,
          std::enable_if_t< not isOptional< std::decay_t<T> >, bool > = true >
static decltype(auto) get( T&& t ){ return std::forward<T>(t); }

template< typename T,
          std::enable_if_t< isOptional< std::decay_t<T> >, bool > = true >
static decltype(auto) get( T&& t ){ return std::forward<T>(t).value(); }
