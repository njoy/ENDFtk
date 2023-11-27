# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import Probability

class Test_ENDFtk_MF5_Probability( unittest.TestCase ) :
    """Unit test for the Probability class."""

    chunk_u0 = ( ' 0.000000+0 0.000000+0          0          1          1          29437 5 18     \n'
                 '          2          2                                            9437 5 18     \n'
                 ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n' )

    chunk_u1 = ( ' 1.000000+0 0.000000+0          0          1          1          29437 5 18     \n'
                 '          2          2                                            9437 5 18     \n'
                 ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          1          2          29437 5 18     \n'
                '          2          2                                            9437 5 18     \n'
                ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n' )

    def test_component( self ) :

        def verify_chunk_u0( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LF )
            self.assertEqual( 1, chunk.LAW )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.P ) )
            self.assertEqual( 2, len( chunk.probabilities ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 3e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 3e+7, chunk.energies[1] )
            self.assertAlmostEqual( 1., chunk.P[0] )
            self.assertAlmostEqual( 1., chunk.P[1] )
            self.assertAlmostEqual( 1., chunk.probabilities[0] )
            self.assertAlmostEqual( 1., chunk.probabilities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_u0, chunk.to_string( 9437, 5, 18 ) )

        def verify_chunk_u1( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LF )
            self.assertEqual( 1, chunk.LAW )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.P ) )
            self.assertEqual( 2, len( chunk.probabilities ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 3e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 3e+7, chunk.energies[1] )
            self.assertAlmostEqual( 1., chunk.P[0] )
            self.assertAlmostEqual( 1., chunk.P[1] )
            self.assertAlmostEqual( 1., chunk.probabilities[0] )
            self.assertAlmostEqual( 1., chunk.probabilities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_u1, chunk.to_string( 9437, 5, 18 ) )

        # the data is given explicitly with u = 0.
        chunk = Probability( lf = 1,
                             boundaries = [ 2 ], interpolants = [ 2 ],
                             energies = [ 1e-5, 3e+7 ], probabilities = [ 1., 1. ] )

        verify_chunk_u0( self, chunk )

        # the data is read from a string with u = 0.
        chunk = Probability.from_string( self.chunk_u0, 9437, 5, 18 )

        verify_chunk_u0( self, chunk )

        # the data is copied with u = 0.
        copy = Probability( chunk )

        verify_chunk_u0( self, copy )

        # the data is given explicitly with u = 1.
        chunk = Probability( lf = 1, u= 1.,
                             boundaries = [ 2 ], interpolants = [ 2 ],
                             energies = [ 1e-5, 3e+7 ], probabilities = [ 1., 1. ] )

        verify_chunk_u1( self, chunk )

        # the data is read from a string with u = 1.
        chunk = Probability.from_string( self.chunk_u1, 9437, 5, 18 )

        verify_chunk_u1( self, chunk )

        # the data is copied with u = 1.
        copy = Probability( chunk )

        verify_chunk_u1( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = Probability( lf = 1,
                                 boundaries = [ 2,4 ], interpolants = [ 2 ],
                                 energies = [ 1e-5, 3e+7 ], values = [ 1., 1. ] )

        with self.assertRaises( Exception ) :

            chunk = Probability.from_string( self.invalid, 9437, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
