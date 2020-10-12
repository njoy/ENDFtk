# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import PartialDistribution
from ENDFtk.MF5 import Probability
from ENDFtk.MF5 import PartialDistribution
from ENDFtk.MF5 import Probability
from ENDFtk.MF5 import TabulatedSpectrum
from ENDFtk.MF5 import GeneralEvaporationSpectrum
from ENDFtk.MF5 import MaxwellianFissionSpectrum
from ENDFtk.MF5 import EvaporationSpectrum
from ENDFtk.MF5 import WattSpectrum
from ENDFtk.MF5 import MadlandNixSpectrum
from ENDFtk.MF5 import OutgoingEnergyDistribution
from ENDFtk.MF5 import Parameter
from ENDFtk.MF5 import EffectiveTemperature

class Test_ENDFtk_MF5_PartialDistribution( unittest.TestCase ) :
    """Unit test for the PartialDistribution class."""

    chunk_lf1 = ( ' 0.000000+0 0.000000+0          0          1          1          29437 5 18     \n'
                  '          2          2                                            9437 5 18     \n'
                  ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9437 5 18     \n'
                  ' 0.000000+0 0.000000+0          0          0          1          29437 5 18     \n'
                  '          2          4                                            9437 5 18     \n'
                  ' 0.000000+0 1.000000-5          0          0          1          39437 5 18     \n'
                  '          3          2                                            9437 5 18     \n'
                  ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-99437 5 18     \n'
                  ' 0.000000+0 3.000000+7          0          0          1          49437 5 18     \n'
                  '          4          2                                            9437 5 18     \n'
                  ' 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-99437 5 18     \n'
                  ' 3.000000+7 1.898849-9                                            9437 5 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          2          1          29222 5 18     \n'
                '          2          2                                            9222 5 18     \n'
                ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      9222 5 18     \n'
                ' 0.000000+0 0.000000+0          0          0          1          39222 5 18     \n'
                '          3          2                                            9222 5 18     \n'
                ' 1.000000-5 9.770000+5 1.500000+6 1.000000+6 3.000000+7 1.060000+69222 5 18     \n'
                ' 0.000000+0 0.000000+0          0          0          1          59222 5 18     \n'
                '          5          2                                            9222 5 18     \n'
                ' 1.000000-5 2.546000-6 1.500000+6 2.546000-6 1.000000+7 2.474000-69222 5 18     \n'
                ' 1.220000+7 2.612000-6 3.000000+7 2.620000-6                      9222 5 18     \n' )

    def test_component( self ) :

        def verify_chunk_lf1( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.U )
            self.assertAlmostEqual( 0.0, chunk.energy_limit_constant )

            p = chunk.probability

            self.assertEqual( 1, p.LF )
            self.assertEqual( 1, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = chunk.distribution

            self.assertEqual( True, isinstance( d, TabulatedSpectrum ) )

            self.assertEqual( 1, d.NR )
            self.assertEqual( 2, d.NE )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 2, d.boundaries[0] )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 4, d.interpolants[0] )

            self.assertEqual( 2, len( d.incident_energies ) )
            self.assertAlmostEqual( 1e-5, d.incident_energies[0] )
            self.assertAlmostEqual( 3e+7, d.incident_energies[1] )

            value = d.outgoing_distributions[0]
            self.assertAlmostEqual( 1e-5, value.incident_energy )
            self.assertEqual( 3, value.NP )
            self.assertEqual( 1, value.NR )
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

            value = d.outgoing_distributions[1]
            self.assertAlmostEqual( 3e+7, value.incident_energy )
            self.assertEqual( 4, value.NP )
            self.assertEqual( 1, value.NR )
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

            self.assertEqual( 12, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lf1, chunk.to_string( 9437, 5, 18 ) )

        # the data is given explicitly for lf=1 (arbitrary tabulated)
        chunk = PartialDistribution(
                  probability = Probability( 1, [ 2 ], [ 2 ],
                                             [ 1e-5, 3e+7 ],
                                             [ 1.0, 1.0 ] ),
                  distribution = TabulatedSpectrum(
                                     [ 2 ], [ 4 ],
                                     [ OutgoingEnergyDistribution(
                                           1e-5, [ 3 ], [ 2 ],
                                           [ 0.0, 1e+5, 3e+7 ],
                                           [ 0.0, 1.757570e-9, 1.843350e-9 ] ),
                                       OutgoingEnergyDistribution(
                                           3e+7, [ 4 ], [ 2 ],
                                           [ 0.0, 10., 11., 3e+7 ],
                                           [ 0.0, 1.733405e-9,
                                             1.818010e-9, 1.898849e-9 ] ) ] ) )

        verify_chunk_lf1( self, chunk )

        # the data is read from a string for lf=1 (arbitrary tabulated)
        chunk = PartialDistribution.from_string( self.chunk_lf1, 9437, 5, 18 )

        verify_chunk_lf1( self, chunk )

        # the data is copied for lf=1 (arbitrary tabulated)
        copy = PartialDistribution( chunk )

        verify_chunk_lf1( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = PartialDistribution( boundaries = [ 5 ],
                               interpolants = [ 1, 2 ],
                               energies = [ 1., 2., 3., 4., 5. ],
                               values = [ 6., 7., 8., 9., 10. ] )

        with self.assertRaises( Exception ) :

            chunk = PartialDistribution.from_string( self.invalid, 9437, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
