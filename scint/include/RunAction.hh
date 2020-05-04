
#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <fstream>

using namespace std;

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

	G4double xmin;
	G4double xmax;
    G4double binsize;
	G4int nbins;
    G4double amin;
    G4double amax;
    G4double abinsize;
    G4int abins;
    G4double emin;
    G4double emax;
    G4int ebins;
};

#endif

