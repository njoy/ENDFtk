static void
verifyLAW( int multiplicityLAW, int distributionLaw ) {

  if ( multiplicityLAW != distributionLaw ) {
    Log::error( "Inconsistent LAW between multiplicity and distribution data" );
    Log::info( "Multiplicity LAW: {}", multiplicityLAW );
    Log::info( "Distribution LAW: {}", distributionLaw );
    throw std::exception();
  }
}
