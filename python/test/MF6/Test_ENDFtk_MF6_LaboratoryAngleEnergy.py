# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import LaboratoryAngleEnergy
from ENDFtk.MF6.LAW7 import AngularDistribution
from ENDFtk.MF6.LAW7 import EnergyDistribution

class Test_ENDFtk_MF6_AngularDistribution( unittest.TestCase ) :
    """Unit test for the AngularDistribution class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          29228 6  5     \n'
              '          2          1                                            9228 6  5     \n'
              ' 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n'
              '          2          4                                            9228 6  5     \n'
              ' 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n'
              ' 3.000000+7 6.000000+0                                            9228 6  5     \n'
              ' 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n'
              '          3          2                                            9228 6  5     \n'
              ' 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n'
              ' 0.000000+0 2.000000+7          0          0          1          29228 6  5     \n'
              '          2          4                                            9228 6  5     \n'
              ' 0.000000+0 9.000000-1          0          0          1          49228 6  5     \n'
              '          4          2                                            9228 6  5     \n'
              ' 1.000000-5 1.000000+0 1.100000+7 3.000000+0 1.147000+7 5.000000+09228 6  5     \n'
              ' 3.000000+7 7.000000+0                                            9228 6  5     \n'
              ' 0.000000+0-9.000000-1          0          0          1          39228 6  5     \n'
              '          3          2                                            9228 6  5     \n'
              ' 1.000000-5 5.000000+0 1.000000+6 3.000000+0 3.000000+7 1.000000+09228 6  5     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          1          49228 6  5     \n'
                '          2          1                                            9228 6  5     \n'
                ' 0.000000+0 1.000000-5          0          0          1          29228 6  5     \n'
                '          2          4                                            9228 6  5     \n'
                ' 0.000000+0 1.000000+0          0          0          1          49228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 2.000000+0 1.147000+7 4.000000+09228 6  5     \n'
                ' 3.000000+7 6.000000+0                                            9228 6  5     \n'
                ' 0.000000+0-1.000000+0          0          0          1          39228 6  5     \n'
                '          3          2                                            9228 6  5     \n'
                ' 1.000000-5 6.000000+0 1.000000+6 4.000000+0 3.000000+7 2.000000+09228 6  5     \n'
                ' 0.000000+0 2.000000+7          0          0          1          29228 6  5     \n'
                '          2          4                                            9228 6  5     \n'
                ' 0.000000+0 9.000000-1          0          0          1          49228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 1.000000+0 1.100000+7 3.000000+0 1.147000+7 5.000000+09228 6  5     \n'
                ' 3.000000+7 7.000000+0                                            9228 6  5     \n'
                ' 0.000000+0-9.000000-1          0          0          1          39228 6  5     \n'
                '          3          2                                            9228 6  5     \n'
                ' 1.000000-5 5.000000+0 1.000000+6 3.000000+0 3.000000+7 1.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 7, chunk.LAW )

            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )

            self.assertAlmostEqual( 1e-5, chunk.angular_distributions[0].E )
            self.assertAlmostEqual( 1e-5, chunk.angular_distributions[0].incident_energy )

            self.assertEqual( 2, chunk.angular_distributions[0].NMU )
            self.assertEqual( 1, chunk.angular_distributions[0].NRM )
            self.assertEqual( 1, len( chunk.angular_distributions[0].interpolants ) )
            self.assertEqual( 1, len( chunk.angular_distributions[0].boundaries ) )
            self.assertEqual( 4, chunk.angular_distributions[0].interpolants[0] )
            self.assertEqual( 2, chunk.angular_distributions[0].boundaries[0] )

            cosines = chunk.angular_distributions[0].energy_distributions
            self.assertEqual( 2, len( cosines ) )

            self.assertAlmostEqual( 1., cosines[0].MU )
            self.assertAlmostEqual( 1., cosines[0].cosine )
            self.assertEqual( 1, cosines[0].NRP )
            self.assertEqual( 1, cosines[0].number_interpolation_regions )
            self.assertEqual( 4, cosines[0].NEP )
            self.assertEqual( 4, cosines[0].number_outgoing_energies )
            self.assertEqual( 1, len( cosines[0].INT ) )
            self.assertEqual( 1, len( cosines[0].NBT ) )
            self.assertEqual( 2, cosines[0].INT[0] )
            self.assertEqual( 4, cosines[0].NBT[0] )
            self.assertEqual( 1, len( cosines[0].interpolants ) )
            self.assertEqual( 1, len( cosines[0].boundaries ) )
            self.assertEqual( 2, cosines[0].interpolants[0] )
            self.assertEqual( 4, cosines[0].boundaries[0] )
            self.assertEqual( 4, len( cosines[0].EP ) )
            self.assertEqual( 4, len( cosines[0].energies ) )
            self.assertEqual( 4, len( cosines[0].F ) )
            self.assertEqual( 4, len( cosines[0].probabilities ) )
            self.assertAlmostEqual( 1e-5, cosines[0].EP[0] )
            self.assertAlmostEqual( 1.1e+7, cosines[0].EP[1] )
            self.assertAlmostEqual( 1.147e+7, cosines[0].EP[2] )
            self.assertAlmostEqual( 3e+7, cosines[0].EP[3] )
            self.assertAlmostEqual( 1e-5, cosines[0].energies[0] )
            self.assertAlmostEqual( 1.1e+7, cosines[0].energies[1] )
            self.assertAlmostEqual( 1.147e+7, cosines[0].energies[2] )
            self.assertAlmostEqual( 3e+7, cosines[0].energies[3] )
            self.assertAlmostEqual( 0., cosines[0].F[0] )
            self.assertAlmostEqual( 2., cosines[0].F[1] )
            self.assertAlmostEqual( 4., cosines[0].F[2] )
            self.assertAlmostEqual( 6., cosines[0].F[3] )
            self.assertAlmostEqual( 0., cosines[0].probabilities[0] )
            self.assertAlmostEqual( 2., cosines[0].probabilities[1] )
            self.assertAlmostEqual( 4., cosines[0].probabilities[2] )
            self.assertAlmostEqual( 6., cosines[0].probabilities[3] )

            self.assertAlmostEqual( -1., cosines[1].cosine )
            self.assertEqual( 1, cosines[1].NRP )
            self.assertEqual( 1, cosines[1].number_interpolation_regions )
            self.assertEqual( 3, cosines[1].NEP )
            self.assertEqual( 3, cosines[1].number_outgoing_energies )
            self.assertEqual( 1, len( cosines[1].INT ) )
            self.assertEqual( 1, len( cosines[1].NBT ) )
            self.assertEqual( 2, cosines[1].INT[0] )
            self.assertEqual( 3, cosines[1].NBT[0] )
            self.assertEqual( 1, len( cosines[1].interpolants ) )
            self.assertEqual( 1, len( cosines[1].boundaries ) )
            self.assertEqual( 2, cosines[1].interpolants[0] )
            self.assertEqual( 3, cosines[1].boundaries[0] )
            self.assertEqual( 3, len( cosines[1].EP ) )
            self.assertEqual( 3, len( cosines[1].energies ) )
            self.assertEqual( 3, len( cosines[1].F ) )
            self.assertEqual( 3, len( cosines[1].probabilities ) )
            self.assertAlmostEqual( 1e-5, cosines[1].EP[0] )
            self.assertAlmostEqual( 1e+6, cosines[1].EP[1] )
            self.assertAlmostEqual( 3e+7, cosines[1].EP[2] )
            self.assertAlmostEqual( 1e-5, cosines[1].energies[0] )
            self.assertAlmostEqual( 1e+6, cosines[1].energies[1] )
            self.assertAlmostEqual( 3e+7, cosines[1].energies[2] )
            self.assertAlmostEqual( 6., cosines[1].F[0] )
            self.assertAlmostEqual( 4., cosines[1].F[1] )
            self.assertAlmostEqual( 2., cosines[1].F[2] )
            self.assertAlmostEqual( 6., cosines[1].probabilities[0] )
            self.assertAlmostEqual( 4., cosines[1].probabilities[1] )
            self.assertAlmostEqual( 2., cosines[1].probabilities[2] )

            self.assertAlmostEqual( 2e+7, chunk.angular_distributions[1].E )
            self.assertAlmostEqual( 2e+7, chunk.angular_distributions[1].incident_energy )

            self.assertEqual( 2, chunk.angular_distributions[1].NMU )
            self.assertEqual( 2, chunk.angular_distributions[1].number_cosines )
            self.assertEqual( 1, chunk.angular_distributions[1].NRM )
            self.assertEqual( 1, chunk.angular_distributions[1].number_interpolation_regions )
            self.assertEqual( 1, len( chunk.angular_distributions[1].INT ) )
            self.assertEqual( 1, len( chunk.angular_distributions[1].NBT ) )
            self.assertEqual( 4, chunk.angular_distributions[1].INT[0] )
            self.assertEqual( 2, chunk.angular_distributions[1].NBT[0] )
            self.assertEqual( 1, len( chunk.angular_distributions[1].interpolants ) )
            self.assertEqual( 1, len( chunk.angular_distributions[1].boundaries ) )
            self.assertEqual( 4, chunk.angular_distributions[1].interpolants[0] )
            self.assertEqual( 2, chunk.angular_distributions[1].boundaries[0] )

            cosines = chunk.angular_distributions[1].energy_distributions
            self.assertEqual( 2, len( cosines ) )

            self.assertAlmostEqual( .9, cosines[0].cosine )
            self.assertEqual( 1, cosines[0].NRP )
            self.assertEqual( 1, cosines[0].number_interpolation_regions )
            self.assertEqual( 4, cosines[0].NEP )
            self.assertEqual( 4, cosines[0].number_outgoing_energies )
            self.assertEqual( 1, len( cosines[0].INT ) )
            self.assertEqual( 1, len( cosines[0].NBT ) )
            self.assertEqual( 2, cosines[0].INT[0] )
            self.assertEqual( 4, cosines[0].NBT[0] )
            self.assertEqual( 1, len( cosines[0].interpolants ) )
            self.assertEqual( 1, len( cosines[0].boundaries ) )
            self.assertEqual( 2, cosines[0].interpolants[0] )
            self.assertEqual( 4, cosines[0].boundaries[0] )
            self.assertEqual( 4, len( cosines[0].EP ) )
            self.assertEqual( 4, len( cosines[0].energies ) )
            self.assertEqual( 4, len( cosines[0].F ) )
            self.assertEqual( 4, len( cosines[0].probabilities ) )
            self.assertAlmostEqual( 1e-5, cosines[0].EP[0] )
            self.assertAlmostEqual( 1.1e+7, cosines[0].EP[1] )
            self.assertAlmostEqual( 1.147e+7, cosines[0].EP[2] )
            self.assertAlmostEqual( 3e+7, cosines[0].EP[3] )
            self.assertAlmostEqual( 1e-5, cosines[0].energies[0] )
            self.assertAlmostEqual( 1.1e+7, cosines[0].energies[1] )
            self.assertAlmostEqual( 1.147e+7, cosines[0].energies[2] )
            self.assertAlmostEqual( 3e+7, cosines[0].energies[3] )
            self.assertAlmostEqual( 1., cosines[0].F[0] )
            self.assertAlmostEqual( 3., cosines[0].F[1] )
            self.assertAlmostEqual( 5., cosines[0].F[2] )
            self.assertAlmostEqual( 7., cosines[0].F[3] )
            self.assertAlmostEqual( 1., cosines[0].probabilities[0] )
            self.assertAlmostEqual( 3., cosines[0].probabilities[1] )
            self.assertAlmostEqual( 5., cosines[0].probabilities[2] )
            self.assertAlmostEqual( 7., cosines[0].probabilities[3] )

            self.assertAlmostEqual( -.9, cosines[1].cosine )
            self.assertEqual( 1, cosines[1].NRP )
            self.assertEqual( 1, cosines[1].number_interpolation_regions )
            self.assertEqual( 3, cosines[1].NEP )
            self.assertEqual( 3, cosines[1].number_outgoing_energies )
            self.assertEqual( 1, len( cosines[1].INT ) )
            self.assertEqual( 1, len( cosines[1].NBT ) )
            self.assertEqual( 2, cosines[1].INT[0] )
            self.assertEqual( 3, cosines[1].NBT[0] )
            self.assertEqual( 1, len( cosines[1].interpolants ) )
            self.assertEqual( 1, len( cosines[1].boundaries ) )
            self.assertEqual( 2, cosines[1].interpolants[0] )
            self.assertEqual( 3, cosines[1].boundaries[0] )
            self.assertEqual( 3, len( cosines[1].EP ) )
            self.assertEqual( 3, len( cosines[1].energies ) )
            self.assertEqual( 3, len( cosines[1].F ) )
            self.assertEqual( 3, len( cosines[1].probabilities ) )
            self.assertAlmostEqual( 1e-5, cosines[1].EP[0] )
            self.assertAlmostEqual( 1e+6, cosines[1].EP[1] )
            self.assertAlmostEqual( 3e+7, cosines[1].EP[2] )
            self.assertAlmostEqual( 1e-5, cosines[1].energies[0] )
            self.assertAlmostEqual( 1e+6, cosines[1].energies[1] )
            self.assertAlmostEqual( 3e+7, cosines[1].energies[2] )
            self.assertAlmostEqual( 5., cosines[1].F[0] )
            self.assertAlmostEqual( 3., cosines[1].F[1] )
            self.assertAlmostEqual( 1., cosines[1].F[2] )
            self.assertAlmostEqual( 5., cosines[1].probabilities[0] )
            self.assertAlmostEqual( 3., cosines[1].probabilities[1] )
            self.assertAlmostEqual( 1., cosines[1].probabilities[2] )

            self.assertEqual( 20, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        boundaries = [ 2 ]
        interpolants = [ 1 ]
        distributions = [ AngularDistribution(
                            1e-5, [ 2 ], [ 4 ],
                            [ EnergyDistribution( 1.0, [ 4 ], [ 2 ],
                                                  [ 1e-5, 1.1e+7, 1.147e+7,
                                                    3e+7 ],
                                                  [ 0., 2., 4., 6. ] ),
                              EnergyDistribution( -1.0, [ 3 ], [ 2 ],
                                                  [ 1e-5, 1e+6, 3e+7 ],
                                                  [ 6., 4., 2. ] ) ] ),
                          AngularDistribution(
                            2e+7, [ 2 ], [ 4 ],
                            [ EnergyDistribution( 0.9, [ 4 ], [ 2 ],
                                                  [ 1e-5, 1.1e+7, 1.147e+7,
                                                    3e+7 ],
                                                  [ 1., 3., 5., 7. ] ),
                              EnergyDistribution( -0.9, [ 3 ], [ 2 ],
                                                  [ 1e-5, 1e+6, 3e+7 ],
                                                  [ 5., 3., 1. ] ) ] ) ]

        chunk = LaboratoryAngleEnergy( boundaries = boundaries,
                                       interpolants = interpolants,
                                       distributions = distributions )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LaboratoryAngleEnergy.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LaboratoryAngleEnergy( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            boundaries = [ 2, 4 ]
            interpolants = [ 1 ]
            distributions = [ AngularDistribution(
                                1e-5, [ 2 ], [ 4 ],
                                [ EnergyDistribution( 1.0, [ 4 ], [ 2 ],
                                                      [ 1e-5, 1.1e+7, 1.147e+7,
                                                        3e+7 ],
                                                      [ 0., 2., 4., 6. ] ),
                                  EnergyDistribution( -1.0, [ 3 ], [ 2 ],
                                                      [ 1e-5, 1e+6, 3e+7 ],
                                                      [ 6., 4., 2. ] ) ] ),
                              AngularDistribution(
                                2e+7, [ 2 ], [ 4 ],
                                [ EnergyDistribution( 0.9, [ 4 ], [ 2 ],
                                                      [ 1e-5, 1.1e+7, 1.147e+7,
                                                        3e+7 ],
                                                      [ 1., 3., 5., 7. ] ),
                                  EnergyDistribution( -0.9, [ 3 ], [ 2 ],
                                                      [ 1e-5, 1e+6, 3e+7 ],
                                                      [ 5., 3., 1. ] ) ] ) ]

            chunk = LaboratoryAngleEnergy( boundaries = boundaries,
                                           interpolants = interpolants,
                                           distributions = distributions )

        with self.assertRaises( Exception ) :

            chunk = LaboratoryAngleEnergy.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
