
#include "colour.h"
#include "grayscale.h"

//raw - coloured
int main1()
{
    std::string imagePath = "D:/oop/lab3/lab3/ab.png";
    ColoredImage coloredImage(imagePath);
    coloredImage.ProcessImage();
    coloredImage.ShowImages();

    return 0;
}

//incdec-colour
int main2() 
{
    std::string imagePath = "D:/oop/lab3/lab3/ab.png";
    ColoredImage2 coloredImage(imagePath);

    int changered, changegreen, changeblue;

    std::cout << "Do you want to increase or decrease the red color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter value to increase red color: ";
        std::cin >> changered;
    }
    else if (choice == -1) {
        std::cout << "Enter value to decrease red color: ";
        std::cin >> changered;
        changered = -changered;
    }
    else {
        changered = 0;
    }

    std::cout << "Do you want to increase or decrease the green color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter value to increase green color: ";
        std::cin >> changegreen;
    }
    else if (choice == -1) {
        std::cout << "Enter value to decrease green color: ";
        std::cin >> changegreen;
        changegreen = -changegreen;
    }
    else {
        changegreen = 0;
    }

    std::cout << "Do you want to increase or decrease the blue color? (Enter '1' for increase, '-1' for decrease, '0' for no change): ";
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Enter value to increase blue color: ";
        std::cin >> changeblue;
    }
    else if (choice == -1) {
        std::cout << "Enter value to decrease blue color: ";
        std::cin >> changeblue;
        changeblue = -changeblue;
    }
    else {
        changeblue = 0;
    }

    coloredImage.ProcessImage(changered, changegreen, changeblue);
    coloredImage.ShowImages();

    return 0;
}

//cropping - colour
int main3()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    std::vector<int> cropDimensions(2);
    std::cout << "Enter the height for cropping: ";
    std::cin >> cropDimensions[0];
    std::cout << "Enter the width for cropping: ";
    std::cin >> cropDimensions[1];

    cropImage(image, cropDimensions);

    cv::imshow("Cropped Image", image);

    cv::waitKey(0);
    return 0;
}

//rotation - colour
int main4()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    std::vector<int> rp(1);
    std::cout << "Enter the degree of rotation (90, 180, or 270): ";
    std::cin >> rp[0];

    rotateImage(image, rp);

    cv::imshow("Rotated Image", image);

    cv::waitKey(0);
    return 0;
}

//quantization - colour
int main5()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png");

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    std::vector<int> channelLevels(3);
    std::cout << "Enter the level for Blue channel (2/4/8/16/32/64/128): ";
    std::cin >> channelLevels[0];

    std::cout << "Enter the level for Green channel (2/4/8/16/32/64/128): ";
    std::cin >> channelLevels[1];

    std::cout << "Enter the level for Red channel (2/4/8/16/32/64/128): ";
    std::cin >> channelLevels[2];

    quantizeChannels(image, channelLevels);

    cv::imshow("Quantized Image", image);

    cv::waitKey(0);
    return 0;
}

//raw - grayscale
int main6()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    g1(image);

    cv::waitKey(0);
    return 0;
}

//incdec - grayscale
int main7()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int intch = 0;
    g2(image, intch);

    return 0;
}

//crop - grayscale
int main8()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    std::vector<int> cropDimensions(2);
    std::cout << "Enter the height for cropping: ";
    std::cin >> cropDimensions[0];
    std::cout << "Enter the width for cropping: ";
    std::cin >> cropDimensions[1];

    cropImage3(image, cropDimensions);

    cv::imshow("Cropped Image", image);

    cv::waitKey(0);
    return 0;
}

//rotation - grayscale
int main9()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int degreeOfRotation;
    std::cout << "Enter the degree of rotation (90, 180, or 270): ";
    std::cin >> degreeOfRotation;

    rotateImage3(image, degreeOfRotation);

    cv::imshow("Rotated Image", image);

    cv::waitKey(0);
    return 0;
}

//quantization - grayscale
int main10()
{
    cv::Mat image = cv::imread("D:/oop/lab3/lab3/ab.png", cv::IMREAD_GRAYSCALE);

    if (image.empty())
    {
        std::cerr << "Error: Unable to load the image." << std::endl;
        return -1;
    }

    int level;
    std::cout << "Enter the level for quantization (2/4/8/16/32/64/128): ";
    std::cin >> level;

    quantizeChannels(image, level);

    cv::imshow("Quantized Image", image);

    cv::waitKey(0);
    return 0;
}

void menu()
{
    std::cout << "1. Raw - coloured" << std::endl;
    std::cout << "2. Inc/Dec - coloured" << std::endl;
    std::cout << "3. Cropping - coloured" << std::endl;
    std::cout << "4. Rotation - coloured" << std::endl;
    std::cout << "5. Channel Specific - coloured" << std::endl;
    std::cout << "6. Raw - grayscale" << std::endl;
    std::cout << "7. Inc/Dec - grayscale" << std::endl;
    std::cout << "8. Cropping - grayscale" << std::endl;
    std::cout << "9. Rotation - grayscale" << std::endl;
    std::cout << "10. Channel Specific - grayscale" << std::endl;
    std::cout << "0. Exit" << std::endl;

}
int main()
{
    int choice;
    while (true)
    {
        std::cout << "__________________________\n" << std::endl;
        menu();
        std::cout << "__________________________\n" << std::endl;
        std::cout << "Enter Choice:";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            return 0;
            break;
        case 1:
            main1();
            break;
        case 2:
            main2();
            break;
        case 3:
            main3();
            break;
        case 4:
            main4();
            break;
        case 5:
            main5();
            break;
        case 6:
            main6();
            break;
        case 7:
            main7();
            break;
        case 8:
            main8();
            break;
        case 9:
            main9();
            break;
        case 10:
            main10();
            break;
        default:
            break;
        }
    }
    return 0;
}
