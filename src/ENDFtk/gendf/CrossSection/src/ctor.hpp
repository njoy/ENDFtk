public:

/*
  CrossSection( double ZA, double AWR, int MT,
                int NL, int NZ, int LRFLAG, int NGN,
                std::vector< double > fluxes,
                std::vector< double > cross_sections ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN,
                 makeRecords( fluxes, cross_sections, NL, NZ ) ) {}

  CrossSection( double ZA, double AWR, int MT,
                int NL, int NZ, int LRFLAG, int NGN,
                std::vector< std::vector< std::vector< double > > > fluxes,
                std::vector< std::vector< std::vector< double > > > cross_sections ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN,
                 makeRecords( fluxes, cross_sections ) ) {}

  CrossSection( double ZA, double AWR, int MT,
                int NZ, int LRFLAG, int NGN,
                std::vector< double > fluxes,
                std::vector< double > cross_sections ) :
    SectionBase( ZA, AWR, MT, NL, NZ, LRFLAG, NGN,
                 makeRecords( fluxes, cross_sections, NZ ) ) {}

  CrossSection( double ZA, double AWR, int MT,
                int NZ, int LRFLAG, int NGN,
                std::vector< std::vector< double > > fluxes,
                std::vector< std::vector< double > > cross_sections ) :
    SectionBase( ZA, AWR, MT, 1, NZ, LRFLAG, NGN,
                 makeRecords( fluxes, cross_sections ) ) {}
*/

  /**
   *  @brief Constructor from buffer
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] begin        the iterator for begin
   *  @param[in] end          the iterator for end
   */
  template< typename Iterator >
  CrossSection( const HEAD& head,
               Iterator& begin,
               const Iterator& end ) :
    SectionBase( head, begin, end ) {}
