namespace ENDFtk {
namespace implementation {
namespace record {

template< int w >
struct Integer{
  static constexpr std::size_t width = w;
  using Type = long;
  using Parser = disco::Integer< width >;

  static constexpr Type defaultValue = 0;
};

}
}
}
