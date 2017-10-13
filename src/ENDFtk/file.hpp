namespace file{

template< int MF >
class Type {
public:
  /* convenience typedefs */
  using Section = section::Type< MF >;
  using iterator = typename std::vector< Section >::iterator;
  using const_iterator = typename std::vector< Section >::const_iterator;

protected:
  /* fields */
  std::vector< Section > sectionVector;
  tsl::hopscotch_map< int, const Section* > sectionMap;

  /* methods */
#include "ENDFtk/file/Type/src/collectVector.hpp"
#include "ENDFtk/file/Type/src/collectMap.hpp"

public:
#include "ENDFtk/file/Type/src/ctor.hpp"
#include "ENDFtk/file/Type/src/sectionNumber.hpp"

  const Section&
  MT( int sectionNo ) const { return this->sectionNumber( sectionNo ); }
  Section&
  MT( int sectionNo ){ return this->sectionNumber( sectionNo ); }

  iterator begin() { return this->sectionVector.begin(); }
  iterator end() { return this->sectionVector.end(); }

  const_iterator begin() const { return const_cast< Type& >(*this).begin(); }
  const_iterator end() const { return const_cast< Type& >(*this).end(); }

  bool
  hasMT( int sectionNo ) const { return this->sectionMap.count( sectionNo ); }
  bool
  hasSectionNumber( int sectionNo ) const {  return this->hasMT( sectionNo ); }
};

/* MF1 has a limited number of possible sections */
template<>
class Type< 1 > {

    /* fields */
  section::Type< 1, 451 > mt451_;                   // MT451 descriptive data
//  std::optional< section::Type< 1, 452 > > mt452_;  // MT452 nubar data
//  std::optional< section::Type< 1, 455 > > mt455_;  // MT455 delayed nubar data
//  std::optional< section::Type< 1, 456 > > mt456_;  // MT456 prompt data
//  std::optional< section::Type< 1, 458 > > mt458_;  // MT458 fission Q value data
//  std::optional< section::Type< 1, 460 > > mt460_;  // MT460 delayed photon data

  /* auxiliary functions */
#include "ENDFtk/file/Type/src/checkRedundant.hpp"

public:

  /* constructors */
#include "ENDFtk/file/Type/src/ctor-1.hpp"

  /* set methods */

  /* get methods */
  const section::Type< 1, 451 >& MT451() const { return this->mt451_; }
//  const section::Type< 1, 452 >& MT452() const { return *mt452_; }
//  const section::Type< 1, 455 >& MT455() const { return *mt455_; }
//  const section::Type< 1, 456 >& MT456() const { return *mt456_; }
//  const section::Type< 1, 458 >& MT458() const { return *mt458_; }
//  const section::Type< 1, 460 >& MT460() const { return *mt460_; }

  bool
  hasMT( int sectionNo ) const { return sectionNo == 451 ? true : false; }
  bool
  hasSectionNumber( int sectionNo ) const {  return this->hasMT( sectionNo ); }

#include "ENDFtk/file/Type/src/print-1.hpp"
};

}
