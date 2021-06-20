#include "VLMain.h"

namespace VL {
	void VL_file::load(const std::string& VL_S_Location, const std::string& Name) {
	
		std::vector<std::string>* a = new std::vector<std::string>();
		std::fstream stream;
		if (Name == "") {
			this->filename = VL_S_Location;
		}
		else {
			this->filename = Name;
		}

		stream.open(VL_S_Location, std::ios::in);
		if (stream.good()) {
			std::string str;
			while (std::getline(stream, str)) {
				a->push_back(str);
			}

			// checking all lines
			for (int i = 0; i < a->size(); i++) {

				std::string line = (*a)[i];
				std::string l_name = "";

				std::string l_value = "";
				if (line.length() > 0) {
					if (line[0] != '#') {
						// finding '=' in line
						/* starts with \ */

						if (line[0] == 0x5C) {
							this->V_list[this->V_list.size() - 1].value += " " + line.substr(1, line.size() - 1);
						}
						else if (line[0] == '&') {
							this->V_list[this->V_list.size() - 1].value += "\n" + line.substr(1, line.size() - 1);
						}
						else {
							// finding '=' in line
							if (line.find('=') < line.length()) {
								int eqPos = strcspn(line.c_str(), "=");
								l_name = line.substr(0, eqPos);
								l_value = line.substr(eqPos + 1, line.size() - (eqPos + 1));								
							}
							else {
								l_name = line;
							}
							bool repeat = 0;
							for (int j = 0; j < this->V_list.size(); j++) {
								if (this->V_list[j].title == l_name) {
									// podmiana wartosci
									this->V_list[j].value = l_value;
									repeat = true;
								}

							}
							if (!repeat) {
								V_list.push_back(VL_variable(l_name, l_value));
							}
						}
					}
				}
			}

		}
		
		stream.close();
	
		delete a;
		a = NULL;
	}
	// ----- search functions -----

	std::vector<VL_variable>* VL_file::getList() {
		return &this->V_list;
	}

	std::string VL_file::getName() {
		return this->filename;
	}

	std::string VL_file::getValue(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return V_list[i].value;
		}
		return "";
	}

	std::string VL_file::getValue(int index) {
		if (index < V_list.size())
			return V_list[index].value;
		return "";
	}

	int VL_file::getIndex(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return i;
		}
		return -1;
	}

	VL_variable* VL_file::getVariable(int index) {
		if (index < V_list.size())
			return &V_list[index];
		return NULL;
	}
	VL_variable* VL_file::getVariable(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return &V_list[i];
		}
		return NULL;
	}

	// ======================= HANDLER =======================



	// utility functions
	std::vector<VL_variable>* VL_Handler::getList() {
		return &this->V_list;
	}

	void VL_Handler::add(VL_variable* variable) {
		bool sorted = false;
		V_list.push_back(*variable);
		
	}

	std::string VL_Handler::getValue(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return V_list[i].value;
		}
		return "";
	}

	std::string VL_Handler::getValue(int index) {
		if (index < V_list.size())
			return V_list[index].value;
		return "";
	}

	int VL_Handler::getIndex(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return i;
		}
		return -1;
	}

	VL_variable* VL_Handler::getVariable(int index) {
		if (index < V_list.size())
			return &V_list[index];
		return NULL;
	}
	VL_variable* VL_Handler::getVariable(const std::string& name) {
		for (int i = 0; i < V_list.size(); i++) {
			if (V_list[i].title == name)
				return &V_list[i];
		}
		return NULL;
	}


}