# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF33 import ReactionBlock
from ENDFtk.MF33 import DerivedRedundant
from ENDFtk.MF33 import DerivedRatioToStandard

class Test_ENDFtk_MF33_ReactionBlock( unittest.TestCase ) :
    """Unit test for the ReactionBlock class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          2          2          0943733  2     \n"
        " 0.000000+0 0.000000+0          0          0          0          0943733  2     \n"
        " 2.500000+3 2.000000+7          0          0         14          7943733  2     \n"
        " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943733  2     \n"
        "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943733  2     \n"
        "-1.000000+0 1.020000+2                                            943733  2     \n"
        " 0.000000+0 0.000000+0          0          1          0          0943733  2     \n"
        " 2.500000+3 2.000000+7        325        102          6          2943733  2     \n"
        " 3.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+0 4.000000+0943733  2     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # subsection CONT record
            self.assertAlmostEqual( 0., chunk.XMF1 )
            self.assertAlmostEqual( 0., chunk.second_file_number )
            self.assertAlmostEqual( 0., chunk.XLFS1 )
            self.assertAlmostEqual( 0., chunk.second_final_excited_state )
            self.assertEqual( 0, chunk.MAT1 )
            self.assertEqual( 0, chunk.second_material_number )
            self.assertEqual( 2, chunk.MT1 )
            self.assertEqual( 2, chunk.second_section_number )
            self.assertEqual( 2, chunk.NK )
            self.assertEqual( 2, chunk.number_derived )
            self.assertEqual( 0, chunk.NI )
            self.assertEqual( 0, chunk.number_explicit )
            self.assertEqual( 2, len(chunk.derived_covariances) )
            self.assertEqual( 0, len(chunk.explicit_covariances) )

            chunky = chunk.derived_covariances[0]

            # metadata
            self.assertEqual( 0, chunky.LTY )
            self.assertEqual( 0, chunky.procedure )
            self.assertAlmostEqual( 2.5e3, chunky.E1 )
            self.assertAlmostEqual( 2.5e3, chunky.lower_energy )
            self.assertAlmostEqual( 2.0e7, chunky.E2 )
            self.assertAlmostEqual( 2.0e7, chunky.upper_energy )
            self.assertEqual( 7, chunky.NCI )
            self.assertEqual( 7, chunky.number_reactions )

            # values
            self.assertAlmostEqual( 1.0, chunky.coefficients[0] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[1] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[2] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[3] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[4] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[5] )
            self.assertAlmostEqual( -1.0, chunky.coefficients[6] )
            self.assertAlmostEqual( -1.0, chunky.CI[6] )
            self.assertAlmostEqual( 1., chunky.reactions[0] )
            self.assertAlmostEqual( 4., chunky.reactions[1] )
            self.assertAlmostEqual( 16., chunky.reactions[2] )
            self.assertAlmostEqual( 17., chunky.reactions[3] )
            self.assertAlmostEqual( 18., chunky.reactions[4] )
            self.assertAlmostEqual( 37., chunky.reactions[5] )
            self.assertAlmostEqual( 102., chunky.reactions[6] )
            self.assertAlmostEqual( 102., chunky.XMTI[6] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk,
                              chunk.to_string( 9437, 33, 2 ) )

        # the data is given explicitly
        chunk = ReactionBlock(xmf1=0, xlfs1=0, mat1=0, mt1=2, nc=[
            DerivedRedundant(
                2.5e3, 2.0e7,
                [1, -1, -1, -1, -1, -1, -1],
                [1, 4, 16, 17, 18, 37, 102]
                ),
            DerivedRatioToStandard(
                1, 2.5e+3, 2.0e+7, 325, 102, 3, 0,
                [1, 2], [3, 4]
                )
            ])

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReactionBlock.from_string( self.chunk, 9437, 33, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ReactionBlock( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
