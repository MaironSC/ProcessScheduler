#include "class.h"


int main(int argc, char* argv[]) {
	
	int cpus, total_mem = 0, cont_slices = 0, go_cpu = 0, memory, slice_lanc = 0, i, j;
	bool flag_processo = false;
	char* file;
	array<list<Processo>, 5> processos;
	list <Processo> disc;
	vector <string> parametros;
	list <Processo> dadosF;
	Processo p;
	cpus = atoi(argv[1]);
	memory = atoi(argv[2]);
	file = argv[3];
	ifstream pf(file);
	string line;
	int total;


	while (getline(pf, line)) {
		StringSplit(line, ",", parametros);
		p.setArrival(atoi(parametros[0].c_str()));
		p.setSlices(atoi(parametros[1].c_str()));
		p.setMemory(atoi(parametros[2].c_str()));
		p.setPriority(atoi(parametros[3].c_str()));
		p.setStatic_priority(atoi(parametros[3].c_str()));
		p.setWatch(1);
		p.setAc_slices(0);
		p.setMark(0);
		p.setDuration(p.getSlices());
		disc.push_back(p);
		parametros.pop_back();
		parametros.pop_back();
		parametros.pop_back();
		parametros.pop_back();
	}


	while ((disc.size() != 0) or (processos[0].size() != 0) or (processos[1].size() != 0) or (processos[2].size() != 0) or (processos[3].size() != 0) or (processos[4].size() != 0)) {
		cont_slices++;
		go_cpu = 0;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < disc.size(); j++) {
				if (disc.front().getArrival() <= slice_lanc) {
					if (disc.front().getPriority() == i) {
						processos[i].push_back(disc.front());
						disc.pop_front();
					}
				}
				else {
					disc.push_back(disc.front());
					disc.pop_front();
				}
				
			}
		}

		for (i = 0; i < 5; i++) { 
			for (j = 0; j < processos[i].size(); j++) {
				processos[i].front().setWatch(processos[i].front().getWatch()+1);
				processos[i].push_back(processos[i].front());
				processos[i].pop_front();
			}
		}
		
		while (cpus != go_cpu) {
			for (i = 0; i < 5; i++) {
				if ((processos[i].size() != 0) and flag_processo == 0) {
					for (j = 0; j < processos[i].size(); j++) {
						if (processos[i].front().getMemory() > memory) {
							processos[i].pop_front();
						}
						if (processos[i].front().getMark() == 1) {
							break;
						}
						total_mem = total_mem + processos[i].front().getMemory();

						if (total_mem <= memory) {
							flag_processo = 1;
							break;
						}
						else {
							flag_processo = 0;
							total_mem = total_mem - processos[i].front().getMemory();
							processos[i].push_back(processos[i].front());
							processos[i].pop_front();
						}
					}
					
					if (flag_processo == 1 and processos[i].front().getMark() == 0) {
						processos[i].push_back(CPU(processos[i].front(), slice_lanc));
						processos[i].pop_front();
						
						if (processos[i].back().getSlices() <= 0) {
							dadosF.push_back(processos[i].back());
							processos[i].pop_back();
						}
						else if((processos[i].back().getPriority() != 0) and (processos[i].back().getPriority() != 4)){
							processos[processos[i].back().getPriority()].push_back(processos[i].back());
							processos[i].pop_back();
						}
					}
				}
			}
			flag_processo = 0; 
			go_cpu++;
		}

		for (i = 0; i < 5; i++) {
			for (j = 0; j < processos[i].size(); j++) {
				processos[i].front().setMark(0);
				processos[i].push_back(processos[i].front());
				processos[i].pop_front();
			}
		}
		
		total_mem = 0;
		slice_lanc++;
	}
	cout << "\nDados do Escalonador: \n --Numero de CPUS: "<< cpus << "\n --Quantidade de memory: "<< memory <<"\n";
	
	
	for (int i = 0; i < dadosF.size(); i++) {
		cout << "Chegada:" << dadosF.front().getArrival() <<", Lancamento: " << dadosF.front().getLaunch() <<", Duracao Projetada: " << dadosF.front().getDuration()<< ", duracao observada: " << dadosF.front().getWatch() << endl;
		dadosF.push_back(dadosF.front());
		dadosF.pop_front();
	}
}