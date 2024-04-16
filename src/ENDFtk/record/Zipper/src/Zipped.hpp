template< typename... ENDFTypes  >
struct Zipped {
  static constexpr std::size_t
  tupleWidth = helper::sum< ENDFTypes::width... >();

  static_assert( tupleWidth < 66, "too many entries on line" );

  static constexpr std::size_t entriesPerTuple = sizeof...( ENDFTypes );
  static constexpr std::size_t tuplesPerRecord = 66 / tupleWidth;

  static constexpr std::size_t
  entriesPerRecord = tuplesPerRecord * entriesPerTuple;

  static const std::size_t nPad = 66 % tupleWidth;

  static constexpr auto tupleIndices =
    std::make_index_sequence< entriesPerTuple >();

  /**
   * @brief
   * This is dark magic to expand the parameter pack a number of times equal
   * to the tuplesPerRecord class variable
   */
  template< std::size_t... indices >
  static decltype(auto)
    expand( std::index_sequence< indices... > ){
    return njoy::tools::disco::Record
      < typename std::tuple_element
        < indices % entriesPerTuple,
          std::tuple< typename ENDFTypes::Parser... > >::type... ,
        njoy::tools::disco::Column< nPad >,
        njoy::tools::disco::RetainCarriage >();
  }

  using Format =
    decltype( expand( std::make_index_sequence< entriesPerRecord >() ) );

  template< std::size_t index >
  using Type =
    typename std::tuple_element
    < index, std::tuple< typename ENDFTypes::Type... > >::type;

  using TupleFormat =
    njoy::tools::disco::Record< typename ENDFTypes::Parser...,
                                njoy::tools::disco::RetainCarriage >;

  static const std::tuple< typename ENDFTypes::Type... >&
  defaultTuple(){
    static const auto defaultValues =
      std::make_tuple( ENDFTypes::defaultValue... );
    return defaultValues;
  }

};
