inline
bool isRedundant( int MT ){
  // Redunant MT numbers are taken from Table 14 in ENDF-102.
  static const std::array< int, 12 > redundantMTs{{
           1,        3,   4,
                                   16,       18,
                                        27,
         101,      103, 104, 105, 106, 107,
  }};

  return ranges::binary_search( redundantMTs, MT );
}
