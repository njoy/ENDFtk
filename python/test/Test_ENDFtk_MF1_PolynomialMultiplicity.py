# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1 import PolynomialMultiplicity

class Test_ENDFtk_MF1_PolynomialMultiplicity( unittest.TestCase ) :
    """Unit test for the PolynomialMultiplicity class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          2          09228 1455     \n'
              ' 2.436700+0 5.000000-2                                            9228 1455     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          1          09228 1455     \n'
                ' 2.436700+0 5.000000-2                                            9228 1455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LNU )
            self.assertEqual( 1, chunk.representation )

            self.assertEqual( 2, chunk.NCO )
            self.assertEqual( 2, chunk.number_coefficients )
            self.assertEqual( 2, len( chunk.C ) )
            self.assertEqual( 2, len( chunk.coefficients ) )
            self.assertAlmostEqual( 2.4367, chunk.C[0] )
            self.assertAlmostEqual( 5e-2, chunk.C[1] )
            self.assertAlmostEqual( 2.4367, chunk.coefficients[0] )
            self.assertAlmostEqual( 5e-2, chunk.coefficients[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 455 ) )

        # the data is given explicitly
        chunk = PolynomialMultiplicity( coefficients = [ 2.4367, 5e-2 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = PolynomialMultiplicity.from_string( self.chunk, 9228, 1, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = PolynomialMultiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = PolynomialMultiplicity.from_string( self.invalid, 9228, 1, 455 )

if __name__ == '__main__' :

    unittest.main()
