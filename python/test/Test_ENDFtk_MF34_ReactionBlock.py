# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF34 import ReactionBlock
from ENDFtk.MF34 import LegendreBlock
from ENDFtk.MF34 import SquareMatrix

class Test_ENDFtk_MF34_ReactionBlock( unittest.TestCase ) :
    """Unit test for the ReactionBlock class."""

    chunk = (
        " 0.000000+0 0.000000+0          0         51          2          2943734 51     \n"
        " 0.000000+0 0.000000+0          1          1          0          1943734 51     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
        " 4.000000+0                                                       943734 51     \n"
        " 0.000000+0 0.000000+0          1          2          0          1943734 51     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
        " 4.000000+0                                                       943734 51     \n"
        " 0.000000+0 0.000000+0          2          2          0          1943734 51     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734 51     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734 51     \n"
        " 4.000000+0                                                       943734 51     \n" )

    chunk1 = (
        " 0.000000+0 0.000000+0          0         51          1          2943734  2     \n"
        " 0.000000+0 0.000000+0          1          1          0          1943734  2     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
        " 4.000000+0                                                       943734  2     \n"
        " 0.000000+0 0.000000+0          1          2          0          1943734  2     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943734  2     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943734  2     \n"
        " 4.000000+0                                                       943734  2     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # ReactionBlock CONT record
            self.assertEqual( 0, chunk.MAT1 )
            self.assertEqual( 0, chunk.second_material_number )
            self.assertEqual( 51, chunk.MT1 )
            self.assertEqual( 51, chunk.second_section_number )
            self.assertEqual( 2, chunk.NL )
            self.assertEqual( 2, chunk.first_number_legendre )
            self.assertEqual( 2, chunk.NL1 )
            self.assertEqual( 2, chunk.second_number_legendre )
            self.assertEqual( 3, chunk.NSS )
            self.assertEqual( 3, chunk.number_legendre_blocks )
            self.assertEqual( 3, len(chunk.legendre_blocks) )

            stuff = chunk.legendre_blocks[1]

            # LegendreBlock CONT record
            self.assertEqual( 1, stuff.L )
            self.assertEqual( 1, stuff.first_legendre_order )
            self.assertEqual( 2, stuff.L1 )
            self.assertEqual( 2, stuff.second_legendre_order )
            self.assertEqual( 0, stuff.LCT )
            self.assertEqual( 0, stuff.reference_frame )
            self.assertEqual( 1, stuff.NI )
            self.assertEqual( 1, stuff.number_data_blocks )
            self.assertEqual( 1, len(stuff.data) )

            self.assertEqual( 13, chunk.NC )

            # verify string
            self.assertEqual( self.chunk,
                              chunk.to_string( 9437, 34, 51 ) )

        def verify_chunk1( self, chunk ) :

              # ReactionBlock CONT record
              self.assertEqual( 0, chunk.MAT1 )
              self.assertEqual( 0, chunk.second_material_number )
              self.assertEqual( 51, chunk.MT1 )
              self.assertEqual( 51, chunk.second_section_number )
              self.assertEqual( 1, chunk.NL )
              self.assertEqual( 1, chunk.first_number_legendre )
              self.assertEqual( 2, chunk.NL1 )
              self.assertEqual( 2, chunk.second_number_legendre )
              self.assertEqual( 2, chunk.NSS )
              self.assertEqual( 2, chunk.number_legendre_blocks )
              self.assertEqual( 2, len(chunk.legendre_blocks) )

              stuff = chunk.legendre_blocks[1]

              # LegendreBlock CONT record
              self.assertEqual( 1, stuff.L )
              self.assertEqual( 1, stuff.first_legendre_order )
              self.assertEqual( 2, stuff.L1 )
              self.assertEqual( 2, stuff.second_legendre_order )
              self.assertEqual( 0, stuff.LCT )
              self.assertEqual( 0, stuff.reference_frame )
              self.assertEqual( 1, stuff.NI )
              self.assertEqual( 1, stuff.number_data_blocks )
              self.assertEqual( 1, len(stuff.data) )

              self.assertEqual( 9, chunk.NC )

              # verify string
              self.assertEqual( self.chunk1,
                                chunk.to_string( 9437, 34, 2 ) )

        # the data is given explicitly for MT==MT1
        chunk = ReactionBlock(mt=51, mt1=51, nl=2, nl1=2, lblocks=[
            LegendreBlock(
                1, 1, 0,
                [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                ),
            LegendreBlock(
                1, 2, 0,
                [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                ),
            LegendreBlock(
                2, 2, 0,
                [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                )
            ])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReactionBlock.from_string( self.chunk, 9437, 34, 51 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ReactionBlock( chunk )

        verify_chunk( self, copy )

        # the data is given explicitly for MT!=MT1
        chunk = ReactionBlock(mt=2, mt1=51, nl=1, nl1=2, lblocks=[
            LegendreBlock(
                1, 1, 0,
                [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                ),
            LegendreBlock(
                1, 2, 0,
                [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                )
            ])

        verify_chunk1( self, chunk )


if __name__ == '__main__' :

    unittest.main()
