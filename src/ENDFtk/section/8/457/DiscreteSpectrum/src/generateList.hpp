static std::vector< double >
generateList( double rtyp, double type,
              const std::tuple< double, double >& ri ) {

  return { rtyp, type, std::get< 0 >( ri ), std::get< 1 >( ri ) };
}

static std::vector< double >
generateList( double rtyp, double type,
              const std::tuple< double, double >& ri,
              const std::tuple< double, double >& ris ) {

  return { rtyp, type, std::get< 0 >( ri ), std::get< 1 >( ri ),
           std::get< 0 >( ris ), std::get< 1 >( ris ) };
}

static std::vector< double >
generateList( double rtyp, double type,
              const std::tuple< double, double >& ri,
              const std::tuple< double, double >& ris,
              const std::tuple< double, double >& ricc,
              const std::tuple< double, double >& rick,
              const std::tuple< double, double >& ricl ) {

  return { rtyp, type, std::get< 0 >( ri ), std::get< 1 >( ri ),
           std::get< 0 >( ris ), std::get< 1 >( ris ),
           std::get< 0 >( ricc ), std::get< 1 >( ricc ),
           std::get< 0 >( rick ), std::get< 1 >( rick ),
           std::get< 0 >( ricl ), std::get< 1 >( ricl ) };
}
