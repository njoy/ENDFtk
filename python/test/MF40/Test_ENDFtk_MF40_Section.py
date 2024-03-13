# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF40 import Section
from ENDFtk.MF40 import LevelBlock
from ENDFtk import ReactionBlock
from ENDFtk import SquareMatrix
from ENDFtk.tree import Tape

class Test_ENDFtk_MF40_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( " 9.423900+4 2.369986+2          1          0          1          0943740 51     \n"
              " 3.140000+0 6.280000+0        314        628          0          2943740 51     \n"
              " 3.000000+0 1.000000+0         55         66          0          1943740 51     \n"
              " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
              " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
              " 4.000000+0                                                       943740 51     \n"
              " 3.000000+0 1.000000+0         77         88          0          1943740 51     \n"
              " 0.000000+0 0.000000+0          0          5          7          3943740 51     \n"
              " 0.000000+0 1.000000+2 2.000000+2 1.000000+0 2.000000+0 3.000000+0943740 51     \n"
              " 4.000000+0                                                       943740 51     \n" )


    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  943740  0     \n'
    valid_FEND = '                                                                  9437 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  943740  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 51, chunk.MT )
            self.assertEqual( 51, chunk.section_number )
            self.assertEqual( 94239, chunk.ZA )
            self.assertEqual( 94239, chunk.target_identifier )
            self.assertAlmostEqual( 2.369986e+2, chunk.AWR )
            self.assertAlmostEqual( 2.369986e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LIS )
            self.assertEqual( 1, chunk.excited_level )
            self.assertEqual( 1, chunk.NS )
            self.assertEqual( 1, chunk.number_level_blocks )
            self.assertEqual( 1, len(chunk.level_blocks) )
            self.assertEqual( 51, chunk.MT )
            self.assertEqual( 51, chunk.section_number )

            sub = chunk.level_blocks[0]

            # LevelBlock CONT record
            self.assertAlmostEqual( 3.14, sub.QM )
            self.assertAlmostEqual( 3.14, sub.mass_difference_q_value )
            self.assertAlmostEqual( 6.28, sub.QI )
            self.assertAlmostEqual( 6.28, sub.reaction_q_value )
            self.assertEqual( 314, sub.IZAP )
            self.assertEqual( 314, sub.product_identifier )
            self.assertEqual( 628, sub.LFS )
            self.assertEqual( 628, sub.excited_level )
            self.assertEqual( 2, sub.NL )
            self.assertEqual( 2, sub.number_reactions )
            self.assertEqual( 2, len(sub.reaction_blocks) )

            stuff = sub.reaction_blocks[1]

            # ReactionBlock CONT record
            self.assertAlmostEqual( 3.0, stuff.XMF1 )
            self.assertAlmostEqual( 1.0, stuff.XLFS1 )
            self.assertEqual( 77, stuff.MAT1 )
            self.assertEqual( 88, stuff.MT1 )

            self.assertEqual( 10, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9437, 40 ) )

        # the data is given explicitly
        chunk = Section(
            mt=51, zaid=94239, awr=2.369986e+2, lis=1,
            blocks=[LevelBlock(
                3.14, 6.28, 314, 628, [
                    ReactionBlock(
                        3.0, 1.0, 55, 66,
                        [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                        ),
                    ReactionBlock(
                        3.0, 1.0, 77, 88,
                        [SquareMatrix(0, [0, 100, 200], [1, 2, 3, 4])]
                        )]
                )]
            )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )
        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9437 ).file( 40 ).section( 51 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
