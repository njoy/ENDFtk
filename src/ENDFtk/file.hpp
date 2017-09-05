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
template<>
class Type< 1 > {

    /* fields */
  section::Type< 1 >::DataType< 451 > mt451_;                   // MT451 descriptive data
  std::optional< section::Type< 1 >::DataType< 452 > > mt452_;  // MT452 nubar data
  std::optional< section::Type< 1 >::DataType< 455 > > mt455_;  // MT455 delayed nubar data
  std::optional< section::Type< 1 >::DataType< 456 > > mt456_;  // MT456 prompt data
  std::optional< section::Type< 1 >::DataType< 458 > > mt458_;  // MT458 fission Q value data
  std::optional< section::Type< 1 >::DataType< 460 > > mt460_;  // MT460 delayed photon data

  /* auxiliary functions */
#include "ENDFtk/file/Type/src/checkRedundant.hpp"

public:

  /* constructors */
#include "ENDFtk/file/Type/src/ctor-1.hpp"

  /* set methods */

  /* get methods */
  const section::Type< 1 >::DataType< 451 >& MT451() const { return this->mt451_; }
  const section::Type< 1 >::DataType< 452 >& MT452() const { return *mt452_; }
  const section::Type< 1 >::DataType< 455 >& MT455() const { return *mt455_; }
  const section::Type< 1 >::DataType< 456 >& MT456() const { return *mt456_; }
  const section::Type< 1 >::DataType< 458 >& MT458() const { return *mt458_; }
  const section::Type< 1 >::DataType< 460 >& MT460() const { return *mt460_; }
};

}
