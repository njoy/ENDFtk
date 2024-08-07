/**
 *  @brief Return the angular distributions (one for each incident energy)
 *
 *  This function returns the underlying angular distributions as a variant of
 *  reference wrappers. See the section::Type< 4 > unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  auto lift = ranges::cpp20::views::transform( []( const auto& element ) -> Variant {

    return std::cref( element );
  } );

  return std::visit(
           tools::overload{
               [] ( const Isotropic& ) -> VariantRange
                  { return ranges::cpp20::views::empty<Variant>; },
               [] ( const MixedDistributions& distributions ) -> VariantRange
                  { return distributions.angularDistributions(); },
               [&] ( const auto& distributions ) -> VariantRange
                   { return distributions.angularDistributions() | lift; } },
           this->distributions_ );
}
