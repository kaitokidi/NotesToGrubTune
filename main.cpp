#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>

namespace Solfage {
  enum NOTES {
    DO,DOs,RE,MIb,MI,FA,FAs,SOL,SOLs,LA,SIb,SI
  };
};

namespace Absolute {
  enum NOTES {
    C,Cs,D,Eb,E,F,Fs,G,Gs,A,Bb,B
  };
};

struct Note {
  int scale;
  std::string note;
  Note(std::string n) {
    scale = n[0]-'0';
    n.erase(n.begin());
    note = n;
  }
};

std::vector<std::vector<int> > notas;  
bool grub = false;

void write(std::vector<std::vector<int> > &v) {
  for (int i = 0; i < v.size(); ++i) {
    std::cout << i << std::endl;
    for (int j = 0; j < v[i].size(); ++j) std::cout << v[i][j] << " ";
    std::cout << std::endl;
  }
}

void init() {
  notas.push_back(std::vector<int>());
  float anterior = 16.35;
  notas[0].push_back(anterior);
  float next;
  int i = 0;
  int j = 1;
  while (next <= 20000) {
    next = anterior*pow(2.f,(i*12+j)/12.f);
    //anterior = next;
    notas[i].push_back(roundf(next));
    if (++j > 12) { j = 0; ++i; notas.push_back(std::vector<int>());}  
  }
  if (notas[notas.size()-1].size() != 12) notas.erase(notas.end()-1);
}

 

int translate(Note n) {
  std::string nn = n.note;
  if (nn == "DO" or nn == "C") return notas[n.scale][Solfage::DO];
  else if (nn == "DO#" or nn == "C#") return notas[n.scale][Solfage::DOs];
  else if (nn == "RE" or nn == "D") return notas[n.scale][Solfage::RE];
  else if (nn == "MIB" or nn == "EB") return notas[n.scale][Solfage::MIb];
  else if (nn == "MI" or nn == "E") return notas[n.scale][Solfage::MI];
  else if (nn == "FA" or nn == "F") return notas[n.scale][Solfage::FA];
  else if (nn == "FA#" or nn == "F#") return notas[n.scale][Solfage::FAs];
  else if (nn == "SOL" or nn == "G") return notas[n.scale][Solfage::SOL];
  else if (nn == "SOL#" or nn == "G#") return notas[n.scale][Solfage::SOLs];
  else if (nn == "LA" or nn == "A") return notas[n.scale][Solfage::LA];
  else if (nn == "SIB" or nn == "BB") return notas[n.scale][Solfage::SIb];
  else if (nn == "SI" or nn == "B") return notas[n.scale][Solfage::SI];
  return 0;
}

std::string toStdNote(std::string s) {
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] >= 'a' and s[i] <= 'z') s[i] -= 'a'-'A'; 
  } 
  return s;
}

std::vector<int> readNotes () {
  std::vector<int> aux;
  std::string s;
  while (std::cin >> s) {
    if (s == ",") aux.push_back(0);
    else {
      Note n(s);
      if (n.scale > 8) { std::cout << "BROKEN SCALE ON " << s << std::endl; exit(1);} // son como cervatillos heridos como yo
      n.note = toStdNote(n.note);
      aux.push_back(translate(n));
    }
  }
  return aux;
}

void writeHz(std::vector<int> &s) {
  for (int  i = 0; i < s.size(); ++i) std::cout << s[i] << " ";
  std::cout << std::endl;
}

void writeGrub(float t, std::vector<int> &s) {
  std::cout << 60.f/t << " ";
  int count = 1;
  int anterior = s[0];
  std::cout << anterior << " ";
  for (int  i = 1; i < s.size(); ++i) {
    if (s[i] != anterior) {
      std::cout << count << " " << s[i] << " ";
      count = 1;
      anterior = s[i];
    }
    else ++count;
  }
  std::cout << count << std::endl;
}

int main (int argc, char* argv[]) {
  init();
  std::vector<int> salida;
  float tempo;
  if (argc == 2 and (strcmp(argv[1],"-h") == 0 or strcmp(argv[1],"--help") == 0)) {std::cout << "The Readme is your friend" << std::endl;exit(0);}
  if (argc == 2 and strcmp(argv[1],"--grubTune") == 0) grub = true;
  if (grub) std::cin >> tempo;
  salida = readNotes();
  if (not grub) writeHz(salida);
  else writeGrub(tempo,salida);
  return 0;
}
