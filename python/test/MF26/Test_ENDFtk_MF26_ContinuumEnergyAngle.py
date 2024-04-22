# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26 import ContinuumEnergyAngle
from ENDFtk.MF26.LAW1 import LegendreCoefficients

class Test_ENDFtk_MF26_ContinuumEnergyAngle( unittest.TestCase ) :
    """Unit test for the ContinuumEnergyAngle class."""

    chunk = ( ' 0.000000+0 0.000000+0          1          2          1          2922826  5     \n'
              '          2          1                                            922826  5     \n'
              ' 0.000000+0 1.000000-5          0          1         12          4922826  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1922826  5     \n'
              ' 0.000000+0 2.000000+7          0          1          6          2922826  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    invalid = ( ' 5.000000-1 0.000000+0          4          2          1          2922826  5     \n'
                '          2          1                                            922826  5     \n'
                ' 0.000000+0 1.000000-5          0          1         12          4922826  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+1922826  5     \n'
                ' 0.000000+0 2.000000+7          0          1          6          2922826  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+0922826  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

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
            self.assertEqual( self.chunk, chunk.to_string( 9228, 26, 5 ) )

        # the data is given explicitly
        chunk = ContinuumEnergyAngle(
                    lep = 2, boundaries = [ 2 ], interpolants = [ 1 ],
                    distributions = [ LegendreCoefficients( 1e-5, 0, 1, [ 1., 4., 7., 10. ],
                                                            [ [ 2., 3. ], [ 5., 6. ],
                                                              [ 8., 9. ], [  11., 12. ] ] ),
                                      LegendreCoefficients( 2e+7, 0, 1, [ 1., 4. ],
                                                            [ [ 2., 3. ], [ 5., 6. ] ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ContinuumEnergyAngle.from_string( self.chunk, 9228, 26, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ContinuumEnergyAngle( chunk )

        verify_chunk( self, copy )

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

            chunk = ContinuumEnergyAngle.from_string( self.invalid, 9228, 26, 5 )

if __name__ == '__main__' :

    unittest.main()
