/**
 *  @brief Return the angular distributions
 *
 *  This function returns the underlying angular distributions as a variant of
 *  reference wrappers. See the section::Type< 4 > unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  auto lift = ranges::view::transform( []( const auto& element ) -> Variant {

    return std::cref( element );
  } );

  return std::visit(
           utility::overload{
               [] ( const Isotropic& ) -> VariantRange
                  { return ranges::view::empty< Variant >(); },
               [] ( const MixedDistributions& distributions ) -> VariantRange
                  { return distributions.angularDistributions(); },
               [&] ( const auto& distributions ) -> VariantRange
                   { return distributions.angularDistributions() | lift; } },
           this->distributions_ );
}
