/**
 *  @brief Return the angular distributions
 *
 *  This function returns the underlying angular distributions as reference
 *  wrappers to a variant. See the MixedDistributions unit test for more
 *  information on how to use this.
 */
auto angularDistributions() const {

  using SumType =
    std::variant< std::reference_wrapper< const LegendreCoefficients >,
                  std::reference_wrapper< const TabulatedDistribution > >;

  auto lift = ranges::view::transform( []( const auto& element ) -> SumType {

    return std::cref( element );
  } );

  return ranges::view::concat( this->legendre().angularDistributions() | lift,
                               this->tabulated().angularDistributions() | lift );
}
