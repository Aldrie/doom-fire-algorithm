#include <iostream>
#include <vector>

namespace ray{
    #include <raylib.h>
}

std::vector <int> firePixel;
const int fireWidth = 200;
const int fireHeight = 200;

ray::Color fireColors[] = {
    {0, 0, 0, 255},      {7, 7, 7, 255},       {31, 7, 7, 255},      {47, 15, 7, 255},     {71, 15, 7, 255},     {87, 23, 7, 255},     {103, 31, 7, 255},
    {119, 31, 7, 255},   {143, 39, 7, 255},    {159, 47, 7, 255},    {175, 63, 7, 255},    {191, 71, 7, 255},    {199, 71, 7, 255},    {223, 79, 7, 255},
    {223, 87, 7, 255},   {223, 87, 7, 255},    {215, 95, 7, 255},    {215, 95, 7, 255},    {215, 103, 15, 255},  {207, 111, 15, 255},  {207, 119, 15, 255},
    {207, 127, 15, 255}, {207, 135, 23, 255},  {199, 135, 23, 255},  {199, 143, 23, 255},  {199, 151, 31, 255},  {191, 159, 31, 255},
    {191, 159, 31, 255}, {191, 167, 39, 255},  {191, 167, 39, 255},  {191, 175, 47, 255},  {183, 175, 47, 255},  {183, 183, 47, 255},
    {183, 183, 55, 255}, {207, 207, 111, 255}, {223, 223, 159, 255}, {239, 239, 199, 255},
};



void createFireDataStructure(){
    const int numPixels = fireWidth*fireHeight; 
    firePixel.resize(numPixels);

    for(int i = 0; i < numPixels; i++){
        firePixel[i] = 0;
    }
}


void updateFireIntensityPerPixel(int currentPixelIndex){
    const int belowPixelIndex = currentPixelIndex + fireWidth;

    if (belowPixelIndex >= fireWidth * fireHeight){
        return;
    }

    int decay = ray::GetRandomValue(0, 1);
    const int belowPixelFireIntensity = firePixel[belowPixelIndex];

    int newFireIntensity = 
        (belowPixelFireIntensity - decay) >= 0? belowPixelFireIntensity - decay : 0;

    int newIndex = currentPixelIndex - decay;

    if (newIndex >= 0){
        firePixel[newIndex] = newFireIntensity;
    }
}


void renderFire(){
    for(int row = 0; row < fireHeight; row++){

        for(int column = 0; column < fireWidth; column++){
            const int pixelIndex = column + (fireWidth * row);
            const int fireIntensity = firePixel[pixelIndex];

            DrawRectangle(column * 3, row * 3, 3, 3, fireColors[fireIntensity]);
        }

    }
}

void calculateFirePropagation(){

    for(int column = 0; column < fireWidth; column++ ){
        for(int row = fireHeight - 1; row >= 0; row--){
            int pixelIndex = column + (fireWidth * row);

            updateFireIntensityPerPixel(pixelIndex);
        }
    }

    renderFire();
}

void createSourceFire(){
    for(int column = 0; column < fireWidth; column++){
        const int overflowPixelIndex = fireWidth * fireHeight;
        const int pixelIndex = (overflowPixelIndex - fireWidth) + column;

        firePixel[pixelIndex] = 36;
    }
}

int main(){
    ray::InitWindow(fireWidth*3, fireHeight*3, "Doom Fire");

    createFireDataStructure();
    createSourceFire();

    while(!ray::WindowShouldClose()){
        ray::BeginDrawing();
        ray::ClearBackground(ray::BLACK);

        calculateFirePropagation();

        ray::EndDrawing();
    }

    ray::CloseWindow();
    return 0;
}
