LaboratoryAngleEnergy(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< EnergyOutgoingCosineDistribution >&& energies ) :
  data_( InterpolationRecord( 0.0, 0.0, 0, 0,
                              std::move( boundaries ),
                              std::move( interpolants ) ),
                              std::move( energies ) ) {};

template< typename Iterator >
LaboratoryAngleEnergy( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT ) :
  data_( begin, end, lineNumber, MAT, MF, MT  ) {}

