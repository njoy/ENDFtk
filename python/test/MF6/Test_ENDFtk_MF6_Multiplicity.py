# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import Multiplicity

class Test_ENDFtk_MF6_Multiplicity( unittest.TestCase ) :
    """Unit test for the Multiplicity class."""

    chunk = ( ' 1.001000+3 9.986234-1          0          1          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
              ' 3.000000+7 2.149790-1                                            9228 6  5     \n' )

    invalid = ( ' 1.001000+3 9.986234-1          0          1          1          59228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
                ' 3.000000+7 2.149790-1                                            9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1001, chunk.ZAP )
            self.assertEqual( 1001, chunk.product_identifier )
            self.assertAlmostEqual( 0.9986234, chunk.AWP )
            self.assertAlmostEqual( 0.9986234, chunk.product_weight_ratio )
            self.assertEqual( 0, chunk.LIP )
            self.assertEqual( 0, chunk.product_modifier_flag )
            self.assertEqual( 1, chunk.LAW )

            self.assertEqual( 4, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 4, chunk.boundaries[0] )
            self.assertEqual( 4, len( chunk.E ) )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.Y ) )
            self.assertEqual( 4, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 1.1e+7, chunk.E[1] )
            self.assertAlmostEqual( 1.147e+7, chunk.E[2] )
            self.assertAlmostEqual( 3e+7, chunk.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 1.1e+7, chunk.energies[1] )
            self.assertAlmostEqual( 1.147e+7, chunk.energies[2] )
            self.assertAlmostEqual( 3e+7, chunk.energies[3] )
            self.assertAlmostEqual( 0., chunk.Y[0] )
            self.assertAlmostEqual( 8.45368e-11, chunk.Y[1] )
            self.assertAlmostEqual( 6.622950e-8, chunk.Y[2] )
            self.assertAlmostEqual( 2.149790e-1, chunk.Y[3] )
            self.assertAlmostEqual( 0., chunk.multiplicities[0] )
            self.assertAlmostEqual( 8.45368e-11, chunk.multiplicities[1] )
            self.assertAlmostEqual( 6.622950e-8, chunk.multiplicities[2] )
            self.assertAlmostEqual( 2.149790e-1, chunk.multiplicities[3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = Multiplicity( zap = 1001, awp = 0.9986234, lip = 0, law = 1,
                              boundaries = [ 4 ], interpolants = [ 2 ],
                              energies = [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ],
                              multiplicities = [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Multiplicity.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = Multiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = Multiplicity( zap = 1001, awp = 0.9986234, lip = 0, law = 1,
                                  boundaries = [ 4, 5 ], interpolants = [ 2 ],
                                  energies = [ 1e-5, 1.1e+7, 1.147e+7, 3e+7 ],
                                  multiplicities = [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] )

        with self.assertRaises( Exception ) :

            chunk = Multiplicity.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
