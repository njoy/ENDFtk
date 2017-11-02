class Material {
protected:
  static constexpr auto files = /*     required? | fileNumber */
    hana::make_tuple( hana::make_pair(   true_c,      1_c),
		      hana::make_pair(   true_c,      2_c),
		      hana::make_pair(   true_c,      3_c),
		      hana::make_pair(   false_c,     4_c),
		      hana::make_pair(   false_c,     5_c),
		      hana::make_pair(   false_c,     6_c),
		      hana::make_pair(   false_c,     7_c),
		      hana::make_pair(   false_c,     8_c),
		      hana::make_pair(   false_c,     9_c),
		      hana::make_pair(   false_c,     10_c),
		      hana::make_pair(   false_c,     12_c),
		      hana::make_pair(   false_c,     13_c),
		      hana::make_pair(   false_c,     14_c),
		      hana::make_pair(   false_c,     15_c),
		      hana::make_pair(   false_c,     23_c),
		      hana::make_pair(   false_c,     26_c),
		      hana::make_pair(   false_c,     27_c),
		      hana::make_pair(   false_c,     28_c),
		      hana::make_pair(   false_c,     30_c),
		      hana::make_pair(   false_c,     31_c),
		      hana::make_pair(   false_c,     32_c),
		      hana::make_pair(   false_c,     33_c),
		      hana::make_pair(   false_c,     34_c),
		      hana::make_pair(   false_c,     35_c),
		      hana::make_pair(   false_c,     40_c) );


  #include "ENDFtk/Material/src/get.hpp"
  #include "ENDFtk/Material/src/read.hpp"
  #include "ENDFtk/Material/src/fill.hpp"

  using Map = decltype( read( std::declval< StructureDivision& >(),
			      std::declval< std::string::iterator& >(),
			      std::declval< const std::string::iterator& >(),
			      std::declval< long& >(),
			      std::declval< int >() ) );
  
  Map fileMap;
  int MAT_;

public:
  #include "ENDFtk/Material/src/ctor.hpp"
  #include "ENDFtk/Material/src/fileNumber.hpp"

  template< typename Index >
  decltype(auto)
  MF( Index fileNo ) const { return this->fileNumber( fileNo ); }

  template< typename Index >
  decltype(auto)
  MF( Index fileNo ) { return this->fileNumber( fileNo ); }

  #include "ENDFtk/Material/src/hasMF.hpp"

  bool
  hasFileNumber( int fileNo ) const { return this->hasMF( fileNo ); }

  int MAT() const { return this->MAT_; }
  int materialNumber() const { return this->MAT(); }
};
