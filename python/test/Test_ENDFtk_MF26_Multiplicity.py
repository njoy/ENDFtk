# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26 import Multiplicity

class Test_ENDFtk_MF26_Multiplicity( unittest.TestCase ) :
    """Unit test for the Multiplicity class."""

    chunk = ( ' 1.100000+1 5.438673-4          0          2          1          2 10026525     \n'
              '          2          2                                             10026525     \n'
              ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n' )

    invalid = ( ' 1.100000+1 5.438673-4          0          2          2          2 10026525     \n'
              '          2          2                                             10026525     \n'
              ' 1.000000+1 1.000000+0 1.00000+11 1.000000+0                       10026525     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 11., chunk.ZAP )
            self.assertAlmostEqual( 11., chunk.product_identifier )
            self.assertAlmostEqual( 5.438673e-4, chunk.AWI )
            self.assertAlmostEqual( 5.438673e-4, chunk.projectile_weight_ratio )
            self.assertEqual( 2, chunk.LAW )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.Y ) )
            self.assertEqual( 2, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 10., chunk.E[0] )
            self.assertAlmostEqual( 1.e+11, chunk.E[1] )
            self.assertAlmostEqual( 10., chunk.energies[0] )
            self.assertAlmostEqual( 1.e+11, chunk.energies[1] )
            self.assertAlmostEqual( 1., chunk.Y[0] )
            self.assertAlmostEqual( 1., chunk.Y[1] )
            self.assertAlmostEqual( 1., chunk.multiplicities[0] )
            self.assertAlmostEqual( 1., chunk.multiplicities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 100, 26, 525 ) )

        # the data is given explicitly
        chunk = Multiplicity( zap = 11., awi = 5.438673e-4, law = 2,
                              boundaries = [ 2 ], interpolants = [ 2 ],
                              energies = [ 10., 1e+11 ],
                              multiplicities = [ 1., 1. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Multiplicity.from_string( self.chunk, 100, 26, 525 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = Multiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = Multiplicity( zap = 11., awi = 5.438673e-4, law = 2,
                                  boundaries = [ 2, 4 ], interpolants = [ 2 ],
                                  energies = [ 10., 1e+11 ],
                                  multiplicities = [ 1., 1. ] )

        with self.assertRaises( Exception ) :

            chunk = Multiplicity.from_string( self.invalid, 100, 26, 525 )

if __name__ == '__main__' :

    unittest.main()
