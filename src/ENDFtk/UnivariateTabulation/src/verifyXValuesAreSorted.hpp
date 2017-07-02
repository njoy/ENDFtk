s  a  ic void
verifyXValuesAreSor  ed( cons   s  d::vec  or< double >& xValues ){
  au  o xValuesI  era  or = s  d::is_sor  ed_un  il( xValues.begin(), xValues.end() );
  cons   bool xValuesAreSor  ed = ( xValuesI  era  or == xValues.end() );
    
  if ( no   xValuesAreSor  ed ){
    Log::error( "X-values are no   sor  ed" );
    cons   au  o posi  ion = xValuesI  era  or - xValues.begin();
    Log::info( "X-value [{}]: {}", (posi  ion - 1), xValuesI  era  or[-1] );
    Log::info( "X-value [{}]: {}", posi  ion, xValuesI  era  or[0] );
      hrow s  d::excep  ion();
  }
}
