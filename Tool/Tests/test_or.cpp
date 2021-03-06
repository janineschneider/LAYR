#include "../getworkingdir.h"
#include "../Heuristics/Ext3/ext3.h"
#include "../Heuristics/Failure/failure.h"
#include "../SequentialOperators/or.h"

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
    std::string imagePath2(imagePath);
    imagePath.append("\\TestImages\\Ext3\\");
    imagePath2.append("\\buildDebug\\");

    //Read in image name
    std::string imageName;
    imageName = "ext3-img-kw-1.dd";
    imagePath.append(imageName);

    //Open binary ifstream
    std::ifstream imageStream(imagePath, std::ios::binary);

    if (imageStream.is_open()) {
        ByteContainer* rawData;
        rawData = new ByteContainer(imageStream);
        std::vector<uint64_t> input = {0, rawData->size()};
        std::vector<std::vector<uint64_t>> result;

        Heuristic* h1;
        h1 = new Failure();

        Heuristic* h2;
        h2 = new Ext3(rawData);

        Or op(h1, h2);
        result = op.evaluate(input);

        for (auto it = result.begin(); it != result.end(); ++it) {
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                std::cout << *it2 << " ";
            }
            std::cout << std::endl;
        }

        imageStream.close();
    }

    return 0;
}
