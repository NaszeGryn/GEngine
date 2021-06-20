#include <string>
#include <vector>
#include <fstream>
#include <iostream>
namespace VL {
	// Variable struct
	struct VL_variable {
		// constructor
		VL_variable(const std::string& title, const std::string& value) {
			this->title = title;
			this->value = value;
		}

		// variables
		std::string title;
		std::string value;
	};


	// varialbe language file 
	class VL_file {
	public:
		//constructor
		VL_file(const std::string& VL_S_Location, const std::string& Name = "") {
			this->load(VL_S_Location, Name);
		}

		// interpreter
		void load(const std::string& VL_S_Location, const std::string& Name = "");

		// ---- search functions ---- 
		std::string getName();

		std::string getValue(const std::string& name);

		std::string getValue(int index);

		int getIndex(const std::string& name);

		VL_variable* getVariable(int index);
		VL_variable* getVariable(const std::string& name);

		std::vector<VL_variable>* getList();
	public:
		std::vector<VL_variable> V_list;
		std::string filename;
		
	};

	// combines variables from file to variable list
	static void combine(std::vector<VL_variable>* V_list, VL_file* file) {
		for (int i = 0; i < file->V_list.size(); i++) {

			bool repeat = 0;
			for (int j = 0; j < V_list->size(); j++) {
				if ((*V_list)[j].title == file->V_list[i].title) {
					(*V_list)[j].value = file->V_list[i].value;
					repeat = true;
				}

			}

			if (!repeat) {
				V_list->push_back(file->V_list[i]);
			}
		}
	}

	static void saveToFile(VL_file& file, const std::string& filename, bool clear_file) {
		std::fstream stream;
		if (clear_file)
			stream.open(filename, std::ios::out | std::ios::trunc);
		else
			stream.open(filename, std::ios::out);

		for (int i = 0; i < file.V_list.size(); i++) {
			stream << file.V_list[i].title;
			if (file.V_list[i].value != "") {
				stream << "=";
				for (int j = 0; j < file.V_list[i].value.size(); j++) {
					stream << file.V_list[i].value[j];
					if (file.V_list[i].value[j] == '\n') {
						stream << '&';
					}
				}
			}
			stream << "\n";
		}

		stream.close();
	}

	

	// variable handler
	class VL_Handler {
	public:
		VL_Handler() { ; }
		~VL_Handler() {
			V_list.clear();
		}

		// adds variables from file
		void addFromFile(const std::string& VL_S_Location) {
			VL_file* tempFile = new VL_file(VL_S_Location);
			VL::combine(&V_list, tempFile);
			delete tempFile;
			tempFile = NULL;
		}


		// adds variable
		void add(VL_variable* variable);

		std::string getValue(const std::string& name);

		std::string getValue(int index);
		int getIndex(const std::string& name);

		VL_variable* getVariable(int index);
		VL_variable* getVariable(const std::string& name);


		std::vector<VL_variable>* getList();
	public:

		std::vector<VL_variable> V_list;
	};

	static void saveToFile(VL_Handler& file, const std::string& filename, bool clear_file) {
		std::fstream stream;
		if (clear_file)
			stream.open(filename, std::ios::out | std::ios::trunc);
		else
			stream.open(filename, std::ios::out);

		for (int i = 0; i < file.V_list.size(); i++) {
			stream << file.V_list[i].title;
			if (file.V_list[i].value != "") {
				stream << "=";
				for (int j = 0; j < file.V_list[i].value.size(); j++) {
					stream << file.V_list[i].value[j];
					if (file.V_list[i].value[j] == '\n') {
						stream << '&';
					}
				}
			}
			stream << "\n";
		}

		stream.close();
	}

	class VL_FileHandler {
	public:
		VL_FileHandler();
		~VL_FileHandler();

		void addFile(VL_file& file);
		void addFile(const std::string& VL_S_Location, const std::string& Name = "");

		VL_file* getFile(const std::string& name);
		VL_file* getFile(int index);

		std::vector<VL_file>* getList();
	private:
		std::vector<VL_file> files;
	};
}
