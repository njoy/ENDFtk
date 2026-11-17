import unittest

# local imports
from ENDFtk.MF5.MT18 import GSection

class Test_ENDFtk_MF5_MT18_GSection( unittest.TestCase ) :
    """
    Unit test for the GSection class of MF5 MT18
    """
  
    chunkPrompt = ( " 9.223500+4 0.000000+0          1          1          0         209228 5 18     \n"    
   " 2.936000+2 0.000000+0         20          1         20         209228 5 18     \n"    
   " 1.96730-14 1.15287-11 7.10093-11 7.358034-9 9.678216-7 9.976067-59228 5 18     \n"    
   " 8.080721-4 4.412081-3 3.119482-3 2.172044-2 4.250824-2 1.727228-19228 5 18     \n"    
   " 6.932789-2 1.778175-1 2.204227-1 2.772107-1 8.677879-3 1.124378-39228 5 18     \n"    
   " 1.884936-5 8.232639-6                                            9228 5 18     \n" )
    
    validSEND = ( "                                                                  9228 5  0     \n" )

    def test_section( self ) :
        
        def verify_chunk_prompt( self, chunk ) :
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertEqual( 0, chunk.LR )
            self.assertEqual( 0, chunk.break_up )
            self.assertEqual( 1, chunk.NZ )
            self.assertEqual( 1, chunk.number_dilutions )
            self.assertEqual( 20, chunk.NGN )
            self.assertEqual( 20, chunk.number_neutron_groups )
            self.assertAlmostEqual( 293.6, chunk.TEMP )
            self.assertAlmostEqual( 293.6, chunk.temperature )
            self.assertAlmostEqual( 0.0, chunk.AWR )
            self.assertAlmostEqual( 0.0, chunk.atomic_weight_ratio )
            expected_chi = [ 1.96730e-14, 1.15287e-11, 7.10093e-11, 7.358034e-9, 9.678216e-7, 9.976067e-5, 
                  8.080721e-4, 4.412081e-3, 3.119482e-3, 2.172044e-2, 4.250824e-2, 1.727228e-1,
                  6.932789e-2, 1.778175e-1, 2.204227e-1, 2.772107e-1, 8.677879e-3, 1.124378e-3,
                  1.884936e-5, 8.232639e-6 ]
            for g in range( chunk.NGN ):
                self.assertAlmostEqual( expected_chi[g], chunk.chi[g] )

            # verify string
            self.assertEqual( self.chunkPrompt + self.validSEND, chunk.to_string( 9228, 5 ) )
        
        # TESTS

        # When the data is provided explicitly for prompt fission neutron spectra
        chi = [ 1.96730e-14, 1.15287e-11, 7.10093e-11, 7.358034e-9, 9.678216e-7, 9.976067e-5, 
                  8.080721e-4, 4.412081e-3, 3.119482e-3, 2.172044e-2, 4.250824e-2, 1.727228e-1,
                  6.932789e-2, 1.778175e-1, 2.204227e-1, 2.772107e-1, 8.677879e-3, 1.124378e-3,
                  1.884936e-5, 8.232639e-6 ]
        
        chunk_prompt = GSection( zaid = 92235, awr = 0.0, lr = 0, temp = 293.6, chi = chi )

        # then it can be be verified
        verify_chunk_prompt( self, chunk_prompt )

        # When the data is read in from a string
        chunk_prompt = GSection.from_string( self.chunkPrompt + self.validSEND )

        # then it can be verified
        verify_chunk_prompt( self, chunk_prompt )

