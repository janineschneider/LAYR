#include "dos.h"
#include <iostream>

DOS::DOS(ByteContainer* rawData) : m_rawData(rawData)
{
    //TODO Check for empty pointer
}

DOS::~DOS()
{
    if (m_rawData != nullptr) {
        delete m_rawData;
    }
}

std::vector<std::vector<uint64_t>> DOS::evaluate(std::vector<uint64_t> input)
{
    //Result vector
    std::vector<uint64_t> blockSeqence;
    std::vector<std::vector<uint64_t>> extendedBlockSeqences;
    std::vector<std::vector<uint64_t>> blockSeqences;

    try {
        //Variable initialization
        unsigned char bytes[4];
        uint32_t num32 = 0;

        //Seperate partition table entries
        std::vector<std::pair<uint32_t, uint32_t>> tableEntries;
        tableEntries.push_back(std::make_pair(446, 461));
        tableEntries.push_back(std::make_pair(462, 477));
        tableEntries.push_back(std::make_pair(478, 493));
        tableEntries.push_back(std::make_pair(494, 509));

        for(auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
            if ((m_rawData->at(it->first, 12, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 13, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 14, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 15, input.at(0), input.at(input.size() - 1)) == 0x00)) {
                break;
            }
            else {
                //Store starting LBA address in sectors
                bytes[0] = m_rawData->at(it->first, 8, input.at(0), input.at(input.size() - 1));
                bytes[1] = m_rawData->at(it->first, 9, input.at(0), input.at(input.size() - 1));
                bytes[2] = m_rawData->at(it->first, 10, input.at(0), input.at(input.size() - 1));
                bytes[3] = m_rawData->at(it->first, 11, input.at(0), input.at(input.size() - 1));
                num32 = 0;
                std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
                blockSeqence.push_back(num32);

                //Store size in sectors
                bytes[0] = m_rawData->at(it->first, 12, input.at(0), input.at(input.size() - 1));
                bytes[1] = m_rawData->at(it->first, 13, input.at(0), input.at(input.size() - 1));
                bytes[2] = m_rawData->at(it->first, 14, input.at(0), input.at(input.size() - 1));
                bytes[3] = m_rawData->at(it->first, 15, input.at(0), input.at(input.size() - 1));
                num32 = 0;
                std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

                //Check partition type
                if ((m_rawData->at(it->first, 4, input.at(0), input.at(input.size() - 1)) == 0x05) ||
                    (m_rawData->at(it->first, 4, input.at(0), input.at(input.size() - 1)) == 0x0f)) {
                    extendedBlockSeqences = handleExtended(blockSeqence.at(0), input);
                    for (auto it = extendedBlockSeqences.begin(); it != extendedBlockSeqences.end(); ++it) {
                        blockSeqences.push_back(*it);
                    }
                }
                else {
                    for (uint32_t i = 0; i < num32; i++) {
                        blockSeqence.push_back(blockSeqence.at(0) + i);
                    }
                    blockSeqences.push_back(blockSeqence);
                }

                blockSeqence.clear();
            }
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return blockSeqences;
}

std::vector<std::vector<uint64_t>> DOS::handleExtended(uint32_t offset, std::vector<uint64_t> input)
{
    //Result vector
    std::vector<uint64_t> blockSeqence;
    std::vector<std::vector<uint64_t>> extendedBlockSeqences;
    std::vector<std::vector<uint64_t>> blockSeqences;

    try {
        //Variable initialization
        unsigned char bytes[4];
        uint32_t num32 = 0;

        //Seperate partition table entries
        std::vector<std::pair<uint32_t, uint32_t>> tableEntries;
        tableEntries.push_back(std::make_pair((offset * 512) + 446, (offset * 512) + 461));
        tableEntries.push_back(std::make_pair((offset * 512) + 462, (offset * 512) + 477));
        tableEntries.push_back(std::make_pair((offset * 512) + 478, (offset * 512) + 493));
        tableEntries.push_back(std::make_pair((offset * 512) + 494, (offset * 512) + 509));

        for(auto it = tableEntries.begin(); it != tableEntries.end(); ++it) {
            if ((m_rawData->at(it->first, 12, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 13, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 14, input.at(0), input.at(input.size() - 1)) == 0x00) &&
                (m_rawData->at(it->first, 15, input.at(0), input.at(input.size() - 1)) == 0x00)) {
                break;
            }
            else {
                //Store starting LBA address in sectors
                bytes[0] = m_rawData->at(it->first, 8, input.at(0), input.at(input.size() - 1));
                bytes[1] = m_rawData->at(it->first, 9, input.at(0), input.at(input.size() - 1));
                bytes[2] = m_rawData->at(it->first, 10, input.at(0), input.at(input.size() - 1));
                bytes[3] = m_rawData->at(it->first, 11, input.at(0), input.at(input.size() - 1));
                num32 = 0;
                std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
                blockSeqence.push_back(num32 + offset);

                //Store size in sectors
                bytes[0] = m_rawData->at(it->first, 12, input.at(0), input.at(input.size() - 1));
                bytes[1] = m_rawData->at(it->first, 13, input.at(0), input.at(input.size() - 1));
                bytes[2] = m_rawData->at(it->first, 14, input.at(0), input.at(input.size() - 1));
                bytes[3] = m_rawData->at(it->first, 15, input.at(0), input.at(input.size() - 1));
                num32 = 0;
                std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

                //Check partition type
                if ((m_rawData->at(it->first, 4, input.at(0), input.at(input.size() - 1)) == 0x05) ||
                    (m_rawData->at(it->first, 4, input.at(0), input.at(input.size() - 1)) == 0x0f)) {
                    extendedBlockSeqences = handleExtended(blockSeqence.at(0), input);
                    for (auto it = extendedBlockSeqences.begin(); it != extendedBlockSeqences.end(); ++it) {
                        blockSeqences.push_back(*it);
                    }
                }
                else {
                    for (uint32_t i = 0; i < num32; i++) {
                        blockSeqence.push_back(blockSeqence.at(0) + i);
                    }
                    blockSeqences.push_back(blockSeqence);
                }

                blockSeqence.clear();
            }
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return blockSeqences;
}
