# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactReichMoore
from ENDFtk.MF32.MT151 import CompactReichMooreUncertainties
from ENDFtk.MF32.MT151 import CompactCorrelationMatrix

class Test_ENDFtk_MF32_MT151_CompactReichMoore( unittest.TestCase ) :
    """Unit test for the CompactReichMoore class."""

    chunk = ( ' 2.500000+0 9.620000-1          0          2          0          0922232151     \n'
              ' 2.310377+2 0.000000+0          0          0         24          2922232151     \n'
              '-1.060000+3 3.000000+0 1.524000+0 4.000000-2 2.600000-1 2.370000-1922232151     \n'
              ' 2.061000+0 0.000000+0 1.453063+0 3.999991-2 2.592466-1 2.362210-1922232151     \n'
              '-8.000000+2 2.000000+0 1.315000+0 4.000000-2 3.120000-1-2.250000-1922232151     \n'
              ' 1.891999+0 0.000000+0 1.268267+0 3.999987-2 3.106125-1 2.241766-1922232151     \n'
              ' 0.000000+0 0.000000+0          5         10          7          0922232151     \n'
              '    2    1   -120                                                 922232151     \n'
              '    4    1     -2  -937                                           922232151     \n'
              '    5    1     -2  -621     0   -38                               922232151     \n'
              '    6    2    -10                                                 922232151     \n'
              '    7    1     -9 -6134     0  -209   114  -139                   922232151     \n'
              '    8    2      2                                                 922232151     \n'
              '    9    2    324     0    17     3    -3  -748                   922232151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 3, chunk.LRF )
            self.assertEqual( 3, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )
            self.assertEqual( 2, chunk.LCOMP )
            self.assertEqual( 2, chunk.covariance_representation )

            self.assertAlmostEqual( 2.5, chunk.SPI )
            self.assertAlmostEqual( 2.5, chunk.spin )
            self.assertAlmostEqual( 0.962, chunk.AP )
            self.assertAlmostEqual( 0.962, chunk.scattering_radius )
            self.assertEqual( False, chunk.LAD )
            self.assertEqual( False, chunk.angular_distributions_flag )

            self.assertEqual( None, chunk.DAP )
            self.assertEqual( None, chunk.scattering_radius_uncertainty )
            self.assertEqual( False, chunk.ISR )
            self.assertEqual( False, chunk.scattering_radius_uncertainty_flag )

            self.assertAlmostEqual( 231.0377, chunk.uncertainties.AWRI )
            self.assertAlmostEqual( 231.0377, chunk.uncertainties.atomic_weight_ratio )
            self.assertAlmostEqual( 0., chunk.uncertainties.APL )
            self.assertAlmostEqual( 0., chunk.uncertainties.l_dependent_scattering_radius )

            self.assertEqual( 2, chunk.uncertainties.NRSA )
            self.assertEqual( 2, chunk.uncertainties.number_resonances )
            self.assertEqual( 2, len( chunk.uncertainties.ER ) )
            self.assertEqual( 2, len( chunk.uncertainties.resonance_energies ) )
            self.assertEqual( 2, len( chunk.uncertainties.AJ ) )
            self.assertEqual( 2, len( chunk.uncertainties.spin_values ) )
            self.assertEqual( 2, len( chunk.uncertainties.GN ) )
            self.assertEqual( 2, len( chunk.uncertainties.neutron_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GG ) )
            self.assertEqual( 2, len( chunk.uncertainties.gamma_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GFA ) )
            self.assertEqual( 2, len( chunk.uncertainties.first_fission_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GFB ) )
            self.assertEqual( 2, len( chunk.uncertainties.second_fission_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.DER ) )
            self.assertEqual( 2, len( chunk.uncertainties.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGN ) )
            self.assertEqual( 2, len( chunk.uncertainties.neutron_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGG ) )
            self.assertEqual( 2, len( chunk.uncertainties.gamma_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGFA ) )
            self.assertEqual( 2, len( chunk.uncertainties.first_fission_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGFB ) )
            self.assertEqual( 2, len( chunk.uncertainties.second_fission_width_uncertainties ) )

            self.assertAlmostEqual( -1.060000e+3, chunk.uncertainties.ER[0] )
            self.assertAlmostEqual( -8.000000e+2, chunk.uncertainties.ER[1] )
            self.assertAlmostEqual( -1.060000e+3, chunk.uncertainties.resonance_energies[0] )
            self.assertAlmostEqual( -8.000000e+2, chunk.uncertainties.resonance_energies[1] )
            self.assertAlmostEqual( 3., chunk.uncertainties.AJ[0] )
            self.assertAlmostEqual( 2., chunk.uncertainties.AJ[1] )
            self.assertAlmostEqual( 3., chunk.uncertainties.spin_values[0] )
            self.assertAlmostEqual( 2., chunk.uncertainties.spin_values[1] )
            self.assertAlmostEqual( 1.524000e+0, chunk.uncertainties.GN[0] )
            self.assertAlmostEqual( 1.315000e+0, chunk.uncertainties.GN[1] )
            self.assertAlmostEqual( 1.524000e+0, chunk.uncertainties.neutron_widths[0] )
            self.assertAlmostEqual( 1.315000e+0, chunk.uncertainties.neutron_widths[1] )
            self.assertAlmostEqual( .04, chunk.uncertainties.GG[0] )
            self.assertAlmostEqual( .04, chunk.uncertainties.GG[1] )
            self.assertAlmostEqual( .04, chunk.uncertainties.gamma_widths[0] )
            self.assertAlmostEqual( .04, chunk.uncertainties.gamma_widths[1] )
            self.assertAlmostEqual( 2.600000e-1, chunk.uncertainties.GFA[0] )
            self.assertAlmostEqual( 3.120000e-1, chunk.uncertainties.GFA[1] )
            self.assertAlmostEqual( 2.600000e-1, chunk.uncertainties.first_fission_widths[0] )
            self.assertAlmostEqual( 3.120000e-1, chunk.uncertainties.first_fission_widths[1] )
            self.assertAlmostEqual(  2.370000e-1, chunk.uncertainties.GFB[0] )
            self.assertAlmostEqual( -2.250000e-1, chunk.uncertainties.GFB[1] )
            self.assertAlmostEqual(  2.370000e-1, chunk.uncertainties.second_fission_widths[0] )
            self.assertAlmostEqual( -2.250000e-1, chunk.uncertainties.second_fission_widths[1] )

            self.assertAlmostEqual( 2.061000e+0, chunk.uncertainties.DER[0] )
            self.assertAlmostEqual( 1.891999e+0, chunk.uncertainties.DER[1] )
            self.assertAlmostEqual( 2.061000e+0, chunk.uncertainties.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 1.891999e+0, chunk.uncertainties.resonance_energy_uncertainties[1] )
            self.assertAlmostEqual( 1.453063e+0, chunk.uncertainties.DGN[0] )
            self.assertAlmostEqual( 1.268267e+0, chunk.uncertainties.DGN[1] )
            self.assertAlmostEqual( 1.453063e+0, chunk.uncertainties.neutron_width_uncertainties[0] )
            self.assertAlmostEqual( 1.268267e+0, chunk.uncertainties.neutron_width_uncertainties[1] )
            self.assertAlmostEqual( 3.999991e-2, chunk.uncertainties.DGG[0] )
            self.assertAlmostEqual( 3.999987e-2, chunk.uncertainties.DGG[1] )
            self.assertAlmostEqual( 3.999991e-2, chunk.uncertainties.gamma_width_uncertainties[0] )
            self.assertAlmostEqual( 3.999987e-2, chunk.uncertainties.gamma_width_uncertainties[1] )
            self.assertAlmostEqual( 2.592466e-1, chunk.uncertainties.DGFA[0] )
            self.assertAlmostEqual( 3.106125e-1, chunk.uncertainties.DGFA[1] )
            self.assertAlmostEqual( 2.592466e-1, chunk.uncertainties.first_fission_width_uncertainties[0] )
            self.assertAlmostEqual( 3.106125e-1, chunk.uncertainties.first_fission_width_uncertainties[1] )
            self.assertAlmostEqual( 2.362210e-1, chunk.uncertainties.DGFB[0] )
            self.assertAlmostEqual( 2.241766e-1, chunk.uncertainties.DGFB[1] )
            self.assertAlmostEqual( 2.362210e-1, chunk.uncertainties.second_fission_width_uncertainties[0] )
            self.assertAlmostEqual( 2.241766e-1, chunk.uncertainties.second_fission_width_uncertainties[1] )

            self.assertEqual( 5, chunk.correlation_matrix.NDIGIT )
            self.assertEqual( 5, chunk.correlation_matrix.number_digits )
            self.assertEqual( 10, chunk.correlation_matrix.NNN )
            self.assertEqual( 10, chunk.correlation_matrix.order )
            self.assertEqual( 18, len( chunk.correlation_matrix.I ) )
            self.assertEqual( 18, len( chunk.correlation_matrix.J ) )
            self.assertEqual( 18, len( chunk.correlation_matrix.correlations ) )

            self.assertEqual( 2, chunk.correlation_matrix.I[0] )
            self.assertEqual( 4, chunk.correlation_matrix.I[1] )
            self.assertEqual( 4, chunk.correlation_matrix.I[2] )
            self.assertEqual( 5, chunk.correlation_matrix.I[3] )
            self.assertEqual( 5, chunk.correlation_matrix.I[4] )
            self.assertEqual( 5, chunk.correlation_matrix.I[5] )
            self.assertEqual( 6, chunk.correlation_matrix.I[6] )
            self.assertEqual( 7, chunk.correlation_matrix.I[7] )
            self.assertEqual( 7, chunk.correlation_matrix.I[8] )
            self.assertEqual( 7, chunk.correlation_matrix.I[9] )
            self.assertEqual( 7, chunk.correlation_matrix.I[10] )
            self.assertEqual( 7, chunk.correlation_matrix.I[11] )
            self.assertEqual( 8, chunk.correlation_matrix.I[12] )
            self.assertEqual( 9, chunk.correlation_matrix.I[13] )
            self.assertEqual( 9, chunk.correlation_matrix.I[14] )
            self.assertEqual( 9, chunk.correlation_matrix.I[15] )
            self.assertEqual( 9, chunk.correlation_matrix.I[16] )
            self.assertEqual( 9, chunk.correlation_matrix.I[17] )

            self.assertEqual( 1, chunk.correlation_matrix.J[0] )
            self.assertEqual( 1, chunk.correlation_matrix.J[1] )
            self.assertEqual( 2, chunk.correlation_matrix.J[2] )
            self.assertEqual( 1, chunk.correlation_matrix.J[3] )
            self.assertEqual( 2, chunk.correlation_matrix.J[4] )
            self.assertEqual( 4, chunk.correlation_matrix.J[5] )
            self.assertEqual( 2, chunk.correlation_matrix.J[6] )
            self.assertEqual( 1, chunk.correlation_matrix.J[7] )
            self.assertEqual( 2, chunk.correlation_matrix.J[8] )
            self.assertEqual( 4, chunk.correlation_matrix.J[9] )
            self.assertEqual( 5, chunk.correlation_matrix.J[10] )
            self.assertEqual( 6, chunk.correlation_matrix.J[11] )
            self.assertEqual( 2, chunk.correlation_matrix.J[12] )
            self.assertEqual( 2, chunk.correlation_matrix.J[13] )
            self.assertEqual( 4, chunk.correlation_matrix.J[14] )
            self.assertEqual( 5, chunk.correlation_matrix.J[15] )
            self.assertEqual( 6, chunk.correlation_matrix.J[16] )
            self.assertEqual( 7, chunk.correlation_matrix.J[17] )

            self.assertAlmostEqual(  -1205e-6, chunk.correlation_matrix.correlations[0] )
            self.assertAlmostEqual(    -25e-6, chunk.correlation_matrix.correlations[1] )
            self.assertAlmostEqual(  -9375e-6, chunk.correlation_matrix.correlations[2] )
            self.assertAlmostEqual(    -25e-6, chunk.correlation_matrix.correlations[3] )
            self.assertAlmostEqual(  -6215e-6, chunk.correlation_matrix.correlations[4] )
            self.assertAlmostEqual(   -385e-6, chunk.correlation_matrix.correlations[5] )
            self.assertAlmostEqual(   -105e-6, chunk.correlation_matrix.correlations[6] )
            self.assertAlmostEqual(    -95e-6, chunk.correlation_matrix.correlations[7] )
            self.assertAlmostEqual( -61345e-6, chunk.correlation_matrix.correlations[8] )
            self.assertAlmostEqual(  -2095e-6, chunk.correlation_matrix.correlations[9] )
            self.assertAlmostEqual(   1145e-6, chunk.correlation_matrix.correlations[10] )
            self.assertAlmostEqual(  -1395e-6, chunk.correlation_matrix.correlations[11] )
            self.assertAlmostEqual(     25e-6, chunk.correlation_matrix.correlations[12] )
            self.assertAlmostEqual(   3245e-6, chunk.correlation_matrix.correlations[13] )
            self.assertAlmostEqual(    175e-6, chunk.correlation_matrix.correlations[14] )
            self.assertAlmostEqual(     35e-6, chunk.correlation_matrix.correlations[15] )
            self.assertAlmostEqual(    -35e-6, chunk.correlation_matrix.correlations[16] )
            self.assertAlmostEqual(  -7485e-6, chunk.correlation_matrix.correlations[17] )

            self.assertEqual( 14, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9222, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactReichMoore(
                  spi = 2.5, ap = 0.962, lad = False,
                  parameters = CompactReichMooreUncertainties(
                                   231.0377, 0.,
                                   [ -1.060000e+3, -8.000000e+2 ], [ 3., 2. ],
                                   [ 1.524000e+0, 1.315000e+0 ], [ 0.04, 0.04 ],
                                   [ 2.600000e-1, 3.120000e-1 ], [  2.370000e-1, -2.250000e-1 ],
                                   [ 2.061000e+0, 1.891999e+0 ],
                                   [ 1.453063e+0, 1.268267e+0 ], [ 3.999991e-2, 3.999987e-2 ],
                                   [ 2.592466e-1, 3.106125e-1 ], [ 2.362210e-1, 2.241766e-1 ] ),
                  matrix = CompactCorrelationMatrix(
                               10,
                               [ 2, 4, 4, 5, 5, 5, 6, 7, 7, 7,
                                 7, 7, 8, 9, 9, 9, 9, 9 ],
                               [ 1, 1, 2, 1, 2, 4, 2, 1, 2, 4,
                                 5, 6, 2, 2, 4, 5, 6, 7 ],
                               [ -1205e-6,   -25e-6, -9375e-6,   -25e-6, -6215e-6,
                                  -385e-6,  -105e-6,   -95e-6, -61345e-6, -2095e-6,
                                  1145e-6, -1395e-6,    25e-6,  3245e-6,   175e-6,
                                   35e-6,   -35e-6, -7485e-6 ], 5 ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactReichMoore.from_string( self.chunk, 9222, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactReichMoore( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
