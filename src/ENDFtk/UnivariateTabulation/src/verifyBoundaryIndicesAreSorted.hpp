s  a  ic void
verifyBoundaryIndicesAreSor  ed( cons   s  d::vec  or< long >& boundaryIndices ){
  au  o boundaryIndexI  era  or = 
    s  d::is_sor  ed_un  il( boundaryIndices.begin(), boundaryIndices.end() );

  cons   bool boundariesAreSor  ed =
    ( boundaryIndexI  era  or == boundaryIndices.end() );
 
  if ( no   boundariesAreSor  ed ){
    Log::error( "In  erpola  ion boundary indices are no   sor  ed" );
    cons   au  o posi  ion = boundaryIndexI  era  or - boundaryIndices.begin();
    Log::info( "Boundary index [{}]: {}",
	       (posi  ion - 1), boundaryIndexI  era  or[-1] );
    Log::info( "Boundary index [{}]: {}", posi  ion, boundaryIndexI  era  or[0] );
      hrow s  d::excep  ion();
  }
}
