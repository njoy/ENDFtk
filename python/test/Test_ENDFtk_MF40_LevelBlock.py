# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF40 import LevelBlock
from ENDFtk import ReactionBlock
from ENDFtk import SquareMatrix

class Test_ENDFtk_MF40_LevelBlock( unittest.TestCase ) :
    """Unit test for the LevelBlock class."""

    chunk = (
        " 3.140000+0 6.280000+0        314        628          0          2943740 51     \n"
        " 3.000000+0 1.000000+0         55         66          0          1943740 51     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
        " 4.000000+0                                                       943740 51     \n"
        " 3.000000+0 1.000000+0         77         88          0          1943740 51     \n"
        " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
        " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
        " 4.000000+0                                                       943740 51     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # LevelBlock CONT record
            self.assertAlmostEqual( 3.14, chunk.QM )
            self.assertAlmostEqual( 3.14, chunk.mass_difference_q_value )
            self.assertAlmostEqual( 6.28, chunk.QI )
            self.assertAlmostEqual( 6.28, chunk.reaction_q_value )
            self.assertEqual( 314, chunk.IZAP )
            self.assertEqual( 314, chunk.product_identifier )
            self.assertEqual( 628, chunk.LFS )
            self.assertEqual( 628, chunk.excited_level )
            self.assertEqual( 2, chunk.NL )
            self.assertEqual( 2, chunk.number_reactions )
            self.assertEqual( 2, len(chunk.reaction_blocks) )

            stuff = chunk.reaction_blocks[1]

            # ReactionBlock CONT record
            self.assertAlmostEqual( 3.0, stuff.XMF1 )
            self.assertAlmostEqual( 1.0, stuff.XLFS1 )
            self.assertEqual( 77, stuff.MAT1 )
            self.assertEqual( 88, stuff.MT1 )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk,
                              chunk.to_string( 9437, 40, 51 ) )

        # the data is given explicitly
        chunk = LevelBlock(
            qm=3.14, qi=6.28, izap=314, lfs=628,
            reactions=[
                ReactionBlock(
                    3.0, 1.0, 55, 66,
                    [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                    ),
                ReactionBlock(
                    3.0, 1.0, 77, 88,
                    [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                    )]
                )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LevelBlock.from_string( self.chunk, 9437, 40, 51 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LevelBlock( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
