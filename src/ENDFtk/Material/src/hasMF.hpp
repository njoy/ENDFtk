bool
hasMF( int fileNo ) const {
  switch( fileNo ){
  case 1: return true;
  case 2: return true;
  case 3: return true;
  case 4: return this->fileMap[ 4_c ];
  case 5: return this->fileMap[ 5_c ];
  case 6: return this->fileMap[ 6_c ];
  case 7: return this->fileMap[ 7_c ];
  case 8: return this->fileMap[ 8_c ];
  case 9: return this->fileMap[ 9_c ];
  case 10: return this->fileMap[ 10_c ];
  case 12: return this->fileMap[ 12_c ];
  case 13: return this->fileMap[ 13_c ];
  case 14: return this->fileMap[ 14_c ];
  case 15: return this->fileMap[ 15_c ];
  case 23: return this->fileMap[ 23_c ];
  case 26: return this->fileMap[ 26_c ];
  case 27: return this->fileMap[ 27_c ];
  case 28: return this->fileMap[ 28_c ];
  case 30: return this->fileMap[ 30_c ];
  case 31: return this->fileMap[ 31_c ];
  case 32: return this->fileMap[ 32_c ];
  case 33: return this->fileMap[ 33_c ];
  case 34: return this->fileMap[ 34_c ];
  case 35: return this->fileMap[ 35_c ];
  case 40: return this->fileMap[ 40_c ];
  default: return false;
  }
}
