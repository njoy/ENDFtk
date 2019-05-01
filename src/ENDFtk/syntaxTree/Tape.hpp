template< typename BufferIterator >
class Tape {
public:
  /* convenience typedefs */
  using Material_t = Material< BufferIterator >;
  using iterator = typename std::vector< Material_t >::iterator;
  using const_iterator = typename std::vector< Material_t >::const_iterator;
  using Multimap = std::unordered_multimap< int, const Material_t* >;
  
protected:
  /* fields */
  std::pair< BufferIterator, BufferIterator > bufferLimits;
  TapeIdentification tpid;
  std::vector< Material_t > materialVector;
  Multimap materialMap;

  /* ctor */
#include "ENDFtk/syntaxTree/Tape/src/createVector.hpp"
#include "ENDFtk/syntaxTree/Tape/src/createMap.hpp"

public:
#include "ENDFtk/syntaxTree/Tape/src/ctor.hpp"

  /* methods */
#include "ENDFtk/syntaxTree/Tape/src/materialNumber.hpp"

  auto MAT( int materialNo ){ return this->materialNumber( materialNo ); }
  auto MAT( int materialNo ) const { return this->materialNumber( materialNo ); }

  bool hasMAT( int materialNo ) const {
    return this->materialMap.count( materialNo );
  }

  bool hasMaterialNumber( int materialNo ) const {
    return this->hasMAT( materialNo );
  }
  
  iterator begin(){ return materialVector.begin(); }
  iterator end(){ return materialVector.end(); }

  const_iterator begin() const { return const_cast< Tape& >( *this ).begin(); }
  const_iterator end() const { return const_cast< Tape& >( *this ).end(); }
  
  std::size_t size() const { return materialVector.size(); }

  auto buffer() const {
    return ranges::make_iterator_range( this->bufferLimits.first,
                                        this->bufferLimits.second );
  }

  const TapeIdentification& TPID() const { return this->tpid; }
};


template< typename BufferIterator,
	  typename Traits = std::iterator_traits<BufferIterator>,
	  std::enable_if_t
	  <std::is_same
	   <typename Traits::iterator_category,
	    std::random_access_iterator_tag>::value, bool > = true,
	  std::enable_if_t
	  <std::is_same
	   <typename Traits::value_type, char>::value, bool > = true>
Tape< BufferIterator >
tape( BufferIterator begin, BufferIterator end ) {
  return {begin, end};
}

template< typename Range >
auto tape( const Range& range )
  -> decltype( tape( range.begin(), range.end() ) ) {
  return tape( range.begin(), range.end() );
} 
