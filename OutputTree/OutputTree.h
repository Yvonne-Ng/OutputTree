#include "TTree.h"
#include "TLorentzVector.h"

#include "fastjet/PseudoJet.hh"

#include "xAODJet/JetContainer.h"
#include "xAODTruth/TruthParticle.h"

class OutputTree : public TTree {
public:
  OutputTree(const std::string& name="output");

  void add_scalar(const std::string& name, float val);
  void add_vector(const std::string& name, const std::vector<float>& vec);
  
  void add_photon_type(const std::string& name);

  void add_photon(const std::string& name, const TLorentzVector& ph);

  void add_jet_type(const std::string& name);
  
  void add_jet(const std::string& name, const TLorentzVector& j);
  void add_jet(const std::string& name, const fastjet::PseudoJet& j);
  void add_jets(const std::string& name, const std::vector<TLorentzVector>& jets);
  void add_jets(const std::string& name, const std::vector<fastjet::PseudoJet>& jets);
  void add_jets(const std::string& name, const xAOD::JetContainer* jets);
  void add_jets(const std::string& name, const xAOD::JetContainer& jets);
  void add_jets(const std::string& name, const std::vector<const xAOD::Jet*>& jets);

  void add_truth_type(const std::string& name);
  void add_truth(const std::string& name, const xAOD::TruthParticle* particle);
  void add_truths(const std::string& name, const std::vector<const xAOD::TruthParticle*>& particles);

  void clear();
  
private:
  std::map<std::string, float* > scalar_vars;
  std::map<std::string, std::vector<float> > vector_vars;

  std::map<std::string, std::vector<float> > jet_vars;
  std::set<std::string> jet_names;

  std::map<std::string, std::vector<float> > ph_vars;
  std::set<std::string> ph_names;

  std::map<std::string, std::vector<float> > truth_vars;
  std::set<std::string> truth_names;
};

