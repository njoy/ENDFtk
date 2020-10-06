# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import ParticlePairs

class Test_ENDFtk_MF2_MT151_ParticlePairs( unittest.TestCase ) :
    """Unit test for the ParticlePairs class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          0         24          42625 2151     \n'
              ' 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+02625 2151     \n'
              ' 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+12625 2151     \n'
              ' 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+02625 2151     \n'
              ' 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+12625 2151     \n' )

    invalid_size = ( ' 0.000000+0 0.000000+0          2          0         23          42625 2151     \n'
                     ' 0.000000+0 5.446635+1 0.000000+0 2.600000+1 1.000000+0 0.000000+02625 2151     \n'
                     ' 0.000000+0 0.000000+0 0.000000+0 1.020000+2 0.000000+0 0.000000+02625 2151     \n'
                     ' 1.000000+0 5.347624+1 0.000000+0 2.600000+1 5.000000-1 0.000000+02625 2151     \n'
                     ' 0.000000+0 1.000000+0 0.000000+0 2.000000+0 0.000000+0           2625 2151     \n' )

    zero_size = ( ' 0.000000+0 0.000000+0          2          0          0          42625 2151     \n' )

    zero_npp = ( ' 0.000000+0 0.000000+0          0          0         24          02625 2151     \n'
                 ' 0.000000+0 5.446635+1 2.000000+0 2.600000+1 1.000000+0 4.000000+02625 2151     \n'
                 ' 6.000000+0 8.000000+0 1.000000+1 1.020000+2 1.200000+1 1.400000+12625 2151     \n'
                 ' 1.000000+0 5.347624+1 3.000000+0 2.700000+1 5.000000-1 5.000000+02625 2151     \n'
                 ' 7.000000+0 9.000000+0 1.100000+1 2.000000+0 1.300000+1 1.500000+12625 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NPP )
            self.assertEqual( 2, chunk.number_particle_pairs )
            self.assertEqual( 2, len( chunk.MA ) )
            self.assertEqual( 2, len( chunk.mass_particle_A ) )
            self.assertEqual( 2, len( chunk.MB ) )
            self.assertEqual( 2, len( chunk.mass_particle_B ) )
            self.assertEqual( 2, len( chunk.ZA ) )
            self.assertEqual( 2, len( chunk.charge_particle_A ) )
            self.assertEqual( 2, len( chunk.ZB ) )
            self.assertEqual( 2, len( chunk.charge_particle_B ) )
            self.assertEqual( 2, len( chunk.IA ) )
            self.assertEqual( 2, len( chunk.spin_particle_A ) )
            self.assertEqual( 2, len( chunk.IB ) )
            self.assertEqual( 2, len( chunk.spin_particle_B ) )
            self.assertEqual( 2, len( chunk.PA ) )
            self.assertEqual( 2, len( chunk.parity_particle_A ) )
            self.assertEqual( 2, len( chunk.PB ) )
            self.assertEqual( 2, len( chunk.parity_particle_B ) )
            self.assertEqual( 2, len( chunk.Q ) )
            self.assertEqual( 2, len( chunk.PNT ) )
            self.assertEqual( 2, len( chunk.penetrability_flag ) )
            self.assertEqual( 2, len( chunk.SHF ) )
            self.assertEqual( 2, len( chunk.shift_factor_flag ) )
            self.assertEqual( 2, len( chunk.MT ) )

            self.assertAlmostEqual( 0., chunk.MA[0] )
            self.assertAlmostEqual( 1., chunk.MA[1] )
            self.assertAlmostEqual( 0, chunk.mass_particle_A[0] )
            self.assertAlmostEqual( 1, chunk.mass_particle_A[1] )
            self.assertAlmostEqual( 5.446635e+1, chunk.MB[0] )
            self.assertAlmostEqual( 5.347624e+1, chunk.MB[1] )
            self.assertAlmostEqual( 5.446635e+1, chunk.mass_particle_B[0] )
            self.assertAlmostEqual( 5.347624e+1, chunk.mass_particle_B[1] )
            self.assertAlmostEqual( 2., chunk.ZA[0] )
            self.assertAlmostEqual( 3., chunk.ZA[1] )
            self.assertAlmostEqual( 2., chunk.charge_particle_A[0] )
            self.assertAlmostEqual( 3., chunk.charge_particle_A[1] )
            self.assertAlmostEqual( 26., chunk.ZB[0] )
            self.assertAlmostEqual( 27., chunk.ZB[1] )
            self.assertAlmostEqual( 26., chunk.charge_particle_B[0] )
            self.assertAlmostEqual( 27., chunk.charge_particle_B[1] )
            self.assertAlmostEqual( 1., chunk.IA[0] )
            self.assertAlmostEqual( 0.5, chunk.IA[1] )
            self.assertAlmostEqual( 1., chunk.spin_particle_A[0] )
            self.assertAlmostEqual( 0.5, chunk.spin_particle_A[1] )
            self.assertAlmostEqual( 4., chunk.IB[0] )
            self.assertAlmostEqual( 5., chunk.IB[1] )
            self.assertAlmostEqual( 4., chunk.spin_particle_B[0] )
            self.assertAlmostEqual( 5., chunk.spin_particle_B[1] )
            self.assertAlmostEqual( 12., chunk.PA[0] )
            self.assertAlmostEqual( 13., chunk.PA[1] )
            self.assertAlmostEqual( 12., chunk.parity_particle_A[0] )
            self.assertAlmostEqual( 13., chunk.parity_particle_A[1] )
            self.assertAlmostEqual( 14., chunk.PB[0] )
            self.assertAlmostEqual( 15., chunk.PB[1] )
            self.assertAlmostEqual( 14., chunk.parity_particle_B[0] )
            self.assertAlmostEqual( 15., chunk.parity_particle_B[1] )
            self.assertAlmostEqual( 6., chunk.Q[0] )
            self.assertAlmostEqual( 7., chunk.Q[1] )
            self.assertEqual( 8, chunk.PNT[0] );
            self.assertEqual( 9, chunk.PNT[1] );
            self.assertEqual( 8, chunk.penetrability_flag[0] );
            self.assertEqual( 9, chunk.penetrability_flag[1] );
            self.assertEqual( 10, chunk.SHF[0] );
            self.assertEqual( 11, chunk.SHF[1] );
            self.assertEqual( 10, chunk.shift_factor_flag[0] );
            self.assertEqual( 11, chunk.shift_factor_flag[1] );
            self.assertEqual( 102, chunk.MT[0] );
            self.assertEqual( 2, chunk.MT[1] );

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = ParticlePairs( ma = [ 0., 1. ], mb = [ 5.446635e+1, 5.347624e+1 ],
                               za = [ 2., 3. ],  zb = [ 26., 27. ],
                               ia = [ 1., 0.5 ], ib = [ 4., 5. ],
                               q = [ 6., 7. ], pnt = [ 8, 9 ],
                               shf = [ 10, 11 ], mt = [ 102, 2 ],
                               pa = [ 12., 13. ], pb = [ 14., 15. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ParticlePairs.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = ParticlePairs( ma = [ 1. ], mb = [ 5.446635e+1, 5.347624e+1 ],
                                   za = [ 2., 3. ],  zb = [ 26., 27. ],
                                   ia = [ 1., 0.5 ], ib = [ 4., 5. ],
                                   q = [ 6., 7. ], pnt = [ 8, 9 ],
                                   shf = [ 10, 11 ], mt = [ 102, 2 ],
                                   pa = [ 12., 13. ], pb = [ 14., 15. ]  )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = ParticlePairs( ma = [], mb = [], za = [],  zb = [],
                                   ia = [], ib = [], q = [], pnt = [],
                                   shf = [], mt = [], pa = [], pb = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = ParticlePairs.from_string( self.invalid_size, 2625, 2, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = ParticlePairs.from_string( self.zero_size, 2625, 2, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = ParticlePairs.from_string( self.zero_npp, 2625, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
