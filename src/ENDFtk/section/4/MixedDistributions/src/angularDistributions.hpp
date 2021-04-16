/**
 *  @brief Return the angular distributions (one for each incident energy)
 *
 *  This function returns the underlying angular distributions as a variant
 *  of reference wrappers. See the MixedDistributions unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  auto lift = ranges::cpp20::views::transform( []( const auto& element ) -> Variant {

    return std::cref( element );
  } );

  return ranges::views::concat( this->legendre().angularDistributions() | lift,
                                this->tabulated().angularDistributions() | lift );
}
