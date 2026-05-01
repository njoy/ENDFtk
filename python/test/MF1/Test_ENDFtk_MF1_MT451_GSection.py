import unittest

# local imports
from ENDFtk.MF1.MT451 import GSection

class Test_ENDFtk_MF1_MT451_GSection( unittest.TestCase ) :
    """
    Unit test for the Gsection class.
    """

    chunk = ( " 9.223500+4 2.330248+2          0          3         -1          09228 1451     \n"
              " 2.936000+2 0.000000+0         30         12         47          09228 1451     \n"
              " 1.00000+10 1.000000+4 1.000000+2 1.390000-4 1.520000-1 4.140000-19228 1451     \n"
              " 1.130000+0 3.060000+0 8.320000+0 2.260000+1 6.140000+1 1.670000+29228 1451     \n"
              " 4.540000+2 1.235000+3 3.350000+3 9.120000+3 2.480000+4 6.760000+49228 1451     \n"
              " 1.840000+5 3.030000+5 5.000000+5 8.230000+5 1.353000+6 1.738000+69228 1451     \n"
              " 2.232000+6 2.865000+6 3.680000+6 6.070000+6 7.790000+6 1.000000+79228 1451     \n"
              " 1.200000+7 1.350000+7 1.500000+7 1.700000+7 1.000000+4 1.000000+59228 1451     \n"
              " 5.000000+5 1.000000+6 2.000000+6 3.000000+6 4.000000+6 5.000000+69228 1451     \n"
              " 6.000000+6 7.000000+6 8.000000+6 9.000000+6 2.000000+7           9228 1451     \n" )

    validFEND = ( "                                                                  9228 0  0     \n" )

    def test_section( self ):

        def verify_chunk( self, chunk ) :
            self.assertEqual( 451, chunk.MT )
            self.assertEqual( 451, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( -1, chunk.NGT )
            self.assertEqual( -1, chunk.type )
            self.assertEqual( 0, chunk.NWT )
            self.assertEqual( 0, chunk.number_title_words )
            self.assertEqual( 3, chunk.NZ )
            self.assertEqual( 3, chunk.number_dilutions )
            self.assertAlmostEqual( 293.6, chunk.TEMP )
            self.assertAlmostEqual( 293.6, chunk.temperature )
            self.assertEqual( 30, chunk.NGN )
            self.assertEqual( 30, chunk.number_neutron_groups )
            self.assertEqual( 12, chunk.NGG )
            self.assertEqual( 12, chunk.number_photon_groups )
            dilutions = [1e10, 1e4, 1e2]
            egn = [1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000,
             3.060000, 8.320000, 2.260000e1, 6.140000e1, 1.670000e2, 4.540000e2,
             1.235000e3, 3.350000e3, 9.120000e3, 2.480000e4, 6.760000e4, 1.840000e5,
             3.030000e5, 5.000000e5, 8.230000e5, 1.353000e6, 1.738000e6, 2.232000e6,
             2.865000e6, 3.680000e6, 6.070000e6, 7.790000e6, 1.000000e7, 1.200000e7,
             1.350000e7, 1.500000e7, 1.700000e7]
            egg = [1.000000e4, 1.000000e5, 5.000000e5, 1.000000e6, 2.000000e6, 3.000000e6,
             4.000000e6, 5.000000e6, 6.000000e6, 7.000000e6, 8.000000e6, 9.000000e6,
             2.000000e7]
            for z in range( chunk.NZ ) :
                self.assertAlmostEqual( dilutions[z], chunk.SIGZ[z] )
                self.assertAlmostEqual( dilutions[z], chunk.dilutions[z] )
            for g in range( chunk.NGN ) :
                self.assertAlmostEqual( egn[g], chunk.neutron_structure[g] )
                self.assertAlmostEqual( egn[g], chunk.EGN[g] )
            for g in range( chunk.NGG ):
                self.assertAlmostEqual( egg[g], chunk.photon_structure[g] )
                self.assertAlmostEqual( egg[g], chunk.EGG[g] )

            # verify string
            self.assertEqual( self.chunk + self.validFEND,
                              chunk.to_string(9228, 1))

        # TEST

        # the data is given explicitly
        chunk = GSection( zaid = 92235, awr = 233.0248, temp = 293.6,
                          sigz = [1e10, 1e4, 1e2],
                          egn = [1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000,
                                 3.060000, 8.320000, 2.260000e1, 6.140000e1, 1.670000e2, 4.540000e2,
                                 1.235000e3, 3.350000e3, 9.120000e3, 2.480000e4, 6.760000e4, 1.840000e5,
                                 3.030000e5, 5.000000e5, 8.230000e5, 1.353000e6, 1.738000e6, 2.232000e6,
                                 2.865000e6, 3.680000e6, 6.070000e6, 7.790000e6, 1.000000e7, 1.200000e7,
                                 1.350000e7, 1.500000e7, 1.700000e7],
                          egg = [1.000000e4, 1.000000e5, 5.000000e5, 1.000000e6, 2.000000e6,
                                 3.000000e6, 4.000000e6, 5.000000e6, 6.000000e6, 7.000000e6,
                                 8.000000e6, 9.000000e6, 2.000000e7] )
        # then it can be verified
        verify_chunk( self, chunk )

        # the data is read in from string
        chunk = GSection.from_string( self.chunk + self.validFEND )

        # then it can be verified
        verify_chunk( self, chunk )

if __name__ == "__main__" :

    unittest.main()