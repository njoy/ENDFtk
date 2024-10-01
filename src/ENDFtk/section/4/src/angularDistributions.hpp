/**
 *  @brief Return the angular distributions (one for each incident energy)
 *
 *  This function returns the underlying angular distributions as a variant of
 *  reference wrappers. See the section::Type< 4 > unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  return std::visit(
           tools::overload{
               [] ( const Isotropic& ) -> VariantRange
                  { using namespace njoy::tools;
                    return std20::views::empty<Variant>; },
               [] ( const MixedDistributions& distributions ) -> VariantRange
                  { return distributions.angularDistributions(); },
               [&] ( const auto& distributions ) -> VariantRange
                   { using namespace njoy::tools;
                     return distributions.angularDistributions()
                            | std20::views::transform( [] ( auto&& element ) -> Variant
                                                          { return std::cref( element ); } ); } },
           this->distributions_ );
}
