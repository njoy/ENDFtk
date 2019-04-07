SubSection( SubSectionVariant&& subsection ) :
  data_( std::move( subsection ) ) {}

SubSection( LegendreCoefficients&& subsection ) :
  data_( std::move( subsection ) ) {}

SubSection( KalbachMann&& subsection ) :
  data_( std::move( subsection ) ) {}

SubSection( Tabulated&& subsection ) :
  data_( std::move( subsection ) ) {}

