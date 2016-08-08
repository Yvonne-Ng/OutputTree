#include "OutputTree/OutputTree.h"

#include "TBranch.h"

OutputTree::OutputTree(const std::string& name) :
  TTree(name.c_str(), name.c_str())
{
}

void OutputTree::add_vector(const std::string& name, const std::vector<float>& vec) {
  if (vector_vars.count(name) == 0) {
    TBranch* b = Branch(name.c_str(), &vector_vars[name]);

    int n_entries = GetEntries();
    for (int i=0; i < n_entries; ++i) {
      b->Fill();
    }
  }

  std::vector<float>& outvec = vector_vars[name];
  for (auto f : vec) {
    outvec.push_back(f);
  }
}

void OutputTree::add_photon_type(const std::string& name) {
  if (ph_names.count(name) != 0) return;

  TBranch* b_pt = Branch((name+"_pt").c_str(), &ph_vars[name+"_pt"]);
  TBranch* b_eta = Branch((name+"_eta").c_str(), &ph_vars[name+"_eta"]);
  TBranch* b_phi = Branch((name+"_phi").c_str(), &ph_vars[name+"_phi"]);

  int n_entries = GetEntries();
  for (int i = 0; i < n_entries; ++i) {
    b_pt->Fill();
    b_eta->Fill();
    b_phi->Fill();
  }

  ph_names.insert(name);
}

void OutputTree::add_photon(const std::string& name, const TLorentzVector& ph) {
  add_photon_type(name);

  ph_vars[name+"_pt"].push_back(ph.Pt());
  ph_vars[name+"_eta"].push_back(ph.Eta());
  ph_vars[name+"_phi"].push_back(ph.Phi());
}

void OutputTree::add_jet_type(const std::string& name) {
  if (jet_names.count(name) != 0) return;

  TBranch* b_pt = Branch((name+"_pt").c_str(), &jet_vars[name+"_pt"]);
  TBranch* b_eta = Branch((name+"_eta").c_str(), &jet_vars[name+"_eta"]);
  TBranch* b_phi = Branch((name+"_phi").c_str(), &jet_vars[name+"_phi"]);
  TBranch* b_m = Branch((name+"_m").c_str(), &jet_vars[name+"_m"]);

  int n_entries = GetEntries();
  for (int i = 0; i < n_entries; ++i) {
    b_pt->Fill();
    b_eta->Fill();
    b_phi->Fill();
    b_m->Fill();
  }

  jet_names.insert(name);
}

void OutputTree::add_jet(const std::string& name, const TLorentzVector& j) {
  add_jet_type(name);

  jet_vars[name+"_pt"].push_back(j.Pt());
  jet_vars[name+"_eta"].push_back(j.Eta());
  jet_vars[name+"_phi"].push_back(j.Phi());
  jet_vars[name+"_m"].push_back(j.M());
}

void OutputTree::add_jet(const std::string& name, const fastjet::PseudoJet& j) {
  add_jet_type(name);

  jet_vars[name+"_pt"].push_back(j.pt());
  jet_vars[name+"_eta"].push_back(j.eta());
  jet_vars[name+"_phi"].push_back(j.phi());
  jet_vars[name+"_m"].push_back(j.m());
}

void OutputTree::add_jets(const std::string& name, const std::vector<TLorentzVector>& jets) {
  for (auto j : jets) {
    add_jet(name, j);
  }
}

void OutputTree::add_jets(const std::string& name, const std::vector<fastjet::PseudoJet>& jets) {
  for (auto j : jets) {
    add_jet(name, j);
  }
}

void OutputTree::add_jets(const std::string& name, const xAOD::JetContainer* jets) {
  for (auto j : *jets) {
    add_jet(name, j->p4());
  }
}

void OutputTree::add_jets(const std::string& name, const xAOD::JetContainer& jets) {
  for (auto j : jets) {
    add_jet(name, j->p4());
  }
}

void OutputTree::add_jets(const std::string& name, const std::vector<const xAOD::Jet*>& jets) {
  for (auto j : jets) {
    add_jet(name, j->p4());
  }
}

void OutputTree::add_truth_type(const std::string& name) {
  if (truth_names.count(name) != 0) return;

  TBranch* b_pt = Branch((name+"_pt").c_str(), &truth_vars[name+"_pt"]);
  TBranch* b_eta = Branch((name+"_eta").c_str(), &truth_vars[name+"_eta"]);
  TBranch* b_phi = Branch((name+"_phi").c_str(), &truth_vars[name+"_phi"]);
  TBranch* b_m = Branch((name+"_m").c_str(), &truth_vars[name+"_m"]);
  TBranch* b_status = Branch((name+"_status").c_str(), &truth_vars[name+"_status"]);
  TBranch* b_pid = Branch((name+"_pid").c_str(), &truth_vars[name+"_pid"]);

  int n_entries = GetEntries();
  for (int i = 0; i < n_entries; ++i) {
    b_pt->Fill();
    b_eta->Fill();
    b_phi->Fill();
    b_m->Fill();
    b_status->Fill();
    b_pid->Fill();
  }

  truth_names.insert(name);
}

void OutputTree::add_truth(const std::string& name, const xAOD::TruthParticle* particle) {
  add_truth_type(name);

  truth_vars[name+"_pt"].push_back(particle->pt());
  truth_vars[name+"_eta"].push_back(particle->eta());
  truth_vars[name+"_phi"].push_back(particle->phi());
  truth_vars[name+"_m"].push_back(particle->m());
  truth_vars[name+"_status"].push_back(particle->status());
  truth_vars[name+"_pid"].push_back(particle->pdgId());
}

void OutputTree::add_truths(const std::string& name, const std::vector<const xAOD::TruthParticle*>& particles) {
  for (auto p : particles) {
    add_truth(name, p);
  }
}

void OutputTree::clear() {
  for (auto &p : vector_vars) {
    p.second.clear();
  }
  for (auto &p : ph_vars) {
    p.second.clear();
  }
  for (auto &p : jet_vars) {
    p.second.clear();
  }
  for (auto &p : truth_vars) {
    p.second.clear();
  }
}
