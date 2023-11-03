# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import BreitWignerLValue

class Test_ENDFtk_MF32_MT151_BreitWignerLValue( unittest.TestCase ) :
    """Unit test for the BreitWignerLValue class."""

    chunk = ( ' 1.982069+1 0.000000+0          1          0         36          2102532151     \n'
              '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
              ' 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n'
              ' 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n'
              ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
              ' 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n'
              ' 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1 0.000000+0102532151     \n' )

    invalid_size = ( ' 1.982069+1 0.000000+0          1          0         35          2102532151     \n'
                     '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                     ' 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n'
                     ' 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n'
                     ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                     ' 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n'
                     ' 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1           102532151     \n' )

    zero_size = ( ' 1.982069+1 0.000000+0          0          0          0          21025 2151     \n' )

    no_number_resonances = ( ' 1.982069+1 1.000000+0          1          1         36          01025 2151     \n'
                             '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                             ' 5.000000+0 7.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n'
                             ' 1.700000+1 1.900000+1 2.100000+1 2.300000+1 2.500000+1 0.000000+0102532151     \n'
                             ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                             ' 6.000000+0 8.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n'
                             ' 1.800000+1 2.000000+1 2.200000+1 2.400000+1 2.600000+1 0.000000+0102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1.982069e+1, chunk.AWRI )
            self.assertAlmostEqual( 1.982069e+1, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 2, chunk.NRS )
            self.assertEqual( 2, chunk.number_resonances )
            self.assertEqual( 2, len( chunk.ER ) )
            self.assertEqual( 2, len( chunk.resonance_energies ) )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.GT ) )
            self.assertEqual( 2, len( chunk.total_widths ) )
            self.assertEqual( 2, len( chunk.GN ) )
            self.assertEqual( 2, len( chunk.neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.gamma_widths ) )
            self.assertEqual( 2, len( chunk.GF ) )
            self.assertEqual( 2, len( chunk.fission_widths ) )
            self.assertEqual( 2, len( chunk.DE2 ) )
            self.assertEqual( 2, len( chunk.resonance_energy_variances ) )
            self.assertEqual( 2, len( chunk.DJ2 ) )
            self.assertEqual( 2, len( chunk.spin_variances ) )
            self.assertEqual( 2, len( chunk.DN2 ) )
            self.assertEqual( 2, len( chunk.neutron_width_variances ) )
            self.assertEqual( 2, len( chunk.DG2 ) )
            self.assertEqual( 2, len( chunk.gamma_width_variances ) )
            self.assertEqual( 2, len( chunk.DF2 ) )
            self.assertEqual( 2, len( chunk.fission_width_variances ) )
            self.assertEqual( 2, len( chunk.DJDN ) )
            self.assertEqual( 2, len( chunk.spin_and_neutron_width_covariances ) )
            self.assertEqual( 2, len( chunk.DJDG ) )
            self.assertEqual( 2, len( chunk.spin_and_gamma_width_covariances ) )
            self.assertEqual( 2, len( chunk.DJDF ) )
            self.assertEqual( 2, len( chunk.spin_and_fission_width_covariances ) )
            self.assertEqual( 2, len( chunk.DNDG ) )
            self.assertEqual( 2, len( chunk.neutron_and_gamma_width_covariances ) )
            self.assertEqual( 2, len( chunk.DNDF ) )
            self.assertEqual( 2, len( chunk.neutron_and_fission_width_covariances ) )
            self.assertEqual( 2, len( chunk.DGDF ) )
            self.assertEqual( 2, len( chunk.gamma_and_fission_width_covariances ) )

            self.assertAlmostEqual( -1.470000e+5, chunk.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, chunk.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 0.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.GT[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.GT[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.total_widths[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.total_widths[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.GN[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.GN[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.neutron_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.neutron_widths[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.GG[0] )
            self.assertAlmostEqual( 0.56, chunk.GG[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.gamma_widths[0] )
            self.assertAlmostEqual( 0.56, chunk.gamma_widths[1] )
            self.assertAlmostEqual( 3., chunk.GF[0] )
            self.assertAlmostEqual( 4., chunk.GF[1] )
            self.assertAlmostEqual( 3., chunk.fission_widths[0] )
            self.assertAlmostEqual( 4., chunk.fission_widths[1] )

            self.assertAlmostEqual( 5., chunk.DE2[0] )
            self.assertAlmostEqual( 6., chunk.DE2[1] )
            self.assertAlmostEqual( 5., chunk.resonance_energy_variances[0] )
            self.assertAlmostEqual( 6., chunk.resonance_energy_variances[1] )
            self.assertAlmostEqual( 25., chunk.DJ2[0] )
            self.assertAlmostEqual( 26., chunk.DJ2[1] )
            self.assertAlmostEqual( 25., chunk.spin_variances[0] )
            self.assertAlmostEqual( 26., chunk.spin_variances[1] )
            self.assertAlmostEqual( 7., chunk.DN2[0] )
            self.assertAlmostEqual( 8., chunk.DN2[1] )
            self.assertAlmostEqual( 7., chunk.neutron_width_variances[0] )
            self.assertAlmostEqual( 8., chunk.neutron_width_variances[1] )
            self.assertAlmostEqual( 11., chunk.DG2[0] )
            self.assertAlmostEqual( 12., chunk.DG2[1] )
            self.assertAlmostEqual( 11., chunk.gamma_width_variances[0] )
            self.assertAlmostEqual( 12., chunk.gamma_width_variances[1] )
            self.assertAlmostEqual( 17., chunk.DF2[0] )
            self.assertAlmostEqual( 18., chunk.DF2[1] )
            self.assertAlmostEqual( 17., chunk.fission_width_variances[0] )
            self.assertAlmostEqual( 18., chunk.fission_width_variances[1] )
            self.assertAlmostEqual( 19., chunk.DJDN[0] )
            self.assertAlmostEqual( 20., chunk.DJDN[1] )
            self.assertAlmostEqual( 19., chunk.spin_and_neutron_width_covariances[0] )
            self.assertAlmostEqual( 20., chunk.spin_and_neutron_width_covariances[1] )
            self.assertAlmostEqual( 21., chunk.DJDG[0] )
            self.assertAlmostEqual( 22., chunk.DJDG[1] )
            self.assertAlmostEqual( 21., chunk.spin_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 22., chunk.spin_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 23., chunk.DJDF[0] )
            self.assertAlmostEqual( 24., chunk.DJDF[1] )
            self.assertAlmostEqual( 23., chunk.spin_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 24., chunk.spin_and_fission_width_covariances[1] )
            self.assertAlmostEqual(  9., chunk.DNDG[0] )
            self.assertAlmostEqual( 10., chunk.DNDG[1] )
            self.assertAlmostEqual(  9., chunk.neutron_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 10., chunk.neutron_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 13., chunk.DNDF[0] )
            self.assertAlmostEqual( 14., chunk.DNDF[1] )
            self.assertAlmostEqual( 13., chunk.neutron_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 14., chunk.neutron_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 15., chunk.DGDF[0] )
            self.assertAlmostEqual( 16., chunk.DGDF[1] )
            self.assertAlmostEqual( 15., chunk.gamma_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 16., chunk.gamma_and_fission_width_covariances[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = BreitWignerLValue( awri = 1.982069e+1, l = 1,
                                   energies = [ -1.470000e+5, 4.730000e+5 ],
                                   spins = [ 0.5, 0.5 ],
                                   gt = [ 5.470695e+2, 1.072946e+5 ],
                                   gn = [ 3.680695e+2, 1.072900e+5 ],
                                   gg = [ 1.750000e+2, 5.600000e-1 ],
                                   gf = [ 3., 4. ],
                                   de2 = [ 5., 6. ],
                                   dn2 = [ 7., 8. ],
                                   dndg = [ 9., 10. ],
                                   dg2 = [ 11., 12. ],
                                   dndf = [ 13., 14. ],
                                   dgdf = [ 15., 16. ],
                                   df2 = [ 17., 18. ],
                                   djdn = [ 19., 20. ],
                                   djdg = [ 21., 22. ],
                                   djdf = [ 23., 24. ],
                                   dj2 = [ 25., 26. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = BreitWignerLValue.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = BreitWignerLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = BreitWignerLValue( awri = 1.982069e+1, qx = 1.,
                                       l = 1, lrx = True,
                                       energies = [ -1.470000e+5 ],
                                       spins = [ 0.5, 0.5 ],
                                       gt = [ 5.470695e+2, 1.072946e+5 ],
                                       gn = [ 3.680695e+2, 1.072900e+5 ],
                                       gg = [ 1.750000e+2, 5.600000e-1 ],
                                       gf = [ 3., 4.],
                                       de2 = [ 5., 6. ],
                                       dn2 = [ 7., 8. ],
                                       dndg = [ 9., 10. ],
                                       dg2 = [ 11., 12. ],
                                       dndf = [ 13., 14. ],
                                       dgdf = [ 15., 16. ],
                                       df2 = [ 17., 18. ],
                                       djdn = [ 19., 20. ],
                                       djdg = [ 21., 22. ],
                                       djdf = [ 23., 24. ],
                                       dj2 = [ 25., 26. ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = BreitWignerLValue( awri = 1.982069e+1, qx = 1.,
                                       l = 1, lrx = True,
                                       energies = [], spins = [], gt = [],
                                       gn = [], gg = [], gf = [],
                                       de2 = [], dn2 = [], dndg = [],
                                       dg2 = [], dndf = [], dgdf = [],
                                       df2 = [], djdn = [], djdg = [],
                                       djdf = [], dj2 = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = BreitWignerLValue.from_string( self.invalid_size,
                                                   1025, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = BreitWignerLValue.from_string( self.zero_size,
                                                   1025, 32, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = BreitWignerLValue.from_string( self.no_number_resonances,
                                                   1025, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
