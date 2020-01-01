#include "class.h"

int Processo::getArrival() {
	return this->arrival;
}

void Processo::setArrival(int c) {
	this->arrival = c;
}

int Processo::getDuration() {
	return this->duration;
};

void Processo::setDuration(int d) {
	this->duration = d;
};

int Processo::getLaunch() {
	return this->launch;
};

void Processo::setLaunch(int l) {
	this->launch = l;
};

int Processo::getSlices() {
	return this->slices;
};

void Processo::setSlices(int s) {
	this->slices = s;
};

int Processo::getAc_slices() {
	return this->ac_slices;
};

void Processo::setAc_slices(int as) {
	this->ac_slices = as;
};

int Processo::getMemory() {
	return this->memory;
};

void Processo::setMemory(int m) {
	this->memory = m;
};

int Processo::getPriority() {
	return this->priority;
};

void Processo::setPriority(int p) {
	this->priority = p;
};

int Processo::getStatic_priority() {
	return this->static_priority;
};

void Processo::setStatic_priority(int pe) {
	this->static_priority = pe;
};

int Processo::getWatch() {
	return this->watch;
};

void Processo::setWatch(int o) {
	this->watch = o;
};

int Processo::getMark() {
	return this->mark;
};

void Processo::setMark(int mc) {
	this->mark = mc;
};

Processo CPU(Processo process, int lanc) {
	process.setSlices(process.getSlices()-1);
	process.setAc_slices(process.getAc_slices()+1); //Acumulador de slices para fazer a troca de priority
	if (process.getLaunch() == -1) {
		process.setLaunch(lanc);
	}
	//Faz o teste se o processo ja teve 10 slices executadas e faz a troca de priority
	if (process.getAc_slices() == 10) {
		if ((process.getStatic_priority() != 0) and (process.getStatic_priority() != 4)) { //processos com priority inicial 0 e 4 n�o sofrem altera��o
			if (process.getStatic_priority() == process.getPriority()) {
				process.setPriority(process.getPriority()+1);
			}
			else {
				process.setPriority(process.getPriority()-1);
			}
		}
		process.setAc_slices(0);
	}
	process.setMark(1);

	return process;
}

void StringSplit(string str, string delim, vector<string>& results){
	int cutAt;
	while ((cutAt = str.find_first_of(delim)) != str.npos)
	{
		if (cutAt > 0) {
			results.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0) {
		results.push_back(str);
	}
}