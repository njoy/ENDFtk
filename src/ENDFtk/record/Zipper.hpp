#ifndef NJOY_ENDFTK_RECORD_ZIPPER
#define NJOY_ENDFTK_RECORD_ZIPPER

// system includes

// other includes
#include "ENDFtk/record/TailVerifying.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  struct Zipper {

    /* helper structs */

    template< typename Iterator >
    struct ReadingPack{
      Iterator& it;
      const Iterator& end;
      long& lineNumber;
      int MAT, MF, MT;

      ReadingPack( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT ) :
        it( it ), end( end ), lineNumber( lineNumber ),
        MAT( MAT ), MF( MF ), MT( MT ){}
    };

    template< typename... ENDFTypes  >
    struct Zipped {
      static constexpr std::size_t
      tupleWidth = helper::sum< ENDFTypes::width... >();

      static_assert( tupleWidth < 66, "too many entries on line" );

      static constexpr std::size_t entriesPerTuple = sizeof...( ENDFTypes );
      static constexpr std::size_t tuplesPerRecord = 66 / tupleWidth;

      static constexpr std::size_t
      entriesPerRecord = tuplesPerRecord * entriesPerTuple;

      static const std::size_t nPad = 66 % tupleWidth;

      static constexpr auto tupleIndices =
        std::make_index_sequence< entriesPerTuple >();

      /**
       * @brief
       * This is dark magic to expand the parameter pack a number of times equal
       * to the tuplesPerRecord class variable
       */
      template< std::size_t... indices >
      static decltype(auto)
        expand( std::index_sequence< indices... > ){
        return njoy::tools::disco::Record
          < typename std::tuple_element
            < indices % entriesPerTuple,
              std::tuple< typename ENDFTypes::Parser... > >::type... ,
            njoy::tools::disco::Column< nPad >,
            njoy::tools::disco::RetainCarriage >();
      }

      using Format =
        decltype( expand( std::make_index_sequence< entriesPerRecord >() ) );

      template< std::size_t index >
      using Type =
        typename std::tuple_element
        < index, std::tuple< typename ENDFTypes::Type... > >::type;

      using TupleFormat =
        njoy::tools::disco::Record< typename ENDFTypes::Parser...,
                                    njoy::tools::disco::RetainCarriage >;

      static const std::tuple< typename ENDFTypes::Type... >&
      defaultTuple(){
        static const auto defaultValues =
          std::make_tuple( ENDFTypes::defaultValue... );
        return defaultValues;
      }

    };

    /* convenience aliases */

    using tail = ENDFtk::record::TailVerifying< ENDFtk::record::MAT,
                                                ENDFtk::record::MF,
                                                ENDFtk::record::MT >;

    template< std::size_t index >
    using shouldContinueToRecurse =
      std::conditional_t< ( index != 0 ), std::true_type, std::false_type >;

    /* helper methods */

    // TODO eliminate recursion using make_index_sequence
    template< typename Tuple, std::size_t index >
    static void
    reserve( uint64_t, Tuple&, std::false_type ){}

    template< typename Tuple,
              std::size_t index = ( std::tuple_size< Tuple >::value - 1 )  >
    static void
    reserve( uint64_t nEntries, Tuple& result, std::true_type = std::true_type() ){
      std::get< index >( result ).resize( nEntries );
      reserve< Tuple, ( index - 1 ) >
        ( nEntries, result, shouldContinueToRecurse< index >() );
    }

    template< typename Zip, typename Tuple, std::size_t index >
    static void
    increment( Tuple&, std::false_type ){}

    template< typename Zip, typename Tuple,
              std::size_t index = ( std::tuple_size< Tuple >::value - 1 )  >
    static void
    increment( Tuple& result, std::true_type = std::true_type() ){
      std::get< index >( result ) += Zip::tuplesPerRecord;
      increment< Zip, Tuple, ( index - 1 ) >
        ( result, shouldContinueToRecurse< index >() );
    }

    template< typename... Vectors, std::size_t... indices >
    static std::tuple< typename Vectors::iterator... >
    makeIteratorTuple
    ( std::tuple< Vectors... >& vectorTuple, std::index_sequence< indices... > ){
      return std::make_tuple( std::get< indices >( vectorTuple ).begin()... );
    }

    // explicitly recursive version //
    // ---------------------------- //
    // template< typename... T, int index, int... indices >
    // static std::tuple< typename T::iterator... >
    // makeIteratorTuple( std::tuple< T... >& result, std::false_type ){
    //   return std::make_tuple( std::get< indices >( result ).begin()... );
    // }

    // template< typename... T, int index = ( sizeof...( T ) - 1 ), int... indices >
    // static std::tuple< typename T::iterator... >
    // makeIteratorTuple( std::tuple< T... >& result, std::true_type ){
    //   return makeIteratorTuple< T..., index - 1, index, indices... >
    //     ( result, shouldContinueToRecurse< index >() );
    // }

    template< typename Iterator >
    static void
    verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ){
      tail( MAT, MF, MT, it, end, lineNumber );
    }

    template< typename Zip, typename Iterator, typename... References >
    static void
    process( ReadingPack< Iterator > pack, References&... references ){
      Zip::Format::read( pack.it, pack.end, references... );
      verifyTail( pack.it, pack.end, pack.lineNumber,
                  pack.MAT, pack.MF, pack.MT );
    }

    template< typename Zip, std::size_t index,
              typename Pack, typename IteratorTuple,
              std::size_t... iteratorIndices, typename... References >
    static void
    expandReferencePack
    ( Pack& pack, IteratorTuple&, std::false_type,
      std::index_sequence< iteratorIndices... >, References&... references ){
      process< Zip >( pack, references... );
    }

    template< typename Zip, std::size_t index = 0,
              typename Pack, typename IteratorTuple,
              std::size_t... iteratorIndices, typename... References >
    static void
    expandReferencePack
    ( Pack& pack, IteratorTuple& iteratorTuple, std::true_type,
      std::index_sequence< iteratorIndices... >, References&... references ){
      expandReferencePack< Zip, index + 1 >
        ( pack, iteratorTuple,
          shouldContinueToRecurse< Zip::tuplesPerRecord - index - 1 >(),
          Zip::tupleIndices, references... ,
          std::get< iteratorIndices >( iteratorTuple )[index]... );
    }

    template< typename Zip, typename Tuple, typename Iterator >
    static void
    readLine( Tuple& iteratorTuple,
              Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
      ReadingPack< Iterator > pack( it, end, lineNumber, MAT, MF, MT );    
      expandReferencePack< Zip >
        ( pack, iteratorTuple, std::true_type(), Zip::tupleIndices );
    }

    template< typename Zip, typename Tuple,
              typename Iterator, std::size_t... indices >
    static void
    readPartialLine
    ( uint64_t nEntries, Tuple& iteratorTuple, Iterator& it, const Iterator& end,
      long& lineNumber, int MAT, int MF, int MT,
      std::index_sequence< indices... > ){

      using namespace njoy::tools;

    //auto increment = []( uint64_t offset, auto& iterator ){ iterator+= offset; };

      for ( uint64_t offset = 0; offset < nEntries; ++offset ){
        Zip::TupleFormat::read
          ( it, end, std::get< indices >( iteratorTuple )[offset]... );
      }

      auto remainingEntries = Zip::tuplesPerRecord - nEntries;
      std::tuple< typename Zip:: template Type< indices >... > leftovers;

      while ( remainingEntries-- ){
        Zip::TupleFormat::read( it, end, std::get< indices >( leftovers )... );
        if ( leftovers != Zip::defaultTuple() ){
          Log::error( "Encountered non-default value where none was expected" );
          throw std::exception();
        }
      }

      using Gap = disco::Record
                  < disco::Column< Zip::nPad >, disco::RetainCarriage >;

      Gap::read( it, end );

      verifyTail( it, end, lineNumber, MAT, MF, MT );
    }

    /* methods */

    template< typename... ENDFTypes, typename Iterator >
    static std::tuple< std::vector< typename ENDFTypes::Type >... >
    unzip
    ( uint64_t nEntries,
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ){

      std::tuple< std::vector< typename ENDFTypes::Type >... > result;    
      reserve( nEntries, result );

      using Zip = Zipped< ENDFTypes... >;
      auto iterators = makeIteratorTuple( result, Zip::tupleIndices );

      int remainingLines = nEntries / Zip::tuplesPerRecord;
      while ( remainingLines-- ){
        readLine< Zip >( iterators, it, end, lineNumber, MAT, MF, MT );
        increment< Zip >( iterators );
      }

      const int remainingEntries = nEntries % Zip::tuplesPerRecord;
      if ( remainingEntries ){
        readPartialLine< Zip >
          ( remainingEntries, iterators, it, end, lineNumber,
            MAT, MF, MT, Zip::tupleIndices );
      }

      return result;
    }
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
