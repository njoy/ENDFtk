std::string chunkWithCorrectIndex();
std::string chunkWithIncorrectIndex();

SCENARIO( "Update index" ) {

  std::string correct = chunkWithCorrectIndex();

  GIVEN( "a material with a correct index" ) {

    auto position = correct.begin();
    auto start = correct.begin();
    auto end = correct.end();
    long lineNumber = 0;

    HeadRecord head( position, end, lineNumber );
    tree::Material material( head, start, position, end, lineNumber );

    njoy::ENDFtk::tree::updateDirectory( material );

    THEN( "the index is not changed" ) {

      CHECK( correct == material.content() );
    } // GIVEN
  } // GIVEN

  GIVEN( "a material with a incorrect index" ) {

    std::string incorrect = chunkWithIncorrectIndex();
    auto position = incorrect.begin();
    auto start = incorrect.begin();
    auto end = incorrect.end();
    long lineNumber = 0;

    HeadRecord head( position, end, lineNumber );
    tree::Material material( head, start, position, end, lineNumber );

    njoy::ENDFtk::tree::updateDirectory( material );

    THEN( "the index is changed" ) {

      CHECK( correct == material.content() );
    } // GIVEN
  } // GIVEN
} // SCENARIO

std::string chunkWithCorrectIndex() {

  return
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          4 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         16          0 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1          4          0 125 1451     \n"
    "                                3          5          4          0 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n"
    "                                                                   125 2  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  1     \n"
    "          2          2                                             125 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n"
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n"
    "                                                                     0 0  0     \n";
}

std::string chunkWithIncorrectIndex() {

  return
    " 1.001000+3 9.991673-1          0          0          0          3 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n"
    " 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n"
    " 0.000000+0 0.000000+0          0          0          8          5 125 1451     \n"
    "  1-H -  1 LANL       EVAL-OCT05 G.M.Hale                          125 1451     \n"
    "                      DIST-DEC06                       20111222    125 1451     \n"
    "----ENDF/B-VIII.beta  MATERIAL  125                                125 1451     \n"
    "-----INCIDENT NEUTRON DATA                                         125 1451     \n"
    "------ENDF-6 FORMAT                                                125 1451     \n"
    "                                                                   125 1451     \n"
    " ****************************************************************  125 1451     \n"
    " ****************************************************************  125 1451     \n"
    "                                1        451         17          0 125 1451     \n"
    "                                2        151          4          0 125 1451     \n"
    "                                3          1          4          0 125 1451     \n"
    "                                3          5          4          0 125 1451     \n"
    "                                4          5          4          0 125 1451     \n"
    "                                                                   125 1  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          1          0 125 2151     \n"
    " 1.001000+3 1.000000+0          0          0          1          0 125 2151     \n"
    " 1.000000-5 1.000000+5          0          0          0          0 125 2151     \n"
    " 5.000000-1 1.276553+0          0          0          0          0 125 2151     \n"
    "                                                                   125 2  0     \n"
    "                                                                   125 0  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  1     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  1     \n"
    "          2          2                                             125 3  1     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  1     \n"
    "                                                                   125 3  0     \n"
    " 1.001000+3 9.991673-1          0          0          0          0 125 3  5     \n"
    " 1.123400+6 1.123400+6          0          0          1          4 125 3  5     \n"
    "          2          2                                             125 3  5     \n"
    " 1.000000-5 1.000000+0 2.000000+7 2.000000+0                       125 3  5     \n"
    "                                                                   125 3  0     \n"
    "                                                                   125 0  0     \n"
    "                                                                     0 0  0     \n";
}
