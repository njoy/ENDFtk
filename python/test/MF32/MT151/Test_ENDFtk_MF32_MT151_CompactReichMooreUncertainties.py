# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactReichMooreUncertainties

class Test_ENDFtk_MF32_MT151_CompactReichMooreUncertainties( unittest.TestCase ) :
    """Unit test for the CompactReichMooreUncertainties class."""

    chunk = ( ' 1.982069+1 1.500000+1          0          0         24          2102532151     \n'
              '-1.470000+5 5.000000-1 3.680695+2 1.750000+2 3.000000+0 5.000000+0102532151     \n'
              ' 7.000000+0 0.000000+0 9.000000+0 1.100000+1 1.300000+1 1.500000+1102532151     \n'
              ' 4.730000+5 5.000000-1 1.072900+5 5.600000-1 4.000000+0 6.000000+0102532151     \n'
              ' 8.000000+0 0.000000+0 1.000000+1 1.200000+1 1.400000+1 1.600000+1102532151     \n' )

    invalid_size = ( ' 1.982069+1 1.500000+1          0          0         23          2102532151     \n'
                     '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                     ' 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n'
                     ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                     ' 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1           102532151     \n' )

    zero_size = ( ' 1.982069+1 1.500000+1          0          0          0          2102532151     \n' )

    no_number_resonances = ( ' 1.982069+1 1.500000+1          0          0         24          0102532151     \n'
                             '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                             ' 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n'
                             ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                             ' 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1.982069e+1, chunk.AWRI )
            self.assertAlmostEqual( 1.982069e+1, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 15., chunk.APL )
            self.assertAlmostEqual( 15., chunk.l_dependent_scattering_radius )

            self.assertEqual( 2, chunk.NRSA )
            self.assertEqual( 2, chunk.number_resonances )
            self.assertEqual( 2, len( chunk.ER ) )
            self.assertEqual( 2, len( chunk.resonance_energies ) )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.GN ) )
            self.assertEqual( 2, len( chunk.neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.gamma_widths ) )
            self.assertEqual( 2, len( chunk.GFA ) )
            self.assertEqual( 2, len( chunk.first_fission_widths ) )
            self.assertEqual( 2, len( chunk.GFB ) )
            self.assertEqual( 2, len( chunk.second_fission_widths ) )
            self.assertEqual( 2, len( chunk.DER ) )
            self.assertEqual( 2, len( chunk.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGN ) )
            self.assertEqual( 2, len( chunk.neutron_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGG ) )
            self.assertEqual( 2, len( chunk.gamma_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGFA ) )
            self.assertEqual( 2, len( chunk.first_fission_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGFB ) )
            self.assertEqual( 2, len( chunk.second_fission_width_uncertainties ) )

            self.assertAlmostEqual( -1.470000e+5, chunk.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, chunk.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 0.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.GN[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.GN[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.neutron_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.neutron_widths[1] )
            self.assertAlmostEqual( 175., chunk.GG[0] )
            self.assertAlmostEqual( .56, chunk.GG[1] )
            self.assertAlmostEqual( 175., chunk.gamma_widths[0] )
            self.assertAlmostEqual( .56, chunk.gamma_widths[1] )
            self.assertAlmostEqual( 3., chunk.GFA[0] )
            self.assertAlmostEqual( 4., chunk.GFA[1] )
            self.assertAlmostEqual( 3., chunk.first_fission_widths[0] )
            self.assertAlmostEqual( 4., chunk.first_fission_widths[1] )
            self.assertAlmostEqual( 5., chunk.GFB[0] )
            self.assertAlmostEqual( 6., chunk.GFB[1] )
            self.assertAlmostEqual( 5., chunk.second_fission_widths[0] )
            self.assertAlmostEqual( 6., chunk.second_fission_widths[1] )

            self.assertAlmostEqual( 7., chunk.DER[0] )
            self.assertAlmostEqual( 8., chunk.DER[1] )
            self.assertAlmostEqual( 7., chunk.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 8., chunk.resonance_energy_uncertainties[1] )
            self.assertAlmostEqual( 9., chunk.DGN[0] )
            self.assertAlmostEqual( 10., chunk.DGN[1] )
            self.assertAlmostEqual( 9., chunk.neutron_width_uncertainties[0] )
            self.assertAlmostEqual( 10., chunk.neutron_width_uncertainties[1] )
            self.assertAlmostEqual( 11., chunk.DGG[0] )
            self.assertAlmostEqual( 12., chunk.DGG[1] )
            self.assertAlmostEqual( 11., chunk.gamma_width_uncertainties[0] )
            self.assertAlmostEqual( 12., chunk.gamma_width_uncertainties[1] )
            self.assertAlmostEqual( 13., chunk.DGFA[0] )
            self.assertAlmostEqual( 14., chunk.DGFA[1] )
            self.assertAlmostEqual( 13., chunk.first_fission_width_uncertainties[0] )
            self.assertAlmostEqual( 14., chunk.first_fission_width_uncertainties[1] )
            self.assertAlmostEqual( 15., chunk.DGFB[0] )
            self.assertAlmostEqual( 16., chunk.DGFB[1] )
            self.assertAlmostEqual( 15., chunk.second_fission_width_uncertainties[0] )
            self.assertAlmostEqual( 16., chunk.second_fission_width_uncertainties[1] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactReichMooreUncertainties(
                    awri = 1.982069e+1, apl = 15.,
                    energies = [ -1.470000e+5, 4.730000e+5 ],
                    spins = [ 0.5, 0.5 ],
                    gn = [ 3.680695e+2, 1.072900e+5 ],
                    gg = [ 1.750000e+2, 5.600000e-1 ],
                    gfa = [ 3., 4. ],
                    gfb = [ 5., 6. ],
                    der = [ 7., 8. ],
                    dgn = [ 9., 10. ],
                    dgg = [ 11., 12. ],
                    dgfa = [ 13., 14. ],
                    dgfb = [ 15., 16. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactReichMooreUncertainties.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactReichMooreUncertainties( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = CompactReichMooreUncertainties(
                        awri = 1.982069e+1, apl = 15.,
                        energies = [ -1.470000e+5 ],
                        spins = [ 0.5, 0.5 ],
                        gn = [ 3.680695e+2, 1.072900e+5 ],
                        gg = [ 1.750000e+2, 5.600000e-1 ],
                        gfa = [ 3., 4. ],
                        gfb = [ 5., 6. ],
                        der = [ 7., 8. ],
                        dgn = [ 9., 10. ],
                        dgg = [ 11., 12. ],
                        dgfa = [ 13., 14. ],
                        dgfb = [ 15., 16. ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = CompactReichMooreUncertainties(
                        awri = 1.982069e+1, apl = 15.,
                        energies = [],
                        spins = [],
                        gn = [],
                        gg = [],
                        gfa = [],
                        gfb = [],
                        der = [],
                        dgn = [],
                        dgg = [],
                        dgfa = [],
                        dgfb = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = CompactReichMooreUncertainties.from_string( self.invalid_size,
                                                                 1025, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = CompactReichMooreUncertainties.from_string( self.zero_size,
                                                                 1025, 32, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = CompactReichMooreUncertainties.from_string( self.no_number_resonances,
                                                                 1025, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
