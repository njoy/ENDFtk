namespace file{

template< int MF >
class Type {
public:
  /* convenience typedefs */
  using Section = section::Type< MF >;
  using iterator = typename std::vector< Section >::iterator;
  using const_iterator = typename std::vector< Section >::const_iterator;

  /* fields */
  std::vector< Section > sectionVector;
  std::unordered_map< int, Section& > sectionMap;

  /* methods */
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

}
