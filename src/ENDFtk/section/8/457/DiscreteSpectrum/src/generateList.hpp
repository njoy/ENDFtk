static std::vector< double >
generateList( double rtyp, double type,
              const std::array< double, 2 >& ri ) {

  return { rtyp, type, ri[0], ri[1] };
}

static std::vector< double >
generateList( double rtyp, double type,
              const std::array< double, 2 >& ri,
              const std::array< double, 2 >& ris ) {

  return { rtyp, type, ri[0], ri[1], ris[0], ris[1] };
}

static std::vector< double >
generateList( double rtyp, double type,
              const std::array< double, 2 >& ri,
              const std::array< double, 2 >& ris,
              const std::array< double, 2 >& ricc,
              const std::array< double, 2 >& rick,
              const std::array< double, 2 >& ricl ) {

  return { rtyp, type, ri[0], ri[1], ris[0], ris[1],
           ricc[0], ricc[1], rick[0], rick[1], ricl[0], ricl[1] };
}
