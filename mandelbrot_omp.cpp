#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <omp.h>

using namespace std;

int main()
{
    const int width = 1000;
    const int height = 1000;
    const int max_iter = 1000;

    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.5;
    const double ymax = 1.5;

    vector<int> pixels(width * height);

    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double real = xmin + (xmax - xmin) * x / width;
            double imag = ymin + (ymax - ymin) * y / height;

            complex<double> c(real, imag);
            complex<double> z(0.0, 0.0);

            int iter = 0;

            while (abs(z) <= 2.0 && iter < max_iter)
            {
                z = z * z + c;
                iter++;
            }

            pixels[y * width + x] =
                255 * iter / max_iter;
        }
    }

    double end = omp_get_wtime();

    cout << "Calculation time: "
     << end - start
     << " s" << endl;   
    ofstream image("mandelbrot_omp.ppm");

    image << "P3\n";
    image << width << " " << height << "\n";
    image << "255\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int color = pixels[y * width + x];

            image << color << " "
                  << color << " "
                  << color << " ";
        }

        image << "\n";
    }

    image.close();

    return 0;
}