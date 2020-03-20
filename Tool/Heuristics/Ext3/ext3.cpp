#include "ext3.h"

#include <algorithm>
#include <iostream>

Ext3::Ext3(ByteContainer* rawData) : m_rawData(rawData)
{
    //TODO Check for empty pointer
}

Ext3::~Ext3()
{
    if (m_rawData != nullptr) {
        delete m_rawData;
    }
}

std::vector<std::vector<uint64_t>> Ext3::evaluate(std::vector<uint64_t> input)
{
    //Result vector
    std::vector<std::vector<uint64_t>> blockSeqences;

    try {
        //TODO Use input

        //Variable initialization
        unsigned char bytes[4];
        uint16_t num16 = 0;
        uint32_t num32 = 0;

    /**********************************************************************************************************************/
    /**DAL*****************************************************************************************************************/
    /**********************************************************************************************************************/
        //Essential Ext3 file system information
        uint32_t blockSize = 0;
        uint32_t reservedBlocks = 0;
        uint32_t inodesPerGroup = 0;
        uint16_t inodeSize = 0;
        std::vector<std::vector<unsigned char>> inodeTables;

        //Store block size
        bytes[0] = m_rawData->at(1024, 24, input.at(0), input.at(input.size() - 1));
        bytes[1] = m_rawData->at(1024, 25, input.at(0), input.at(input.size() - 1));
        bytes[2] = m_rawData->at(1024, 26, input.at(0), input.at(input.size() - 1));
        bytes[3] = m_rawData->at(1024, 27, input.at(0), input.at(input.size() - 1));
        num32 = 0;
        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
        blockSize = 1024 << num32;

        //Block where first block group starts
        bytes[0] = m_rawData->at(1024, 20, input.at(0), input.at(input.size() - 1));
        bytes[1] = m_rawData->at(1024, 21, input.at(0), input.at(input.size() - 1));
        bytes[2] = m_rawData->at(1024, 22, input.at(0), input.at(input.size() - 1));
        bytes[3] = m_rawData->at(1024, 23, input.at(0), input.at(input.size() - 1));
        num32 = 0;
        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
        reservedBlocks = num32;

        //Store number of inodes per group
        bytes[0] = m_rawData->at(1024, 40, input.at(0), input.at(input.size() - 1));
        bytes[1] = m_rawData->at(1024, 41, input.at(0), input.at(input.size() - 1));
        bytes[2] = m_rawData->at(1024, 42, input.at(0), input.at(input.size() - 1));
        bytes[3] = m_rawData->at(1024, 43, input.at(0), input.at(input.size() - 1));
        num32 = 0;
        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
        inodesPerGroup = num32;

        //Store inode size
        bytes[0] = m_rawData->at(1024, 88, input.at(0), input.at(input.size() - 1));
        bytes[1] = m_rawData->at(1024, 89, input.at(0), input.at(input.size() - 1));
        num16 = 0;
        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint16_t), reinterpret_cast<unsigned char*>(&num16));
        inodeSize = num16;

        //Extract group descriptor tables
        uint64_t start = blockSize * (reservedBlocks + 1);
        uint64_t end = (blockSize * (reservedBlocks + 2)) - 1;
        std::vector<unsigned char> groupDescriptorTables(m_rawData->copy2Vector(start, end));

        //Store block group information
        std::vector<unsigned char> groupDescriptorTable;
        uint32_t inodes = inodesPerGroup * inodeSize;
        inodes = inodes / blockSize;

        while (true) {
            groupDescriptorTable.clear();
            std::copy(groupDescriptorTables.begin(), groupDescriptorTables.begin() + 32, std::back_inserter(groupDescriptorTable));
            groupDescriptorTables.erase(groupDescriptorTables.begin(), groupDescriptorTables.begin() + 32);

            //Check if end is reached
            bool test = std::all_of(groupDescriptorTable.begin(),
                                    groupDescriptorTable.end(), [](int i)
                                    {return i == 0;});
            if (test) {
                break;
            }

            //Store inode table block address
            bytes[0] = groupDescriptorTable.at(8);
            bytes[1] = groupDescriptorTable.at(9);
            bytes[2] = groupDescriptorTable.at(10);
            bytes[3] = groupDescriptorTable.at(11);
            num32 = 0;
            std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

            //Store inode table content for file recovery
            start = num32 * blockSize;
            end = ((inodes + num32 - 1) * blockSize) - 1;
            inodeTables.push_back(m_rawData->copy2Vector(start, end));
        }

    /**********************************************************************************************************************/
    /**FCL*****************************************************************************************************************/
    /**********************************************************************************************************************/
        //Helper
        uint32_t inodeCounter = 1;
        uint64_t position = 0;

        //Essential Ext3 inode/file information
    //    uint32_t filesize = 0;
        std::vector<uint64_t> directBlocks;
        std::vector<uint64_t> indirectBlocks;
        std::vector<uint64_t> totalBlocks;

        //TODO Ignore directories?
        for (std::vector<std::vector<unsigned char>>::const_iterator it = inodeTables.begin();
             it != inodeTables.end(); ++it) {
            while (position < it->size()) {
                //Break if inode essentials (file mode, size) are empty
                if (((it->at(position) == 0x00) &&
                    (it->at(position + 1) == 0x00) &&
                    (it->at(position + 4) == 0x00) &&
                    (it->at(position + 5) == 0x00) &&
                    (it->at(position + 6) == 0x00) &&
                    (it->at(position + 7) == 0x00)) ||
                    ((inodeCounter != 2) && (inodeCounter < 11))) {
                    inodeCounter++;
                    position += inodeSize;
                }
                else {
                    //TODO Unnecessary?
    //                //Store file size
    //                bytes[0] = it->at(position + 4);
    //                bytes[1] = it->at(position + 5);
    //                bytes[2] = it->at(position + 6);
    //                bytes[3] = it->at(position + 7);
    //                num32 = 0;
    //                std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
    //                filesize = num32;

                    //Store direct block pointers
                    //There are twelfe  -> 12 * 4 = 48
                    for (uint32_t i = 0; i < 48; i++) {
                        bytes[0] = it->at(position + 40 + i);
                        bytes[1] = it->at(position + 41 + i);
                        bytes[2] = it->at(position + 42 + i);
                        bytes[3] = it->at(position + 43 + i);
                        num32 = 0;
                        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));
                        if (num32 != 0) {
                            directBlocks.push_back(num32);
                        }

                        i += 3;
                    }

                    totalBlocks = convertBlocks(directBlocks, blockSize);

                    //Store single indirect block pointer
                    bytes[0] = it->at(position + 88);
                    bytes[1] = it->at(position + 89);
                    bytes[2] = it->at(position + 90);
                    bytes[3] = it->at(position + 91);
                    num32 = 0;
                    std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

                    if (num32 != 0) {
                        std::vector<uint64_t> temp;
                        std::vector<uint64_t> temp2;
                        indirectBlocks.push_back(num32);
                        temp = parseBlocks(num32, 12, blockSize, input);
                        temp2 = convertBlocks(temp, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp2.begin(), temp2.end());
                    }

                    //Store double indirect block pointer
                    bytes[0] = it->at(position + 92);
                    bytes[1] = it->at(position + 93);
                    bytes[2] = it->at(position + 94);
                    bytes[3] = it->at(position + 95);
                    num32 = 0;
                    std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

                    if (num32 != 0) {
                        std::vector<uint64_t> temp;
                        std::vector<uint64_t> temp2;
                        std::vector<uint64_t> temp3;
                        temp = parseBlocks(num32, 2, blockSize, input);
                        indirectBlocks.insert(indirectBlocks.end(), temp.begin(), temp.end());
                        temp2 = parseBlocks(temp.at(0), 12, blockSize, input);
                        temp3 = convertBlocks(temp2, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp3.begin(), temp3.end());
                        temp2 = parseBlocks(temp.at(1), 12, blockSize, input);
                        temp3 = convertBlocks(temp2, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp3.begin(), temp3.end());
                    }

                    //Store triple indirect block pointer
                    bytes[0] = it->at(position + 96);
                    bytes[1] = it->at(position + 97);
                    bytes[2] = it->at(position + 98);
                    bytes[3] = it->at(position + 99);
                    num32 = 0;
                    std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num32));

                    if (num32 != 0) {
                        std::vector<uint64_t> temp;
                        std::vector<uint64_t> temp2;
                        std::vector<uint64_t> temp3;
                        temp = parseBlocks(num32, 3, blockSize, input);
                        indirectBlocks.insert(indirectBlocks.end(), temp.begin(), temp.end());
                        temp2 = parseBlocks(temp.at(0), 12, blockSize, input);
                        temp3 = convertBlocks(temp2, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp3.begin(), temp3.end());
                        temp2 = parseBlocks(temp.at(1), 12, blockSize, input);
                        temp3 = convertBlocks(temp2, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp3.begin(), temp3.end());
                        temp2 = parseBlocks(temp.at(1), 12, blockSize, input);
                        temp3 = convertBlocks(temp2, blockSize);
                        totalBlocks.insert(totalBlocks.end(), temp3.begin(), temp3.end());
                    }

                    std::sort(totalBlocks.begin(), totalBlocks.end());


                    //Evaluate file allocation status
                    if (!totalBlocks.empty()) {
                        blockSeqences.push_back(totalBlocks);
                    }

                    inodeCounter++;
                    position += inodeSize;
                    directBlocks.clear();
                    indirectBlocks.clear();
                    totalBlocks.clear();
                }
            }
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return blockSeqences;
}

std::vector<uint64_t> Ext3::parseBlocks(uint32_t startAddress, uint32_t times, uint32_t blockSize, std::vector<uint64_t> input)
{
    unsigned char bytes[4];
    uint32_t num = 0;
    std::vector<uint64_t> blocks;
    uint64_t position = startAddress * blockSize;

    for (uint32_t i = 0; i < (times * 4); i++) {
        //Store block
        bytes[0] = m_rawData->at(position, i, input.at(0), input.at(input.size() - 1));
        bytes[1] = m_rawData->at(position, i + 1, input.at(0), input.at(input.size() - 1));
        bytes[2] = m_rawData->at(position, i + 2, input.at(0), input.at(input.size() - 1));
        bytes[3] = m_rawData->at(position, i + 3, input.at(0), input.at(input.size() - 1));
        num = 0;
        std::copy(&(bytes[0]), &(bytes[0]) + sizeof(uint32_t), reinterpret_cast<unsigned char*>(&num));
        blocks.push_back(num);
        i += 3;
    }

    return blocks;
}

std::vector<uint64_t> Ext3::convertBlocks(std::vector<uint64_t> blocks, uint32_t blockSize)
{
    std::vector<uint64_t> res;

    if (blockSize > 512) {
        uint32_t helper = blockSize;

        for (auto it = blocks.begin(); it != blocks.end(); ++it) {
            auto start = *it * blockSize;

            while (helper > 0) {
                res.push_back(start / 512);
                start += 512;
                helper -= 512;
            }

            helper = blockSize;
        }
    }

    return res;
}
