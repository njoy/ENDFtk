static std::vector< PhotonDistribution >
makePhotonDistributions( std::vector< std::array< double, 2 > >&& isotropic,
                         std::vector< AnisotropicPhotonDistribution >&& anisotropic ) {

  std::vector< PhotonDistribution > sequence;
  sequence.reserve( isotropic.size() + anisotropic.size() );

  for ( unsigned int i = 0; i < isotropic.size(); ++i ) {

    sequence.emplace_back( IsotropicDiscretePhoton( isotropic[i][0],
                                                    isotropic[i][1] ) );
  }

  for ( unsigned int i = 0; i < anisotropic.size(); ++i ) {

    std::visit( [&sequence] ( auto&& alternative )
                            { sequence.emplace_back( std::move( alternative ) ); },
                 anisotropic[i] );
  }

  return sequence;
}
