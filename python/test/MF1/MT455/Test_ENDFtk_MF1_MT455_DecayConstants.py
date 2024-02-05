# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT455 import DecayConstants

class Test_ENDFtk_MF1_MT455_DecayConstants( unittest.TestCase ) :
    """Unit test for the DecayConstants class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0         12          09228 1455     \n'
              ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
              ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          0         13          09228 1455     \n'
                ' 1.000000+0 1.100000+0 2.000000+0 2.100000+0 3.000000+0 3.100000+09228 1455     \n'
                ' 4.000000+0 4.100000+0 5.000000+0 5.100000+0 6.000000+0 6.100000+09228 1455     \n'
                ' 7.000000+0                                                       9228 1455     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 6, chunk.NNF )
            self.assertEqual( 6, chunk.number_precursors )

            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 6, len( chunk.lambdas ) )
            self.assertEqual( 6, len( chunk.decay_constants ) )
            self.assertAlmostEqual( 1., chunk.lambdas[0] )
            self.assertAlmostEqual( 2., chunk.lambdas[1] )
            self.assertAlmostEqual( 3., chunk.lambdas[2] )
            self.assertAlmostEqual( 4., chunk.lambdas[3] )
            self.assertAlmostEqual( 5., chunk.lambdas[4] )
            self.assertAlmostEqual( 6., chunk.lambdas[5] )
            self.assertAlmostEqual( 1., chunk.decay_constants[0] )
            self.assertAlmostEqual( 2., chunk.decay_constants[1] )
            self.assertAlmostEqual( 3., chunk.decay_constants[2] )
            self.assertAlmostEqual( 4., chunk.decay_constants[3] )
            self.assertAlmostEqual( 5., chunk.decay_constants[4] )
            self.assertAlmostEqual( 6., chunk.decay_constants[5] )
            self.assertEqual( 6, len( chunk.alphas ) )
            self.assertEqual( 6, len( chunk.abundances ) )
            self.assertAlmostEqual( 1.1, chunk.alphas[0] )
            self.assertAlmostEqual( 2.1, chunk.alphas[1] )
            self.assertAlmostEqual( 3.1, chunk.alphas[2] )
            self.assertAlmostEqual( 4.1, chunk.alphas[3] )
            self.assertAlmostEqual( 5.1, chunk.alphas[4] )
            self.assertAlmostEqual( 6.1, chunk.alphas[5] )
            self.assertAlmostEqual( 1.1, chunk.abundances[0] )
            self.assertAlmostEqual( 2.1, chunk.abundances[1] )
            self.assertAlmostEqual( 3.1, chunk.abundances[2] )
            self.assertAlmostEqual( 4.1, chunk.abundances[3] )
            self.assertAlmostEqual( 5.1, chunk.abundances[4] )
            self.assertAlmostEqual( 6.1, chunk.abundances[5] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 455 ) )

        # the data is given explicitly
        chunk = DecayConstants( energy = 1e-5,
                                constants = [ 1., 2., 3., 4., 5., 6. ],
                                abundances = [ 1.1, 2.1, 3.1, 4.1, 5.1, 6.1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DecayConstants.from_string( self.chunk, 9228, 1, 455 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DecayConstants( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = DecayConstants.from_string( self.invalid, 9228, 1, 455 )

if __name__ == '__main__' :

    unittest.main()
