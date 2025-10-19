#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int memory_cells[30000] = {0};
int* it = memory_cells;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "The file is not transferred.\n";
        return 1;
    }
    ifstream file(argv[1]); // Первый аргумент — путь к файлу
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << argv[1] << endl;
        return 1;
    }
    
    stringstream buffer;  // преобразуем в string
    buffer << file.rdbuf();  // считываем весь буфер файла в поток stringstream
    
    string code = buffer.str();
    //удаляем все символы кроме <>[]+-.,
    code.erase(remove_if(code.begin(), code.end(),
    [](char c) {
        return string("[]-+<>.,").find(c) == string::npos;
    }),
    code.end());
    
	int b = 0;
    for(auto command = code.begin(); command != code.end(); ++command) {
        switch(*command){
            case '>':
                ++it;
                if (it > memory_cells + 30000) {cerr << "Error: exit beyond memory.\n"; return 1;};
                break;
            case '<':
                --it;
                if (it < memory_cells) {cerr << "Error: exit beyond memory.\n"; return 1;};
                break;
            case '+':++*it;break;
            case '-':--*it;break;
            case '.':cout << (char)*it;break;
            case ',':*it=getchar();break;
            case '[':
                if (*it) continue;
                b = 1;
                while(b)
					switch(*++command){
						case '[': ++b; break;
						case ']': --b; break;
					}
				break;
            case ']':
                if(!*it) continue;
                b = 1;
                while(b)
                    switch(*--command){
                        case '[': --b; break;
                        case ']': ++b; break;
                    }
                --command;
                break;
        }
    }
    return 0;
}
