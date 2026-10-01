#include <iostream>
#include <fstream>
#include <complex>

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

    ofstream image("mandelbrot.ppm");

    image << "P3\n";
    image << width << " " << height << "\n";
    image << "255\n";

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

            int color = 255 * iter / max_iter;

            image << color << " "
                  << color << " "
                  << color << " ";
        }

        image << "\n";
    }

    image.close();

    return 0;
}