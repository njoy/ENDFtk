namespace file{

template< int FileNumber >
class Type {
public:
  /* convenience typedefs */
  using Section = section::Type< FileNumber >;
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

  static int MF() { return FileNumber; }
  static int fileNumber() { return MF(); }

  #include "ENDFtk/file/Type/src/print.hpp"
};

#include "ENDFtk/file/1.hpp"

}
