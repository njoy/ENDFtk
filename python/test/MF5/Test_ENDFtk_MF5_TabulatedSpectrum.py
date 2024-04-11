# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import OutgoingEnergyDistribution
from ENDFtk.MF5 import TabulatedSpectrum

class Test_ENDFtk_MF5_TabulatedSpectrum( unittest.TestCase ) :
    """Unit test for the TabulatedSpectrum class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n'
              '          2          4                                            9437 5 18     \n'
              ' 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n'
              '          3          2                                            9437 5 18     \n'
              ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n'
              ' 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n'
              '          4          2                                            9437 5 18     \n'
              ' 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n'
              ' 3.000000+7 1.898849-9                                            9437 5 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          29437 5 18     \n'
                '          2          4                                            9437 5 18     \n'
                ' 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n'
                '          3          2                                            9437 5 18     \n'
                ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n'
                ' 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n'
                '          4          2                                            9437 5 18     \n'
                ' 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n'
                ' 3.000000+7 1.898849-9                                            9437 5 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LF )
            self.assertEqual( 1, chunk.LAW )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_ranges )
            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 4, chunk.interpolants[0] )

            self.assertEqual( 2, len( chunk.incident_energies ) )
            self.assertAlmostEqual( 1e-5, chunk.incident_energies[0] )
            self.assertAlmostEqual( 3e+7, chunk.incident_energies[1] )

            value = chunk.outgoing_distributions[0]
            self.assertAlmostEqual( 1e-5, value.E )
            self.assertAlmostEqual( 1e-5, value.incident_energy )
            self.assertEqual( 3, value.NP )
            self.assertEqual( 3, value.number_points )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, value.number_interpolation_regions )
            self.assertEqual( 1, len( value.INT ) )
            self.assertEqual( 1, len( value.NBT ) )
            self.assertEqual( 2, value.INT[0] )
            self.assertEqual( 3, value.NBT[0] )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 3, value.boundaries[0] )
            self.assertEqual( 3, len( value.EP ) )
            self.assertEqual( 3, len( value.outgoing_energies ) )
            self.assertEqual( 3, len( value.G ) )
            self.assertEqual( 3, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 1e+5, value.EP[1] )
            self.assertAlmostEqual( 3e+7, value.EP[2] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 1e+5, value.outgoing_energies[1] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[2] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.757570e-9, value.G[1] )
            self.assertAlmostEqual( 1.843350e-9, value.G[2] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.757570e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.843350e-9, value.probabilities[2] )

            value = chunk.outgoing_distributions[1]
            self.assertAlmostEqual( 3e+7, value.E )
            self.assertAlmostEqual( 3e+7, value.incident_energy )
            self.assertEqual( 4, value.NP )
            self.assertEqual( 4, value.number_points )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, value.number_interpolation_regions )
            self.assertEqual( 1, len( value.INT ) )
            self.assertEqual( 1, len( value.NBT ) )
            self.assertEqual( 2, value.INT[0] )
            self.assertEqual( 4, value.NBT[0] )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 4, value.boundaries[0] )
            self.assertEqual( 4, len( value.EP ) )
            self.assertEqual( 4, len( value.outgoing_energies ) )
            self.assertEqual( 4, len( value.G ) )
            self.assertEqual( 4, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 10., value.EP[1] )
            self.assertAlmostEqual( 11., value.EP[2] )
            self.assertAlmostEqual( 3e+7, value.EP[3] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 10., value.outgoing_energies[1] )
            self.assertAlmostEqual( 11., value.outgoing_energies[2] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[3] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.733405e-9, value.G[1] )
            self.assertAlmostEqual( 1.818010e-9, value.G[2] )
            self.assertAlmostEqual( 1.898849e-9, value.G[3] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.733405e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.818010e-9, value.probabilities[2] )
            self.assertAlmostEqual( 1.898849e-9, value.probabilities[3] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9437, 5, 18 ) )

        # the data is given explicitly
        chunk = TabulatedSpectrum(
                  boundaries = [ 2 ], interpolants = [ 4 ],
                  distributions = [ OutgoingEnergyDistribution( 1e-5, [ 3 ], [ 2 ],
                                                                [ 0.0, 1e+5, 3e+7 ],
                                                                [ 0.0, 1.757570e-9, 1.843350e-9 ] ),
                                    OutgoingEnergyDistribution( 3e+7, [ 4 ], [ 2 ],
                                                                [ 0.0, 10., 11., 3e+7 ],
                                                                [ 0.0, 1.733405e-9, 1.818010e-9,
                                                                  1.898849e-9 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TabulatedSpectrum.from_string( self.chunk, 9437, 5, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TabulatedSpectrum( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = TabulatedSpectrum(
                      boundaries = [ 2, 4 ], interpolants = [ 4 ],
                      distributions = [ OutgoingEnergyDistribution( 1e-5, [ 3 ], [ 2 ],
                                                                    [ 0.0, 1e+5, 3e+7 ],
                                                                    [ 0.0, 1.757570e-9, 1.843350e-9 ] ),
                                        OutgoingEnergyDistribution( 3e+7, [ 4 ], [ 2 ],
                                                                    [ 0.0, 10., 11., 3e+7 ],
                                                                    [ 0.0, 1.733405e-9, 1.818010e-9,
                                                                      1.898849e-9 ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = TabulatedSpectrum.from_string( self.invalid, 9437, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
