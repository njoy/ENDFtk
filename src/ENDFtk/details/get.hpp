struct get_fn {

  template< typename T,
            std::enable_if_t< not isOptional< std::decay_t< T > >, bool > = true >
  decltype( auto ) operator()( T&& t ) const {

    return std::forward< T >( t );
  }

  template< typename T,
            std::enable_if_t< isOptional< std::decay_t< T > >, bool > = true >
  decltype(auto) operator()( T&& t ) const {

    return std::forward< T >( t ).value();
  }
};

constexpr const get_fn get{};
