# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import OutgoingEnergyDistribution

class Test_ENDFtk_MF5_OutgoingEnergyDistribution( unittest.TestCase ) :
    """Unit test for the OutgoingEnergyDistribution class."""

    chunk = ( ' 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n'
              '          3          2                                            9437 5 18     \n'
              ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          0          0          2          39437 5 18     \n'
                '          3          2                                            9437 5 18     \n'
                ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 3, len( chunk.EP ) )
            self.assertEqual( 3, len( chunk.outgoing_energies ) )
            self.assertEqual( 3, len( chunk.G ) )
            self.assertEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 0.0, chunk.EP[0] )
            self.assertAlmostEqual( 1e+5, chunk.EP[1] )
            self.assertAlmostEqual( 3e+7, chunk.EP[2] )
            self.assertAlmostEqual( 0.0, chunk.outgoing_energies[0] )
            self.assertAlmostEqual( 1e+5, chunk.outgoing_energies[1] )
            self.assertAlmostEqual( 3e+7, chunk.outgoing_energies[2] )
            self.assertAlmostEqual( 0., chunk.G[0] )
            self.assertAlmostEqual( 1.757570e-9, chunk.G[1] )
            self.assertAlmostEqual( 1.843350e-9, chunk.G[2] )
            self.assertAlmostEqual( 0., chunk.probabilities[0] )
            self.assertAlmostEqual( 1.757570e-9, chunk.probabilities[1] )
            self.assertAlmostEqual( 1.843350e-9, chunk.probabilities[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9437, 5, 18 ) )

        # the data is given explicitly
        chunk = OutgoingEnergyDistribution( incident = 1e-5,
                                            boundaries = [ 3 ], interpolants = [ 2 ],
                                            energies = [ 0.0, 1e+5, 3e+7 ],
                                            probabilities = [ 0.0, 1.757570e-9, 1.843350e-9 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = OutgoingEnergyDistribution.from_string( self.chunk, 9437, 5, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = OutgoingEnergyDistribution( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = OutgoingEnergyDistribution( incident = 1e-5,
                                                boundaries = [ 4 ], interpolants = [ 2 ],
                                                energies = [ 0.0, 1e+5, 3e+7 ],
                                                probabilities = [ 0.0, 1.757570e-9, 1.843350e-9 ] )

        with self.assertRaises( Exception ) :

            chunk = OutgoingEnergyDistribution.from_string( self.invalid, 9437, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
