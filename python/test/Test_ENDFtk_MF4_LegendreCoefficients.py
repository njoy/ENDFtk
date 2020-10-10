# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF4 import LegendreCoefficients

class Test_ENDFtk_MF4_LegendreCoefficients( unittest.TestCase ) :
    """Unit test for the LegendreCoefficients class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n'
              ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          0          2          09228 4  2     \n'
                ' 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )
            self.assertEqual( 3, chunk.NL )
            self.assertEqual( 3, chunk.legendre_order )
            self.assertEqual( 3, len( chunk.A ) )
            self.assertEqual( 3, len( chunk.coefficients ) )
            self.assertAlmostEqual( 7.392510e-5 , chunk.A[0] )
            self.assertAlmostEqual( 8.477139e-9, chunk.A[1] )
            self.assertAlmostEqual( 1.17106e-13, chunk.A[2] )
            self.assertAlmostEqual( 7.392510e-5 , chunk.coefficients[0] )
            self.assertAlmostEqual( 8.477139e-9, chunk.coefficients[1] )
            self.assertAlmostEqual( 1.17106e-13, chunk.coefficients[2] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 4, 2 ) )

        # the data is given explicitly
        chunk = LegendreCoefficients( energy = 1e-5,
                                      coefficients = [ 7.392510e-5, 8.477139e-9,
                                                       1.17106e-13 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LegendreCoefficients.from_string( self.chunk, 9228, 4, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LegendreCoefficients( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = LegendreCoefficients.from_string( self.invalid, 9228, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
