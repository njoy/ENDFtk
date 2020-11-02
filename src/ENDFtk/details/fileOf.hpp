struct fileOf_fn {

  template < int MF, int... MT >
  constexpr auto operator()( const section::Type< MF, MT... >& ) const {

    return index_c< MF >;
  }

  template < int MF >
  constexpr auto operator()( const file::Type< MF >& ) const {

    return index_c< MF >;
  }
};

constexpr const fileOf_fn fileOf{};
