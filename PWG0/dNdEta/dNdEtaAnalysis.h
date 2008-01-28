/* $Id$ */

#ifndef DNDETANALYSIS_H
#define DNDETANALYSIS_H

// ------------------------------------------------------
//
// Class for dn/deta analysis
//
// ------------------------------------------------------
// 
// TODO:
// - more documentation
// - add debug statements
// - add more histograms
// - add functionality to set the bin sizes
// - figure out correct way to treat the errors
// - add functionality to make dn/deta for different mult classes?

#include <TNamed.h>
#include "AlidNdEtaCorrection.h"
#include "AliPWG0Helper.h"

class TH1F;
class TCollection;

class AliCorrection;

class dNdEtaAnalysis : public TNamed
{
public:
  enum { kVertexBinning = 1+2 }; // the first is for the whole vertex range, the others divide the vertex range

  dNdEtaAnalysis();
  dNdEtaAnalysis(Char_t* name, Char_t* title, AliPWG0Helper::AnalysisMode analysisMode = AliPWG0Helper::kTPC);
  virtual ~dNdEtaAnalysis();

  dNdEtaAnalysis(const dNdEtaAnalysis &c);
  dNdEtaAnalysis &operator=(const dNdEtaAnalysis &c);
  virtual void Copy(TObject &c) const;

  void FillTrack(Float_t vtx, Float_t eta, Float_t pt);
  void FillEvent(Float_t vtx, Float_t n);

  void Finish(AlidNdEtaCorrection* correction, Float_t ptCut, AlidNdEtaCorrection::CorrectionType correctionType, Int_t multCut = 0);

  void DrawHistograms(Bool_t simple = kFALSE);
  void LoadHistograms(const Char_t* dir = 0);
  void SaveHistograms();

  virtual Long64_t Merge(TCollection* list);

  AliCorrection* GetData() { return fData; }

  TH1F* GetPtHistogram() { return fPtDist; }

  TH1F* GetdNdEtaHistogram(Int_t i = 0) { return fdNdEta[i]; }
  TH1F* GetdNdEtaPtCutOffCorrectedHistogram(Int_t i = 0) { return fdNdEtaPtCutOffCorrected[i]; }

protected:
  AliCorrection* fData;     // we store the data in an AliCorrection

  TH1F* fPtDist; // pt distribution

  TH1F* fdNdEtaNotEventCorrected[kVertexBinning];  // dndeta results for different vertex bins (0 = full range)
  TH1F* fdNdEta[kVertexBinning];                   // dndeta results for different vertex bins (0 = full range), mult cut off corrected
  TH1F* fdNdEtaPtCutOffCorrected[kVertexBinning];  // dndeta results for different vertex bins (0 = full range), mult + pt cut off corrected 

  ClassDef(dNdEtaAnalysis, 1)
};

#endif
