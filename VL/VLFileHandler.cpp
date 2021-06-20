#include "VLMain.h"

namespace VL {
	VL_FileHandler::VL_FileHandler() {
		;
	}

	VL_FileHandler::~VL_FileHandler() {
		this->files.clear();
	}

	void VL_FileHandler::addFile(VL_file& file) {
		this->files.push_back(file);
	}
	void VL_FileHandler::addFile(const std::string& VL_S_Location, const std::string& Name) {
		VL_file* file = new VL_file(VL_S_Location, Name);
		this->files.push_back(*file);
		delete file;
		file = NULL;
	}

	VL_file* VL_FileHandler::getFile(const std::string& name) {
		for (int i = 0; i < files.size(); i++) {
			if (files[i].filename == name)
				return &files[i];
		}

		return NULL;
	}
	VL_file* VL_FileHandler::getFile(int index) {
		if (index < files.size())
			return &files[index];

		return NULL;
	}

	std::vector<VL_file>* VL_FileHandler::getList() {
		return &files;
	}
}