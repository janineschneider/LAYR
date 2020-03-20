#include "../getworkingdir.h"
#include "../Heuristics/DOS/dos.h"

#include <iostream>

int main()
{
    //Get current working dir path
    //Currently working for Windows
    //Please change define in getworkingdir.h for Unix
    char buffer[100];
    getCurrentDir(buffer, 100);
    std::string imagePath(buffer);

    //Handle file extension
    size_t found = imagePath.rfind("\\");
    imagePath.erase(found, imagePath.size() - found);
    imagePath.append("\\TestImages\\DOS\\");

    //Read in image name
    std::string imageName;
    imageName = "ext-part-test-2.dd";
    imagePath.append(imageName);

    //Open binary ifstream
    std::ifstream imageStream(imagePath, std::ios::binary);

    if (imageStream.is_open()) {
        ByteContainer* rawData;
        rawData = new ByteContainer(imageStream);
        std::vector<uint64_t> input = {0, rawData->size()};
        std::vector<std::vector<uint64_t>> result;

        Heuristic* h1;
        h1 = new DOS(rawData);
        result = h1->evaluate(input);

        for (auto it = result.begin(); it != result.end(); ++it) {
            std::cout << it->front() << " " << it->back();
            std::cout << std::endl;
        }

        imageStream.close();
    }
	
    return 0;
}
