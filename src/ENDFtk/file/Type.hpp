template< int FileNumber >
class Type : public Base< Type< FileNumber > > {

public :

  /* convenience typedefs */
  using Section = section::Type< FileNumber >;
  using iterator = typename std::vector< Section >::iterator;
  using const_iterator = typename std::vector< Section >::const_iterator;

protected :

  /* fields */
  std::vector< Section > sectionVector;
  tsl::hopscotch_map< int, const Section* > sectionMap;

  /* methods */
  #include "ENDFtk/file/Type/src/collectVector.hpp"
  #include "ENDFtk/file/Type/src/collectMap.hpp"

public :

  #include "ENDFtk/file/Type/src/ctor.hpp"
  #include "ENDFtk/file/Type/src/section.hpp"

  iterator begin() { return this->sectionVector.begin(); }
  iterator end() { return this->sectionVector.end(); }

  const_iterator begin() const { return const_cast< Type& >(*this).begin(); }
  const_iterator end() const { return const_cast< Type& >(*this).end(); }

  bool hasSection( int sectionNo ) const {

    return this->sectionMap.count( sectionNo );
  }

  static int fileNumber() { return FileNumber; }

  #include "ENDFtk/file/Type/src/print.hpp"
};
