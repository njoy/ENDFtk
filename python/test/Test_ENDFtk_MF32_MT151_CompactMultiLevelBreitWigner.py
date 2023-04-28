# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactMultiLevelBreitWigner
from ENDFtk.MF32.MT151 import CompactBreitWignerUncertainties
from ENDFtk.MF32.MT151 import CompactCorrelationMatrix

class Test_ENDFtk_MF32_MT151_CompactMultiLevelBreitWigner( unittest.TestCase ) :
    """Unit test for the CompactMultiLevelBreitWigner class."""

    chunk = ( ' 2.500000+0 7.945990-1          0          2          0          1822832151     \n'
              ' 0.000000+0 7.945990-2          0          0          0          0822832151     \n'
              ' 2.032137+2 0.000000+0          0          0         24          2822832151     \n'
              '-8.684388+3 1.000000+0 7.761335-1 1.005949-1 6.755386-1 0.000000+0822832151     \n'
              ' 8.684390-3 0.000000+0 0.000000+0 1.005950-6 6.755390-2 0.000000+0822832151     \n'
              '-5.815640+3 2.000000+0 3.788054+0 2.995726+0 7.923275-1 0.000000+0822832151     \n'
              ' 5.815640-3 0.000000+0 0.000000+0 2.995730-5 7.923280-2 0.000000+0822832151     \n'
              ' 0.000000+0 0.000000+0          2         87          0          0822832151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 2, chunk.LRF )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )
            self.assertEqual( 2, chunk.LCOMP )
            self.assertEqual( 2, chunk.covariance_representation )

            self.assertAlmostEqual( 2.5, chunk.SPI )
            self.assertAlmostEqual( 2.5, chunk.spin )
            self.assertAlmostEqual( .7945990, chunk.AP )
            self.assertAlmostEqual( .7945990, chunk.scattering_radius )

            self.assertEqual( 7.945990e-2, chunk.DAP )
            self.assertEqual( 7.945990e-2, chunk.scattering_radius_uncertainty )
            self.assertEqual( True, chunk.ISR )
            self.assertEqual( True, chunk.scattering_radius_uncertainty_flag )

            self.assertAlmostEqual( 203.2137, chunk.uncertainties.AWRI )
            self.assertAlmostEqual( 203.2137, chunk.uncertainties.atomic_weight_ratio )
            self.assertAlmostEqual( 0., chunk.uncertainties.QX )
            self.assertAlmostEqual( 0., chunk.uncertainties.competitive_qvalue )
            self.assertEqual( False, chunk.uncertainties.LRX )
            self.assertEqual( False, chunk.uncertainties.competitive_width_flag )

            self.assertEqual( 2, chunk.uncertainties.NRSA )
            self.assertEqual( 2, chunk.uncertainties.number_resonances )
            self.assertEqual( 2, len( chunk.uncertainties.ER ) )
            self.assertEqual( 2, len( chunk.uncertainties.resonance_energies ) )
            self.assertEqual( 2, len( chunk.uncertainties.AJ ) )
            self.assertEqual( 2, len( chunk.uncertainties.spin_values ) )
            self.assertEqual( 2, len( chunk.uncertainties.GT ) )
            self.assertEqual( 2, len( chunk.uncertainties.total_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GN ) )
            self.assertEqual( 2, len( chunk.uncertainties.neutron_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GG ) )
            self.assertEqual( 2, len( chunk.uncertainties.gamma_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.GF ) )
            self.assertEqual( 2, len( chunk.uncertainties.fission_widths ) )
            self.assertEqual( 2, len( chunk.uncertainties.DER ) )
            self.assertEqual( 2, len( chunk.uncertainties.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGN ) )
            self.assertEqual( 2, len( chunk.uncertainties.neutron_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGG ) )
            self.assertEqual( 2, len( chunk.uncertainties.gamma_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.uncertainties.DGF ) )
            self.assertEqual( 2, len( chunk.uncertainties.fission_width_uncertainties ) )

            self.assertAlmostEqual( -8.684388e+3, chunk.uncertainties.ER[0] )
            self.assertAlmostEqual( -5.815640e+3, chunk.uncertainties.ER[1] )
            self.assertAlmostEqual( -8.684388e+3, chunk.uncertainties.resonance_energies[0] )
            self.assertAlmostEqual( -5.815640e+3, chunk.uncertainties.resonance_energies[1] )
            self.assertAlmostEqual( 1., chunk.uncertainties.AJ[0] )
            self.assertAlmostEqual( 2., chunk.uncertainties.AJ[1] )
            self.assertAlmostEqual( 1., chunk.uncertainties.spin_values[0] )
            self.assertAlmostEqual( 2., chunk.uncertainties.spin_values[1] )
            self.assertAlmostEqual( 7.761335e-1, chunk.uncertainties.GT[0] )
            self.assertAlmostEqual( 3.788054e+0, chunk.uncertainties.GT[1] )
            self.assertAlmostEqual( 7.761335e-1, chunk.uncertainties.total_widths[0] )
            self.assertAlmostEqual( 3.788054e+0, chunk.uncertainties.total_widths[1] )
            self.assertAlmostEqual( 1.005949e-1, chunk.uncertainties.GN[0] )
            self.assertAlmostEqual( 2.995726e+0, chunk.uncertainties.GN[1] )
            self.assertAlmostEqual( 1.005949e-1, chunk.uncertainties.neutron_widths[0] )
            self.assertAlmostEqual( 2.995726e+0, chunk.uncertainties.neutron_widths[1] )
            self.assertAlmostEqual( 6.755386e-1, chunk.uncertainties.GG[0] )
            self.assertAlmostEqual( 7.923275e-1, chunk.uncertainties.GG[1] )
            self.assertAlmostEqual( 6.755386e-1, chunk.uncertainties.gamma_widths[0] )
            self.assertAlmostEqual( 7.923275e-1, chunk.uncertainties.gamma_widths[1] )
            self.assertAlmostEqual( 0., chunk.uncertainties.GF[0] )
            self.assertAlmostEqual( 0., chunk.uncertainties.GF[1] )
            self.assertAlmostEqual( 0., chunk.uncertainties.fission_widths[0] )
            self.assertAlmostEqual( 0., chunk.uncertainties.fission_widths[1] )

            self.assertAlmostEqual( 8.684390e-3, chunk.uncertainties.DER[0] )
            self.assertAlmostEqual( 5.815640e-3, chunk.uncertainties.DER[1] )
            self.assertAlmostEqual( 8.684390e-3, chunk.uncertainties.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 5.815640e-3, chunk.uncertainties.resonance_energy_uncertainties[1] )
            self.assertAlmostEqual( 1.005950e-6, chunk.uncertainties.DGN[0] )
            self.assertAlmostEqual( 2.995730e-5, chunk.uncertainties.DGN[1] )
            self.assertAlmostEqual( 1.005950e-6, chunk.uncertainties.neutron_width_uncertainties[0] )
            self.assertAlmostEqual( 2.995730e-5, chunk.uncertainties.neutron_width_uncertainties[1] )
            self.assertAlmostEqual( 6.755390e-2, chunk.uncertainties.DGG[0] )
            self.assertAlmostEqual( 7.923280e-2, chunk.uncertainties.DGG[1] )
            self.assertAlmostEqual( 6.755390e-2, chunk.uncertainties.gamma_width_uncertainties[0] )
            self.assertAlmostEqual( 7.923280e-2, chunk.uncertainties.gamma_width_uncertainties[1] )
            self.assertAlmostEqual( 0., chunk.uncertainties.DGF[0] )
            self.assertAlmostEqual( 0., chunk.uncertainties.DGF[1] )
            self.assertAlmostEqual( 0., chunk.uncertainties.fission_width_uncertainties[0] )
            self.assertAlmostEqual( 0., chunk.uncertainties.fission_width_uncertainties[1] )

            self.assertEqual( 2, chunk.correlation_matrix.NDIGIT )
            self.assertEqual( 2, chunk.correlation_matrix.number_digits )
            self.assertEqual( 87, chunk.correlation_matrix.NNN )
            self.assertEqual( 87, chunk.correlation_matrix.order )
            self.assertEqual( 0, len( chunk.correlation_matrix.I ) )
            self.assertEqual( 0, len( chunk.correlation_matrix.J ) )
            self.assertEqual( 0, len( chunk.correlation_matrix.correlations ) )

            self.assertEqual( 8, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 8228, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactMultiLevelBreitWigner(
                  spi = 2.5, ap = 7.945990e-1, dap = 7.945990e-2,
                  parameters = CompactBreitWignerUncertainties(
                                   203.2137, 0., False,
                                   [ -8.684388e+3, -5.815640e+3 ], [ 1., 2. ],
                                   [ 7.761335e-1, 3.788054e+0 ], [ 1.005949e-1, 2.995726e+0 ],
                                   [ 6.755386e-1, 7.923275e-1 ], [ 0., 0. ],
                                   [ 8.684390e-3, 5.815640e-3 ],
                                   [ 1.005950e-6, 2.995730e-5 ], [ 6.755390e-2, 7.923280e-2 ],
                                   [ 0., 0. ] ),
                  matrix = CompactCorrelationMatrix( 87, [], [], [], 2 ) )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactMultiLevelBreitWigner.from_string( self.chunk, 8228, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactMultiLevelBreitWigner( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
