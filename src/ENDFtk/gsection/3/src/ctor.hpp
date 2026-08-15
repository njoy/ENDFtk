private:

/**
 *  @brief Private constructor
 *
 *  @param[in] mt       the section number
 *  @param[in] zaid     the ZAID identifier
 *  @param[in] awr      the atomic weight ratio
 *  @param[in] lr       the break-up identifier flag
 *  @param[in] temp     the temperature
 *  @param[in] groupr   the format flag
 *  @param[in] flux     the group-wise flux
 *  @param[in] sigma    the group-wise cross section
 *  @param[in] ratio    the group-wise ratios
 */
GType( int mt, int zaid, double awr, int lr, double temp, bool groupr,
       std::vector< std::vector< std::vector< double > > > flux,
       std::vector< std::vector< std::vector< double > > > sigma,
       std::vector< std::vector< std::vector< double > > > ratio ) :
    Base( zaid, awr, mt ),
    lr_( lr ),
    temp_( temp ),
    groupr_( groupr ),
    flux_( std::move( flux ) ),
    sigma_( std::move( sigma ) ),
    ratio_( std::move( ratio ) ) {

  verifySize( this->flux_, this->sigma_, this->ratio_ );
}

public:

/**
 *  @brief Constructor from parameters with ratio quantities
 *
 *  @param[in] mt       the section number
 *  @param[in] zaid     the ZAID identifier
 *  @param[in] awr      the atomic weight ratio
 *  @param[in] lr.      the break-up identifier flag
 *  @param[in] temp     the temperature
 *  @param[in] groups   the group indices
 *  @param[in] flux     the group-wise flux
 *  @param[in] sigma    the group-wise cross section
 *  @param[in] ratio    the group-wise ratios
 */
GType( int mt, int zaid, double awr, int lr, double temp,
       std::vector< std::vector< std::vector< double > > > flux,
       std::vector< std::vector< std::vector< double > > > sigma,
       std::vector< std::vector< std::vector< double > > > ratio ) :
    GType( mt, zaid, awr, lr, temp, true,
           std::move( flux ), std::move( sigma ), std::move( ratio ) ) {}

/**
 *  @brief Constructor from parameters without ratio quantities
 *
 *  @param[in] mt       the section number
 *  @param[in] zaid     the ZAID identifier
 *  @param[in] awr      the atomic weight ratio
 *  @param[in] lr.      the break-up identifier flag
 *  @param[in] temp     the temperature
 *  @param[in] groups   the group indices
 *  @param[in] flux     the group-wise flux
 *  @param[in] sigma    the group-wise cross section
 */
GType( int mt, int zaid, double awr, int lr, double temp,
       std::vector< std::vector< std::vector< double > > > flux,
       std::vector< std::vector< std::vector< double > > > sigma ) :
  GType( mt, zaid, awr, lr, temp,
         std::move( flux ), std::move( sigma ), {} ) {}

private:

/**
 *  @brief Constructor for an ERRORR formatted section
 *
 *  @param[in] mt              the section number
 *  @param[in] zaid            the ZAID identifier
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] crossSections   the group-wise cross sections
 *  @param[in] number          the number of groups
 */
GType( int mt, int zaid, double awr,
       std::size_t number,
       std::vector< double > crossSections ) :
    GType( mt, zaid, awr, 0,  0., false,
           { { std::vector< double >( number, 0. ) } },
           { { std::move( crossSections ) } },
           {} ) {}

public:

/**
 *  @brief Constructor for an ERRORR formatted section
 *
 *  @param[in] mt              the section number
 *  @param[in] zaid            the ZAID identifier
 *  @param[in] awr             the atomic weight ratio
 *  @param[in] crossSections   the group-wise cross sections
 */
GType( int mt, int zaid, double awr,
       std::vector< double > crossSections ) :
    GType( mt, zaid, awr, crossSections.size(), std::move( crossSections ) ) {}

/**
 *  @brief Constructor from buffer/string
 *
 *  @tparam Iterator        buffer iterator
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the start for the iterator
 *  @param[in] end          the end for the iterator
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template<typename Iterator>
GType(const HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT)
    try : Base( head.ZA(), head.AWR(), head.MT() ) {

        if ( head.N2() == 0 ) {

          // ERRORR format: the section body is a single list of NGN cross
          // sections at infinite dilution for Legendre order 0
          auto xs = record::Sequence::read< record::Real >(
                        head.N1(), begin, end, lineNumber,
                        head.MAT(), head.MF(), head.MT() );

          this->lr_ = 0;
          this->temp_ = 0.;
          this->groupr_ = false;
          this->flux_ = { { std::vector< double >( xs.size(), 0. ) } };
          this->sigma_ = { { std::move( xs ) } };
          this->ratio_ = {};
        }
        else {

          // GROUPR format: one data record per neutron group
          auto data = makeVectors(
                          readRecords( begin, end, lineNumber, head.MAT(),
                                       head.MF(), head.MT(), head.N2() ),
                          head.L1(), head.L2(), head.N2() );

          this->lr_ = head.N1();
          this->temp_ = std::move( std::get<0>( data ) );
          this->groupr_ = true;
          this->flux_ = std::move( std::get<1>( data ) );
          this->sigma_ = std::move( std::get<2>( data ) );
          this->ratio_ = std::move( std::get<3>( data ) );
        }

        verifySize( this->flux_, this->sigma_, this->ratio_ );
        this->readSEND(begin, end, lineNumber, MAT, head.MF());
    }
    catch(std::exception& e) {
        Log::info("Encountered error while reading section {} of file {} fo material {}"
                  " in GENDF file.", head.MT(), head.MF(), head.MAT());
        throw e;
    }
