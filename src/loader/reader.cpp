
#include "reader.h"
#include "debug.h"
#include <iostream>
#include <regex>
#include <fstream>

FileReader::FileReader(std::string filename)
{
    this->loadFileName(filename);
}

void FileReader::loadFileName(std::string filename)
{
    debug("%s Loading file %s", PLUGIN_INFO, filename.c_str());
    std::ifstream file(PLUGIN_CONFIG_PATH + filename + ".txt");
    std::string line;
    unsigned int pos = 0;
    while (getline(file, line))
    {
        pos++;
        if ((line == "") || (line[0] == ';') || (line[0] == '/') || (line[0] == '#'))
            continue;
        else if (this->loadInclude(line))
            /* Loader from new File*/;
        else if (this->loadData(line, filename, pos))
            /* Loader Data*/;
        else
            throw Exception("%s LoadFile incorrect/unexpected line [%s][%s][%d]", PLUGIN_ERROR, line.c_str(), filename.c_str(), pos);
    }
}

bool FileReader::loadInclude(std::string line)
{
    std::smatch query;
    std::regex regex("LOAD FROM FILE (([\\w\\d]+\\/?)+)");
    // 0 LOAD FROM FILE C172/BIP/bip0
    // 1 C172/BIP/bip0
    // 2 bip0
    if (std::regex_match(line, query, regex))
    {
        this->loadFileName(query[1].str());
        return true;
    }
    return false;
}

bool FileReader::loadData(std::string line, std::string filename, int pos)
{
    std::smatch query;
    std::regex regex("(\\w+)\\s+(\\-?\\d+)\\s+([\\w\\d\\:\\-\\[\\]\\/]+)\\s+([\\w\\d\\:\\-\\[\\]\\/]+)\\s+(.+)");
    // 0 MULTI 1 audio LED dataref(sim/cockpit2/radios/actuators/audio_selection_com1){1:1}
    // 1 MULTI
    // 2 1
    // 3 audio
    // 4 LED
    // 5 dataref(sim/cockpit2/radios/actuators/audio_selection_com1){1:1}
    if (std::regex_match(line, query, regex))
    {
        FileContentLine *raw = new FileContentLine();
        strcpy(raw->line, line.c_str());
        strcpy(raw->filename, filename.c_str());
        strcpy(raw->panelName, query[1].str().c_str());
        strcpy(raw->button, query[3].str().c_str());
        strcpy(raw->key, query[4].str().c_str());
        strcpy(raw->value, query[5].str().c_str());
        raw->lineNumber = pos;
        raw->panelNumber = std::atoi(query[2].str().c_str());
        raw->usage = false;
        this->content.insert(this->content.begin(), 1, raw);
        return true;
    }
    return false;
}
