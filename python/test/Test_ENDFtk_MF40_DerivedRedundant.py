# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF40 import DerivedRedundant

class Test_ENDFtk_MF40_DerivedRedundant( unittest.TestCase ) :
    """Unit test for the DerivedRedundant class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          0          0          0943740  2     \n"
        " 2.500000+3 2.000000+7          0          0         14          7943740  2     \n"
        " 1.000000+0 1.000000+0-1.000000+0 4.000000+0-1.000000+0 1.600000+1943740  2     \n"
        "-1.000000+0 1.700000+1-1.000000+0 1.800000+1-1.000000+0 3.700000+1943740  2     \n"
        "-1.000000+0 1.020000+2                                            943740  2     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 0, chunk.LTY )
            self.assertEqual( 0, chunk.procedure )
            self.assertAlmostEqual( 2.5e3, chunk.E1 )
            self.assertAlmostEqual( 2.5e3, chunk.lower_energy )
            self.assertAlmostEqual( 2.0e7, chunk.E2 )
            self.assertAlmostEqual( 2.0e7, chunk.upper_energy )
            self.assertEqual( 7, chunk.NCI )
            self.assertEqual( 7, chunk.number_reactions )

            # values
            self.assertAlmostEqual( 1.0, chunk.coefficients[0] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[1] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[2] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[3] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[4] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[5] )
            self.assertAlmostEqual( -1.0, chunk.coefficients[6] )
            self.assertAlmostEqual( -1.0, chunk.CI[6] )
            self.assertAlmostEqual( 1., chunk.reactions[0] )
            self.assertAlmostEqual( 4., chunk.reactions[1] )
            self.assertAlmostEqual( 16., chunk.reactions[2] )
            self.assertAlmostEqual( 17., chunk.reactions[3] )
            self.assertAlmostEqual( 18., chunk.reactions[4] )
            self.assertAlmostEqual( 37., chunk.reactions[5] )
            self.assertAlmostEqual( 102., chunk.reactions[6] )
            self.assertAlmostEqual( 102., chunk.XMTI[6] )

            self.assertEqual( 5, chunk.NC )

            self.assertEqual( self.chunk,
                              chunk.to_string( 9437, 40, 2 ) )

        # the data is given explicitly
        chunk = DerivedRedundant(
                e1=2.5e3, e2=2.0e7,
                coefficients=[1, -1, -1, -1, -1, -1, -1],
                reactions=[1, 4, 16, 17, 18, 37, 102]
                )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DerivedRedundant.from_string( self.chunk, 9437, 40, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DerivedRedundant( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
