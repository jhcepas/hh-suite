/*
 * hhalign_app.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: meiermark
 */


#include "hhalign.h"

int main(int argc, char **argv) {
  Parameters par;
  HHalign::ProcessAllArguments(argc, argv, par);

  //is empty and will stay empty in this application
  std::vector<HHblitsDatabase*> databases;

  omp_set_num_threads(par.threads);
  HHalign hhalign(par, databases);

  FILE* inf;
  if(strcmp(par.infile, "stdin") == 0) {
      inf = stdin;
  }
  else {
      inf = fopen(par.infile, "r");
  }

  if(!inf) {
      std::cerr << "Input file (" << par.infile << ") could not be opened!" << std::endl;
      exit(1);
  }

  hhalign.run(inf, par.infile, par.tfile);
  fclose(inf);

  hhalign.writeHHRFile(par.outfile);
  hhalign.writeScoresFile(par.scorefile);
  hhalign.writePairwiseAlisFile(par.pairwisealisfile, par.outformat);
  hhalign.writeAlitabFile(par.alitabfile);
  hhalign.writePsiFile(par.psifile);
  hhalign.writeHMMFile(par.hhmfile);
  hhalign.writeA3MFile(par.alnfile);
  hhalign.writeOptimizedHHRFile(par.opt_outfile);
}



