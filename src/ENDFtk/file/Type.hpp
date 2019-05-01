template< int FileNumber >
class Type : public Base< Type< FileNumber > > {

public :

  /* convenience typedefs */
  using Section = section::Type< FileNumber >;

  /* custom iterators */
  struct iterator : public std::map< int, Section >::iterator {

    iterator( typename std::map< int, Section >::iterator iter )
      : std::map< int, Section >::iterator( iter ) {}

    Section& operator*() {

      return std::map< int, Section >::iterator::operator*().second;
    }

    Section* operator->() {

      return &( std::map< int, Section >::iterator::operator->()->second );
    }
  };

  struct const_iterator : public std::map< int, Section >::const_iterator {

    const_iterator( typename std::map< int, Section >::const_iterator iter )
      : std::map< int, Section >::const_iterator( iter ) {}

    const Section& operator*() {

      return std::map< int, Section >::const_iterator::operator*().second;
    }

    const Section* operator->() {

      return &( std::map< int, Section >::const_iterator::operator->()->second );
    }
  };

protected :

  /* fields */
  std::map< int, Section > sectionMap;

  /* methods */
  #include "ENDFtk/file/Type/src/fill.hpp"
  #include "ENDFtk/file/Type/src/read.hpp"

public :

  #include "ENDFtk/file/Type/src/ctor.hpp"
  #include "ENDFtk/file/Type/src/section.hpp"

  iterator begin() { return iterator( this->sectionMap.begin() ); }
  iterator end() { return iterator( this->sectionMap.end() ); }

  const_iterator begin() const {
  
    return const_iterator( const_cast< Type& >(*this).begin() );
  }
  const_iterator end() const {

    return const_iterator( const_cast< Type& >(*this).end() );
  }

  bool hasSection( int sectionNo ) const {

    return this->sectionMap.count( sectionNo );
  }

  static int fileNumber() { return FileNumber; }

  #include "ENDFtk/file/Type/src/print.hpp"
};
