namespace ENDFtk {
namespace implementation {
namespace record {
namespace helper {

template< int w >
const std::string defaultString = defaultString< w - 1 > + " ";

template<>
const std::string defaultString< 0 > = "";

} // namespace helper

template< int w >
struct Character{
  static constexpr std::size_t width = w;
  using Type = std::string;
  using Parser = disco::Character< width >;

  static constexpr const Type& defaultValue = helper::defaultString< w >;
};

}
}
}
