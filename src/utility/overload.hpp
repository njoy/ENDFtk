#ifndef NJOY_UTILITY_OVERLOAD
#define NJOY_UTILITY_OVERLOAD

// system includes

// other includes

namespace njoy {
namespace utility {

  /**
   *  @brief Overload struct for collecting lambdas for std:: visit
   *
   *  For example:
   *
   *    auto value = std::visit(
   *        utility::overload{ [] ( const Foo& ) -> std::string
   *                              { return "Foo"; },
   *                           [] ( const Bar& )
   *                              { return "Bar"; } },
   *        variant );
   */
  template < class... Types > struct overload : Types... {

    using Types::operator()...;
  };
  template < class... Types > overload( Types... ) -> overload< Types... >;

} // utility namespace
} // njoy namespace

#endif
