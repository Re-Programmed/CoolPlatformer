#include "SaveManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../base64.h"
#include "../../Settings/AppDataFileManager.h"

namespace GAME_NAME::Resources
{
	std::string SaveManager::m_currentSaveFile;

	void SaveManager::SaveString(std::string data, std::string vName)
	{
		const std::filesystem::path fileFolderPath = SM_AppData + std::string(APPDATA_SUBFOLDER).append(SAVE_SUBFOLDER_NAME);

		const std::filesystem::path filePath = std::string(fileFolderPath.string()).append("\\").append(m_currentSaveFile).append(SAVE_FILE_EXTENSION);

		if (std::filesystem::exists(filePath))
		{
			std::string fullFile;

			std::ifstream readFile(filePath);

			while (std::getline(readFile, fullFile))
			{

			}

			readFile.close();

			std::stringstream fileDecoded(B64::Decode(fullFile));
			std::string decodedFile;

			std::string line;
			while (std::getline(fileDecoded, line, '\n'))
			{
				if (!line.starts_with(vName))
				{
					decodedFile.append(line + '\n');
				}
			}

			std::ofstream createstream(filePath);
			createstream << B64::Encode(fullFile.append("\n") + vName + "{" + data + "}");
			createstream.close();
		}
		else
		{
			std::filesystem::create_directories(fileFolderPath);

			std::ofstream createstream(filePath);
			createstream << B64::Encode(vName + "{" + data + "}");
			createstream.close();

			SaveString(data, vName);
		}

	}

	void SaveManager::SetCurrentFile(std::string fileName)
	{
		m_currentSaveFile = fileName;
	}

}
