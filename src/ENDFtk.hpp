#ifndef ENDFTK_HPP
#define ENDFTK_HPP

#include <functional>
#include <unordered_map>

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <variant>   
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif

#ifndef CPP17_KLUDGES
#define CPP17_KLUDGES
  namespace std {
    using namespace std::experimental;
  }
#endif

#include "range/v3/all.hpp"

#include "disco.hpp"
#include "Log.hpp"
#include "header-utilities.hpp"

namespace njoy {
namespace ENDFtk {

template< typename T >
using MutableReturnType = std::add_lvalue_reference_t< T >;

template< typename T >
using ImmutableReturnType =
  std::conditional_t
  < std::is_trivially_copyable< T >::value,
    T, std::add_lvalue_reference_t< std::add_const_t< T > > >;

#include "ENDFtk/record.hpp"

#include "ENDFtk/TapeIdentification.hpp"
using TPID = TapeIdentification;

#include "ENDFtk/StructureDivision.hpp"

#include "ENDFtk/HeadRecord.hpp"
using HEAD = HeadRecord;

#include "ENDFtk/TextRecord.hpp"
using TEXT = TextRecord;

#include "ENDFtk/ControlRecord.hpp"
using CONT = ControlRecord;

#include "ENDFtk/DirectoryRecord.hpp"
using DIR = DirectoryRecord;

#include "ENDFtk/ListRecord.hpp"
using LIST = ListRecord;

#include "ENDFtk/UnivariateTabulation.hpp"
using TAB1 = UnivariateTabulation;

#include "ENDFtk/section.hpp"

#include "ENDFtk/ResonanceParameters.hpp"

#include "ENDFtk/file.hpp"

#include "ENDFtk/syntaxTree.hpp"

}
}

#endif // ENDFTK_HPP
