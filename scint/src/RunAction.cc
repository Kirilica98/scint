///////////////////////////////////////////
//
// Oct/2015  Fabio -> RunAction.cc
//
///////////////////////////////////////////

#include "RunAction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Run.hh"
#include "G4ios.hh"

#include <iomanip>

RunAction::RunAction() : G4UserRunAction()
{
	  // Create analysis manager
	  // The choice of analysis technology is done via selecting of a namespace
	  // in B4Analysis.hh
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	  G4cout << "Using " << analysisManager->GetType() << G4endl;

	  // Create directories
	  //analysisManager->SetHistoDirectoryName("histograms");
	  //analysisManager->SetNtupleDirectoryName("ntuple");
	  analysisManager->SetVerboseLevel(1);
	  analysisManager->SetFirstHistoId(0); // default is 0
	  analysisManager->SetFirstNtupleId(0); // default is 0

	  // Book histograms, ntuple
	  //

	  // Creating histograms

	  //  G4int CreateH1(const G4String& name, const G4String& title,
	  //                 G4int nbins, G4double xmin, G4double xmax,
	  //                 const G4String& unitName = "none",
	  //                 const G4String& fcnName = "none",
	  //                 const G4String& binSchemeName = "linear");

      /*xmin = 0; // in keV
      xmax = 12; // in keV
      //binsize = 0.002; // in keV
      nbins=
      analysisManager->CreateH1("Histo1","Edep in SD", nbins, xmin*eV, xmax*eV);*/

      xmin = 0; // in keV
      xmax = 1000; // in keV
      //binsize = 0.; // in keV
      nbins= 100;
      amax=3.14;
      amin=0.;
      abinsize=0.0314;
      abins=100;
      //analysisManager->CreateH3("Histo1","Coordinates",2*abins,(-1)*amax,amax,abins,amin,amax,nbins,xmin*m,xmax*m);
      analysisManager->CreateH3("Histo1","Coordinates", 2*nbins,(-1)*xmax,xmax,2*nbins,(-1)*xmax,xmax,nbins,(-1)*xmax,xmax);
      analysisManager->CreateH2("Histo2","PHITHETA",2*abins,(-1)*amax,amax,abins,amin,amax);
      analysisManager->CreateH2("Histo3","CoordinatesTHETAPHI", abins,amin,amax,2*abins,(-1)*amax,amax);


      /*emin=0.;
      emax=5;
      ebins=500;
      analysisManager->CreateH1("Histo7","Edep in SD", ebins, emin*eV, emax*eV);*/

	  // Creating ntuple
	  //
      analysisManager->CreateNtuple("B3", "coordinates");
      //analysisManager->CreateNtupleDColumn("Energy");

      //analysisManager->CreateNtupleDColumn("R");
      analysisManager->CreateNtupleDColumn("Phi");
      analysisManager->CreateNtupleDColumn("Theta");
      analysisManager->CreateNtupleDColumn("X");
      analysisManager->CreateNtupleDColumn("Y");
      analysisManager->CreateNtupleDColumn("Z");


	  analysisManager->FinishNtuple();

}

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run*)
{
	  //inform the runManager to save random number seed
	  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

	  // Get analysis manager
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	  // Open an output file
	  //
      G4String fileName = "/home/kirilica/data/test_kolba_data.root";
	  analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run*)
{
	  // print histogram statistics
	  //
	  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
      if ( analysisManager->GetH3(1) ) {
	    G4cout << G4endl << " ----> print histograms statistic ";
	    if(isMaster) {
	      G4cout << "for the entire run " << G4endl << G4endl;
	    }
	    else {
	      G4cout << "for the local thread " << G4endl << G4endl;
	    }

	    G4cout << G4endl << " EAbs : mean = "
	       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
	       << " rms = "
	       << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Energy") << G4endl;

	  }

	  // save histograms & ntuple
	  //
	  analysisManager->Write();
	  analysisManager->CloseFile();

}


