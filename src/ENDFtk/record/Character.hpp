template< int w >
struct Character{
  static constexpr std::size_t width = w;
  using Type = std::string;
  using Parser = disco::Character< width >;

  static constexpr const Type& defaultValue = helper::defaultString< w >;
};
