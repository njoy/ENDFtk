/**
 *  @brief Return the angular distributions
 *
 *  This function returns the underlying angular distributions as a variant
 *  of reference wrappers. See the MixedDistributions unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  auto lift = ranges::view::transform( []( const auto& element ) -> Variant {

    return std::cref( element );
  } );

  return ranges::view::concat( this->legendre().angularDistributions() | lift,
                               this->tabulated().angularDistributions() | lift );
}
