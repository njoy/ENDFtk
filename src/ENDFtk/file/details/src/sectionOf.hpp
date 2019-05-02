struct sectionOf_fn {

  template < int MF, int MT >
  constexpr auto operator()( const section::Type< MF, MT >& ) const {

    return index_c< MT >;
  }
};

constexpr const sectionOf_fn sectionOf{};

