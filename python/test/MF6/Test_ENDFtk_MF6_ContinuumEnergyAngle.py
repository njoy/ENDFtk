# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import ContinuumEnergyAngle
from ENDFtk.MF6.LAW1 import LegendreCoefficients
from ENDFtk.MF6.LAW1 import TabulatedDistribution
from ENDFtk.MF6.LAW1 import KalbachMann

class Test_ENDFtk_MF6_ContinuumEnergyAngle( unittest.TestCase ) :
    """Unit test for the ContinuumEnergyAngle class."""

    chunk_lang1 = ( ' 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n'
                    '          2          1                                            9228 6  5     \n'
                    ' 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n'
                    ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                    ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                    ' 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n'
                    ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    chunk_lang2 = ( ' 0.000000+0 0.000000+0          2          2          1          29228 6  5     \n'
                    '          2          1                                            9228 6  5     \n'
                    ' 0.000000+0 1.000000-5          0          1          6          29228 6  5     \n'
                    ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                    ' 0.000000+0 2.000000+7          0          2          8          29228 6  5     \n'
                    ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                    ' 1.300000+1 1.400000+1                                            9228 6  5     \n' )

    chunk_lang14 = ( ' 0.000000+0 0.000000+0         14          2          1          29228 6  5     \n'
                     '          2          1                                            9228 6  5     \n'
                     ' 0.000000+0 1.000000-5          0          4         12          29228 6  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                     ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                     ' 0.000000+0 2.000000+7          0          4         12          29228 6  5     \n'
                     ' 1.300000+1 1.400000+1 1.500000+1 1.600000+1 1.700000+1 1.800000+19228 6  5     \n'
                     ' 1.900000+1 2.000000+1 2.100000+1 2.200000+1 2.300000+1 2.400000+19228 6  5     \n' )

    invalid = ( ' 5.000000-1 0.000000+0          4          2          1          29228 6  5     \n'
                '          2          1                                            9228 6  5     \n'
                ' 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                ' 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk_lang1( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( 2, chunk.LEP )
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

            energies = chunk.distributions
            self.assertEqual( True, isinstance( energies[0], LegendreCoefficients ) )
            self.assertEqual( True, isinstance( energies[1], LegendreCoefficients ) )

            subsection1 = energies[0]
            self.assertAlmostEqual( 1e-5, subsection1.E )
            self.assertAlmostEqual( 1e-5, subsection1.incident_energy )
            self.assertEqual( 1, subsection1.LANG )
            self.assertEqual( 1, subsection1.representation )
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 1, subsection1.NA )
            self.assertEqual( 1, subsection1.number_angular_parameters )
            self.assertEqual( 12, subsection1.NW )
            self.assertEqual( 4, subsection1.NEP )
            self.assertEqual( 4, subsection1.number_secondary_energies )
            self.assertEqual( 4, len( subsection1.EP ) )
            self.assertEqual( 4, len( subsection1.energies ) )
            self.assertAlmostEqual( 1., subsection1.EP[0] )
            self.assertAlmostEqual( 4., subsection1.EP[1] )
            self.assertAlmostEqual( 7., subsection1.EP[2] )
            self.assertAlmostEqual( 10., subsection1.EP[3] )
            self.assertAlmostEqual( 1., subsection1.energies[0] )
            self.assertAlmostEqual( 4., subsection1.energies[1] )
            self.assertAlmostEqual( 7., subsection1.energies[2] )
            self.assertAlmostEqual( 10., subsection1.energies[3] )
            self.assertEqual( 4, len( subsection1.A ) )
            self.assertEqual( 4, len( subsection1.coefficients ) )
            self.assertAlmostEqual( 2., subsection1.A[0][0] )
            self.assertAlmostEqual( 3., subsection1.A[0][1] )
            self.assertAlmostEqual( 5., subsection1.A[1][0] )
            self.assertAlmostEqual( 6., subsection1.A[1][1] )
            self.assertAlmostEqual( 8., subsection1.A[2][0] )
            self.assertAlmostEqual( 9., subsection1.A[2][1] )
            self.assertAlmostEqual( 11., subsection1.A[3][0] )
            self.assertAlmostEqual( 12., subsection1.A[3][1] )
            self.assertAlmostEqual( 2., subsection1.coefficients[0][0] )
            self.assertAlmostEqual( 3., subsection1.coefficients[0][1] )
            self.assertAlmostEqual( 5., subsection1.coefficients[1][0] )
            self.assertAlmostEqual( 6., subsection1.coefficients[1][1] )
            self.assertAlmostEqual( 8., subsection1.coefficients[2][0] )
            self.assertAlmostEqual( 9., subsection1.coefficients[2][1] )
            self.assertAlmostEqual( 11., subsection1.coefficients[3][0] )
            self.assertAlmostEqual( 12., subsection1.coefficients[3][1] )
            self.assertEqual( 4, len( subsection1.F0 ) )
            self.assertEqual( 4, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection1.F0[0] )
            self.assertAlmostEqual( 5., subsection1.F0[1] )
            self.assertAlmostEqual( 8., subsection1.F0[2] )
            self.assertAlmostEqual( 11., subsection1.F0[3] )
            self.assertAlmostEqual( 2., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., subsection1.total_emission_probabilities[1] )
            self.assertAlmostEqual( 8., subsection1.total_emission_probabilities[2] )
            self.assertAlmostEqual( 11., subsection1.total_emission_probabilities[3] )

            subsection2 = energies[1]
            self.assertAlmostEqual( 2e+7, subsection2.E )
            self.assertAlmostEqual( 2e+7, subsection2.incident_energy )
            self.assertEqual( 1, subsection2.LANG )
            self.assertEqual( 1, subsection2.representation )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 1, subsection2.NA )
            self.assertEqual( 1, subsection2.number_angular_parameters )
            self.assertEqual( 6, subsection2.NW )
            self.assertEqual( 2, subsection2.NEP )
            self.assertEqual( 2, subsection2.number_secondary_energies )
            self.assertEqual( 2, len( subsection2.EP ) )
            self.assertEqual( 2, len( subsection2.energies ) )
            self.assertAlmostEqual( 1., subsection2.EP[0] )
            self.assertAlmostEqual( 4., subsection2.EP[1] )
            self.assertAlmostEqual( 1., subsection2.energies[0] )
            self.assertAlmostEqual( 4., subsection2.energies[1] )
            self.assertEqual( 2, len( subsection2.A ) )
            self.assertEqual( 2, len( subsection2.coefficients ) )
            self.assertAlmostEqual( 2., subsection2.A[0][0] )
            self.assertAlmostEqual( 3., subsection2.A[0][1] )
            self.assertAlmostEqual( 5., subsection2.A[1][0] )
            self.assertAlmostEqual( 6., subsection2.A[1][1] )
            self.assertAlmostEqual( 2., subsection2.coefficients[0][0] )
            self.assertAlmostEqual( 3., subsection2.coefficients[0][1] )
            self.assertAlmostEqual( 5., subsection2.coefficients[1][0] )
            self.assertAlmostEqual( 6., subsection2.coefficients[1][1] )
            self.assertEqual( 2, len( subsection2.F0 ) )
            self.assertEqual( 2, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection2.F0[0] )
            self.assertAlmostEqual( 5., subsection2.F0[1] )
            self.assertAlmostEqual( 2., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., subsection2.total_emission_probabilities[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lang1, chunk.to_string( 9228, 6, 5 ) )

        def verify_chunk_lang2( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( 2, chunk.LEP )
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

            energies = chunk.distributions
            self.assertEqual( True, isinstance( energies[0], KalbachMann ) )
            self.assertEqual( True, isinstance( energies[1], KalbachMann ) )

            subsection1 = energies[0]
            self.assertAlmostEqual( 1e-5, subsection1.E )
            self.assertAlmostEqual( 1e-5, subsection1.incident_energy )
            self.assertEqual( 2, subsection1.LANG )
            self.assertEqual( 2, subsection1.representation )
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 1, subsection1.NA )
            self.assertEqual( 1, subsection1.number_angular_parameters )
            self.assertEqual( 6, subsection1.NW )
            self.assertEqual( 2, subsection1.NEP )
            self.assertEqual( 2, subsection1.number_secondary_energies )
            self.assertEqual( 2, len( subsection1.EP ) )
            self.assertEqual( 2, len( subsection1.energies ) )
            self.assertAlmostEqual( 1., subsection1.EP[0] )
            self.assertAlmostEqual( 4., subsection1.EP[1] )
            self.assertAlmostEqual( 1., subsection1.energies[0] )
            self.assertAlmostEqual( 4., subsection1.energies[1] )
            self.assertEqual( 2, len( subsection1.parameters ) )
            self.assertAlmostEqual( 2., subsection1.parameters[0][0] )
            self.assertAlmostEqual( 3., subsection1.parameters[0][1] )
            self.assertAlmostEqual( 5., subsection1.parameters[1][0] )
            self.assertAlmostEqual( 6., subsection1.parameters[1][1] )
            self.assertEqual( 2, len( subsection1.F0 ) )
            self.assertEqual( 2, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection1.F0[0] )
            self.assertAlmostEqual( 5., subsection1.F0[1] )
            self.assertAlmostEqual( 2., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 5., subsection1.total_emission_probabilities[1] )

            subsection2 = energies[1]
            self.assertAlmostEqual( 2e+7, subsection2.E )
            self.assertAlmostEqual( 2e+7, subsection2.incident_energy )
            self.assertEqual( 2, subsection2.LANG )
            self.assertEqual( 2, subsection2.representation )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 2, subsection2.NA )
            self.assertEqual( 2, subsection2.number_angular_parameters )
            self.assertEqual( 8, subsection2.NW )
            self.assertEqual( 2, subsection2.NEP )
            self.assertEqual( 2, subsection2.number_secondary_energies )
            self.assertEqual( 2, len( subsection2.EP ) )
            self.assertEqual( 2, len( subsection2.energies ) )
            self.assertAlmostEqual( 7., subsection2.EP[0] )
            self.assertAlmostEqual( 11., subsection2.EP[1] )
            self.assertAlmostEqual( 7., subsection2.energies[0] )
            self.assertAlmostEqual( 11., subsection2.energies[1] )
            self.assertEqual( 2, len( subsection2.parameters ) )
            self.assertAlmostEqual( 8., subsection2.parameters[0][0] )
            self.assertAlmostEqual( 9., subsection2.parameters[0][1] )
            self.assertAlmostEqual( 10., subsection2.parameters[0][2] )
            self.assertAlmostEqual( 12., subsection2.parameters[1][0] )
            self.assertAlmostEqual( 13., subsection2.parameters[1][1] )
            self.assertAlmostEqual( 14., subsection2.parameters[1][2] )
            self.assertEqual( 2, len( subsection2.F0 ) )
            self.assertEqual( 2, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 8., subsection2.F0[0] )
            self.assertAlmostEqual( 12., subsection2.F0[1] )
            self.assertAlmostEqual( 8., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 12., subsection2.total_emission_probabilities[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lang2, chunk.to_string( 9228, 6, 5 ) )

        def verify_chunk_lang14( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( 2, chunk.LEP )
            self.assertEqual( 2, chunk.NE )
            self.assertEqual( 2, chunk.number_incident_energies )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 1, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )

            energies = chunk.distributions
            self.assertEqual( True, isinstance( energies[0], TabulatedDistribution ) )
            self.assertEqual( True, isinstance( energies[1], TabulatedDistribution ) )

            subsection1 = energies[0]
            self.assertAlmostEqual( 1e-5, subsection1.E )
            self.assertAlmostEqual( 1e-5, subsection1.incident_energy )
            self.assertEqual( 14, subsection1.LANG )
            self.assertEqual( 14, subsection1.representation )
            self.assertEqual( 0, subsection1.ND )
            self.assertEqual( 0, subsection1.number_discrete_energies )
            self.assertEqual( 4, subsection1.NA )
            self.assertEqual( 4, subsection1.number_angular_parameters )
            self.assertEqual( 12, subsection1.NW )
            self.assertEqual( 2, subsection1.NEP )
            self.assertEqual( 2, subsection1.number_secondary_energies )
            self.assertEqual( 2, len( subsection1.EP ) )
            self.assertEqual( 2, len( subsection1.energies ) )
            self.assertAlmostEqual( 1., subsection1.EP[0] )
            self.assertAlmostEqual( 7., subsection1.EP[1] )
            self.assertAlmostEqual( 1., subsection1.energies[0] )
            self.assertAlmostEqual( 7., subsection1.energies[1] )
            self.assertEqual( 2, len( subsection1.F0 ) )
            self.assertEqual( 2, len( subsection1.total_emission_probabilities ) )
            self.assertAlmostEqual( 2., subsection1.F0[0] )
            self.assertAlmostEqual( 8., subsection1.F0[1] )
            self.assertAlmostEqual( 2., subsection1.total_emission_probabilities[0] )
            self.assertAlmostEqual( 8., subsection1.total_emission_probabilities[1] )
            self.assertEqual( 2, len( subsection1.MU ) )
            self.assertEqual( 2, len( subsection1.cosines ) )
            self.assertAlmostEqual( 3., subsection1.MU[0][0] )
            self.assertAlmostEqual( 5., subsection1.MU[0][1] )
            self.assertAlmostEqual( 9., subsection1.MU[1][0] )
            self.assertAlmostEqual( 11., subsection1.MU[1][1] )
            self.assertAlmostEqual( 3., subsection1.cosines[0][0] )
            self.assertAlmostEqual( 5., subsection1.cosines[0][1] )
            self.assertAlmostEqual( 9., subsection1.cosines[1][0] )
            self.assertAlmostEqual( 11., subsection1.cosines[1][1] )
            self.assertEqual( 2, len( subsection1.F ) )
            self.assertEqual( 2, len( subsection1.probabilities ) )
            self.assertAlmostEqual( 4., subsection1.F[0][0] )
            self.assertAlmostEqual( 6., subsection1.F[0][1] )
            self.assertAlmostEqual( 10., subsection1.F[1][0] )
            self.assertAlmostEqual( 12., subsection1.F[1][1] )
            self.assertAlmostEqual( 4., subsection1.probabilities[0][0] )
            self.assertAlmostEqual( 6., subsection1.probabilities[0][1] )
            self.assertAlmostEqual( 10., subsection1.probabilities[1][0] )
            self.assertAlmostEqual( 12., subsection1.probabilities[1][1] )

            subsection2 = energies[1]
            self.assertAlmostEqual( 2e+7, subsection2.E )
            self.assertAlmostEqual( 2e+7, subsection2.incident_energy )
            self.assertEqual( 14, subsection2.LANG )
            self.assertEqual( 0, subsection2.ND )
            self.assertEqual( 0, subsection2.number_discrete_energies )
            self.assertEqual( 4, subsection2.NA )
            self.assertEqual( 4, subsection2.number_angular_parameters )
            self.assertEqual( 12, subsection2.NW )
            self.assertEqual( 2, subsection2.NEP )
            self.assertEqual( 2, subsection2.number_secondary_energies )
            self.assertEqual( 2, len( subsection2.EP ) )
            self.assertEqual( 2, len( subsection2.energies ) )
            self.assertAlmostEqual( 13., subsection2.EP[0] )
            self.assertAlmostEqual( 19., subsection2.EP[1] )
            self.assertAlmostEqual( 13., subsection2.energies[0] )
            self.assertAlmostEqual( 19., subsection2.energies[1] )
            self.assertEqual( 2, len( subsection2.F0 ) )
            self.assertEqual( 2, len( subsection2.total_emission_probabilities ) )
            self.assertAlmostEqual( 14., subsection2.F0[0] )
            self.assertAlmostEqual( 20., subsection2.F0[1] )
            self.assertAlmostEqual( 14., subsection2.total_emission_probabilities[0] )
            self.assertAlmostEqual( 20., subsection2.total_emission_probabilities[1] )
            self.assertEqual( 2, len( subsection2.MU ) )
            self.assertEqual( 2, len( subsection2.cosines ) )
            self.assertAlmostEqual( 15., subsection2.MU[0][0] )
            self.assertAlmostEqual( 17., subsection2.MU[0][1] )
            self.assertAlmostEqual( 21., subsection2.MU[1][0] )
            self.assertAlmostEqual( 23., subsection2.MU[1][1] )
            self.assertAlmostEqual( 15., subsection2.cosines[0][0] )
            self.assertAlmostEqual( 17., subsection2.cosines[0][1] )
            self.assertAlmostEqual( 21., subsection2.cosines[1][0] )
            self.assertAlmostEqual( 23., subsection2.cosines[1][1] )
            self.assertEqual( 2, len( subsection2.F ) )
            self.assertEqual( 2, len( subsection2.probabilities ) )
            self.assertAlmostEqual( 16., subsection2.F[0][0] )
            self.assertAlmostEqual( 18., subsection2.F[0][1] )
            self.assertAlmostEqual( 22., subsection2.F[1][0] )
            self.assertAlmostEqual( 24., subsection2.F[1][1] )
            self.assertAlmostEqual( 16., subsection2.probabilities[0][0] )
            self.assertAlmostEqual( 18., subsection2.probabilities[0][1] )
            self.assertAlmostEqual( 22., subsection2.probabilities[1][0] )
            self.assertAlmostEqual( 24., subsection2.probabilities[1][1] )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lang14, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = ContinuumEnergyAngle(
                    lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [ LegendreCoefficients( 1e-5, 0, 1, [ 1., 4., 7., 10. ],
                                                            [ [ 2., 3. ], [ 5., 6. ],
                                                              [ 8., 9. ], [  11., 12. ] ] ),
                                      LegendreCoefficients( 2e+7, 0, 1, [ 1., 4. ],
                                                            [ [ 2., 3. ], [ 5., 6. ] ] ) ] )

        verify_chunk_lang1( self, chunk )

        # the data is read from a string
        chunk = ContinuumEnergyAngle.from_string( self.chunk_lang1, 9228, 6, 5 )

        verify_chunk_lang1( self, chunk )

        # the data is copied
        copy = ContinuumEnergyAngle( chunk )

        verify_chunk_lang1( self, copy )

        # the data is given explicitly
        chunk = ContinuumEnergyAngle(
                    lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [ KalbachMann( 1e-5, 0, [ [1., 2., 3.], [4., 5., 6.] ] ),
                                      KalbachMann( 2e+7, 0, [ [7., 8., 9., 10.], [11., 12., 13., 14.] ] ) ] )

        verify_chunk_lang2( self, chunk )

        # the data is copied
        copy = ContinuumEnergyAngle( chunk )

        verify_chunk_lang2( self, copy )

        # the data is given explicitly
        chunk = ContinuumEnergyAngle(
                    lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [ TabulatedDistribution( 14, 1e-5, 0, 4,
                                                             [  1.,  7. ],  [ 2., 8. ],
                                                             [ [ 3., 5. ], [ 9., 11. ] ],
                                                             [ [ 4., 6. ], [ 10., 12. ] ] ),
                                      TabulatedDistribution( 14, 2e+7, 0, 4,
                                                             [  13.,  19. ],  [ 14., 20. ],
                                                             [ [ 15., 17. ], [ 21., 23. ] ],
                                                             [ [ 16., 18. ], [ 22., 24. ] ] ) ] )

        verify_chunk_lang14( self, chunk )

        # the data is read from a string
        chunk = ContinuumEnergyAngle.from_string( self.chunk_lang14, 9228, 6, 5 )

        verify_chunk_lang14( self, chunk )

        # the data is copied
        copy = ContinuumEnergyAngle( chunk )

        verify_chunk_lang14( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = ContinuumEnergyAngle(
                        lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                        distributions = [ LegendreCoefficients( 1e-5, 0, 1, [ 1., 4., 7., 10. ],
                                                                [ [ 2., 3. ], [ 5., 6. ],
                                                                  [ 8., 9. ], [  11., 12. ] ] ),
                                          TabulatedDistribution( 14, 2e+7, 0, 4,
                                                                 [  13.,  19. ],  [ 14., 20. ],
                                                                 [ [ 15., 17. ], [ 21., 23. ] ],
                                                                 [ [ 16., 18. ], [ 22., 24. ] ] ) ] )

        with self.assertRaises( Exception ) :

            chunk = ContinuumEnergyAngle.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
