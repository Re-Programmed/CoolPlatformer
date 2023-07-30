#include "AppDataFileManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace GAME_NAME
{
	namespace AppData
	{
		std::string AppDataFileManager::m_appFolder;

		/// <summary>
		/// Creates a file at a path and writes a variable and value to it.
		/// </summary>
		/// <param name="filePath">Path to the file.</param>
		/// <param name="variable">Variable to write.</param>
		/// <param name="value">Value to assign the written variable.</param>
		inline void CreateFileWithVariable(std::filesystem::path filePath, std::string variable, std::string value)
		{
			std::filesystem::create_directories(filePath.parent_path());

			std::ofstream createFile(filePath);

			createFile << variable << ": " << value << std::endl;
			createFile.close();
		}

		/// <summary>
		/// Appends a variable to a file.
		/// </summary>
		/// <param name="filePath">Path to the file that will be written to.</param>
		/// <param name="variable">Variable to write.</param>
		/// <param name="value">The value to give the written variable.</param>
		/// <param name="fullFile">The current contents of the file that will be written to.</param>
		inline void AddVariable(std::filesystem::path filePath, std::string variable, std::string value, std::string fullFile)
		{
			std::ofstream addVariable(filePath);

			addVariable << fullFile;
			addVariable << variable << ": " << value << std::endl;
			addVariable.close();
		}

		void AppDataFileManager::SetValue(std::string file, std::string variable, std::string value)
		{
			std::filesystem::path filePath = m_appFolder.append("\\").append(file);
			if (std::filesystem::exists(filePath))
			{
				std::string fullFile;

				std::ifstream readFile(filePath);
				std::string line;

				while (std::getline(readFile, line, '\n'))
				{
					if (!line.starts_with(variable))
					{
						fullFile.append(line).append("\n");
					}
				}

				readFile.close();

				AddVariable(filePath, variable, value, fullFile);
			}
			else {
				CreateFileWithVariable(filePath, variable, value);
			}
		}

		std::string AppDataFileManager::GetValue(std::string file, std::string variable, std::string defaultvalue)
		{
			std::filesystem::path filePath = m_appFolder.append("\\").append(file);
			if (std::filesystem::exists(filePath))
			{
				std::string fullFile;

				std::ifstream readFile(filePath);
				std::string line;

				while (std::getline(readFile, line, '\n'))
				{
					if (line.starts_with(variable))
					{
						return line.erase(0, variable.length() + 2);
					}

					fullFile = fullFile.append(line).append("\n");
				}

				readFile.close();

				AddVariable(filePath, variable, defaultvalue, fullFile);
				
				return defaultvalue;
			}
			else {
				CreateFileWithVariable(filePath, variable, defaultvalue);
				
				return defaultvalue;
			}
		}

		void AppDataFileManager::CreateAppDataFiles()
		{
			char* appDataFolder;
			size_t len;
			errno_t err = _dupenv_s(&appDataFolder, &len, "APPDATA");

			if (appDataFolder == NULL)
			{
				std::cout << "APPDATA folder does not exist!" << std::endl;
				return;
			}

			m_appFolder = std::string(appDataFolder) + std::string(APPDATA_SUBFOLDER);

			if (!std::filesystem::exists(m_appFolder))
			{
				std::filesystem::create_directories(m_appFolder);
			}
		}
	}
}
