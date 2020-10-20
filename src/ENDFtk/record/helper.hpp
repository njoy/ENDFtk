#ifndef NJOY_ENDFTK_RECORD_HELPER
#define NJOY_ENDFTK_RECORD_HELPER

// system includes
#include <string>

// other includes

namespace njoy {
namespace ENDFtk {
namespace record {
namespace helper {

template< int position >
std::string symbolDefinition();

template<> inline std::string symbolDefinition< 0 >(){ return "MAT"; }
template<> inline std::string symbolDefinition< 1 >(){ return "MF"; }
template<> inline std::string symbolDefinition< 2 >(){ return "MT"; }

template< int position > const std::string symbol = symbolDefinition<position>();

template< int position >
std::string nameDefintion();

template<> inline std::string nameDefintion<0>(){ return "material"; }
template<> inline std::string nameDefintion<1>(){ return "file"; }
template<> inline std::string nameDefintion<2>(){ return "section"; }

template< int position > const std::string name = nameDefintion<position>();

template< int width >
std::string defaultStringDefinition(){
  return defaultStringDefinition< width - 1 >() + " ";
}

template<>
inline std::string defaultStringDefinition<0>(){ return ""; }

template< int width >
const std::string defaultString = defaultStringDefinition< width >();

template< int entry >
constexpr int sum(){ return entry; }

template< int entry1, int entry2, int... entries >
constexpr int sum(){ return entry1 + sum< entry2, entries... >(); }

} // helper namespace
} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
