#ifndef ENDFTK_HPP
#define ENDFTK_HPP

#include <functional>
#include <unordered_map>
#include <complex>
#include <map>

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
#include <variant>
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif

#include <optional>
#include "range/v3/all.hpp"

#include "disco.hpp"
#include "boost/hana.hpp"
#include "Log.hpp"
#include "header-utilities.hpp"

#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

namespace hana = boost::hana;

inline namespace literals {

using namespace hana::literals;
}

template< typename T >
using MutableReturnType = std::add_lvalue_reference_t< T >;

template< typename T >
using ImmutableReturnType =
  std::conditional_t
  < std::is_trivially_copyable< T >::value,
    T, std::add_lvalue_reference_t< std::add_const_t< T > > >;

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

#include "ENDFtk/InterpolationRecord.hpp"
using TAB2 = InterpolationRecord;

#include "ENDFtk/TabulationRecord.hpp"
using TAB1 = TabulationRecord;

#include "ENDFtk/InterpolationSequenceRecord.hpp"

#include "ENDFtk/resonanceParameters.hpp"

#include "ENDFtk/section.hpp"

#include "ENDFtk/file.hpp"

#include "ENDFtk/syntaxTree.hpp"

}
}

#endif // ENDFTK_HPP

#include "ENDFtk/isRedundant.hpp"
