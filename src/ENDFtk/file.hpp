namespace file{

template< int MF >
class Type {
public:
  /* convenience typedefs */
  using Section = section::Type< MF >;

  /* fields */
  std::vector< Section > sectionVector;
  std::unordered_map< int, Section& > sectionMap;

  /* methods */
#include "ENDFtk/file/Type/src/ctor.hpp"
};

/* MF1 has a limited number of possible sections */
template< 1 >
class Type {

    /* fields */
  section::Type< 1 >::DataType< 451 > mt451_;                   // MT451 descriptive data
//  std::optional< section::Type< 1 >::DataType< 452 > > mt452_;  // MT452 nubar data
//  std::optional< section::Type< 1 >::DataType< 455 > > mt455_;  // MT455 delayed nubar data
//  std::optional< section::Type< 1 >::DataType< 456 > > mt456_;  // MT456 prompt data
  std::optional< section::Type< 1 >::DataType< 458 > > mt458_;  // MT458 fission Q value data
//  std::optional< section::Type< 1 >::DataType< 460 > > mt460;  // MT460 delayed photon data

public:

  /* constructors */
#include "ENDFtk/file/Type/src/ctor-1.hpp"

  /* set methods */

  /* get methods */
  const section::Type< 1 >::DataType< 451 >& MT451() const { return this->MT451_; }
  const section::Type< 1 >::DataType< 458 >& MT458() const { return this->MT458_.value(); }
};

}
