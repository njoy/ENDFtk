# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactBreitWignerUncertainties

class Test_ENDFtk_MF32_MT151_CompactBreitWignerUncertainties( unittest.TestCase ) :
    """Unit test for the CompactBreitWignerUncertainties class."""

    chunk = ( ' 1.982069+1 1.500000+1          0          1         24          2102532151     \n'
              '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
              ' 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n'
              ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
              ' 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n' )

    invalid_size = ( ' 1.982069+1 1.500000+1          0          1         23          2102532151     \n'
                     '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                     ' 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n'
                     ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                     ' 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1           102532151     \n' )

    zero_size = ( ' 1.982069+1 0.000000+0          0          0          0          21025 2151     \n' )

    no_number_resonances = ( ' 1.982069+1 1.500000+1          0          1         24          0102532151     \n'
                             '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+0102532151     \n'
                             ' 5.000000+0 0.000000+0 0.000000+0 7.000000+0 9.000000+0 1.100000+1102532151     \n'
                             ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+0102532151     \n'
                             ' 6.000000+0 0.000000+0 0.000000+0 8.000000+0 1.000000+1 1.200000+1102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1.982069e+1, chunk.AWRI )
            self.assertAlmostEqual( 1.982069e+1, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 15., chunk.QX )
            self.assertAlmostEqual( 15., chunk.competitive_qvalue )
            self.assertEqual( True, chunk.LRX )
            self.assertEqual( True, chunk.competitive_width_flag )

            self.assertEqual( 2, chunk.NRSA )
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
            self.assertEqual( 2, len( chunk.DER ) )
            self.assertEqual( 2, len( chunk.resonance_energy_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGN ) )
            self.assertEqual( 2, len( chunk.neutron_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGG ) )
            self.assertEqual( 2, len( chunk.gamma_width_uncertainties ) )
            self.assertEqual( 2, len( chunk.DGF ) )
            self.assertEqual( 2, len( chunk.fission_width_uncertainties ) )

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

            self.assertAlmostEqual( 5., chunk.DER[0] )
            self.assertAlmostEqual( 6., chunk.DER[1] )
            self.assertAlmostEqual( 5., chunk.resonance_energy_uncertainties[0] )
            self.assertAlmostEqual( 6., chunk.resonance_energy_uncertainties[1] )
            self.assertAlmostEqual( 7., chunk.DGN[0] )
            self.assertAlmostEqual( 8., chunk.DGN[1] )
            self.assertAlmostEqual( 7., chunk.neutron_width_uncertainties[0] )
            self.assertAlmostEqual( 8., chunk.neutron_width_uncertainties[1] )
            self.assertAlmostEqual( 9., chunk.DGG[0] )
            self.assertAlmostEqual( 10., chunk.DGG[1] )
            self.assertAlmostEqual( 9., chunk.gamma_width_uncertainties[0] )
            self.assertAlmostEqual( 10., chunk.gamma_width_uncertainties[1] )
            self.assertAlmostEqual( 11., chunk.DGF[0] )
            self.assertAlmostEqual( 12., chunk.DGF[1] )
            self.assertAlmostEqual( 11., chunk.fission_width_uncertainties[0] )
            self.assertAlmostEqual( 12., chunk.fission_width_uncertainties[1] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactBreitWignerUncertainties(
                    awri = 1.982069e+1, qx = 15., lrx = True,
                    energies = [ -1.470000e+5, 4.730000e+5 ],
                    spins = [ 0.5, 0.5 ],
                    gt = [ 5.470695e+2, 1.072946e+5 ],
                    gn = [ 3.680695e+2, 1.072900e+5 ],
                    gg = [ 1.750000e+2, 5.600000e-1 ],
                    gf = [ 3., 4. ],
                    der = [ 5., 6. ],
                    dgn = [ 7., 8. ],
                    dgg = [ 9., 10. ],
                    dgf = [ 11., 12. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactBreitWignerUncertainties.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactBreitWignerUncertainties( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = CompactBreitWignerUncertainties(
                        awri = 1.982069e+1, qx = 15., lrx = True,
                        energies = [ -1.470000e+5 ],
                        spins = [ 0.5, 0.5 ],
                        gt = [ 5.470695e+2, 1.072946e+5 ],
                        gn = [ 3.680695e+2, 1.072900e+5 ],
                        gg = [ 1.750000e+2, 5.600000e-1 ],
                        gf = [ 3., 4.],
                        der = [ 5., 6. ],
                        dgn = [ 7., 8. ],
                        dgg = [ 9., 10. ],
                        dgf = [ 11., 12. ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = CompactBreitWignerUncertainties(
                        awri = 1.982069e+1, qx = 15., lrx = True,
                        energies = [], spins = [], gt = [],
                        gn = [], gg = [], gf = [],
                        der = [], dgn = [], dgg = [],
                        dgf = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = CompactBreitWignerUncertainties.from_string( self.invalid_size,
                                                                 1025, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = CompactBreitWignerUncertainties.from_string( self.zero_size,
                                                                 1025, 32, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = CompactBreitWignerUncertainties.from_string( self.no_number_resonances,
                                                                 1025, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
