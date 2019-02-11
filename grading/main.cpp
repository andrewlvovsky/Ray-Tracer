#include "render_world.h"
#include "object.h"
#include <iostream>
#include <cstdio>
#include <unistd.h>

/*

  Usage: ./ray_tracer -i <test-file> [ -s <solution-file> ] [ -o <stats-file> ] [ -x <debug-x-coord> -y <debug-y-coord> ]

  Examples:

  ./ray_tracer -i 00.txt

  Renders the scene described by 00.txt.  Dumps the result to output.png.

  ./ray_tracer -i 00.txt -s 00.png

  Renders the scene described by 00.txt.  Dumps the result to output.png.
  Compares this to the solution in 00.png and dumps the error to diff.png.
  Outputs a measure of the error.

  ./ray_tracer -i 00.txt -x 123 -y 234

  The -x and -y flags give you the opportunity to print out lots of detailed
  information about the rendering of a single pixel.  This allows you to be
  verbose about a pixel of interest without printing this information for every
  pixel.  For many of the scenes, there is a pixel trace on the project page
  detailing the results of various computations (intersections, shading, etc.)
  for one specially chosen pixel.

  If you are getting the wrong results for a test, check to see if there is a
  pixel trace available for that test.  When there is, the pixel trace is often
  the easiest way to debug the problem.  Print out the same information from
  your code that is available in the pixel trace.  This will tell you which
  quantities are being computed correctly and can help you narrow down your
  search.

  The -o flag is used by the grading script.  It causes the results of your ray
  tracer to be printed to a file rather than to the standard output.  This
  prevents the grading script from getting confused by debugging output.

 */

// Indicates that we are debugging one pixel; can be accessed everywhere.
bool debug_pixel=false;

// This can be used to quickly disable the hierarchy for testing purposes.
// Though this is not required, it is highly recommended that you implement
// this, as it will make debugging your hierarchy much easier.
bool disable_hierarchy=false;

void Usage(const char* exec)
{
    std::cerr<<"Usage: "<<exec<<" -i <test-file> [ -s <solution-file> ] [ -o <stats-file> ] [ -x <debug-x-coord> -y <debug-y-coord> ]"<<std::endl;
    exit(1);
}

void Parse(Render_World& world,int& width,int& height,const char* test_file);
void Dump_png(Pixel* data,int width,int height,const char* filename);
void Read_png(Pixel*& data,int& width,int& height,const char* filename);

int main(int argc, char** argv)
{
    const char* solution_file = 0;
    const char* input_file = 0;
    const char* statistics_file = 0;
    int test_x=-1, test_y=-1;

    // Parse commandline options
    while(1)
    {
        int opt = getopt(argc, argv, "s:i:m:o:x:y:h");
        if(opt==-1) break;
        switch(opt)
        {
            case 's': solution_file = optarg; break;
            case 'i': input_file = optarg; break;
            case 'o': statistics_file = optarg; break;
            case 'x': test_x = atoi(optarg); break;
            case 'y': test_y = atoi(optarg); break;
            case 'h': disable_hierarchy=true; break;
        }
    }
    if(!input_file) Usage(argv[0]);

    int width=0;
    int height=0;
    Render_World world;
    
    // Parse test scene file
    Parse(world,width,height,input_file);

    // Render the image
    world.Render();

    // For debugging.  Render only the pixel specified on the commandline.
    // Useful for printing out information about a single pixel.
    if(test_x>=0 && test_y>=0)
    {
        // Set a global variable to indicate that we are debugging one pixel.
        // This way you can do: if(debug_pixel) cout<<lots<<of<<stuff<<here<<endl;
        debug_pixel = true;

        // Render just the pixel we are debugging
        world.Render_Pixel(ivec2(test_x,test_y));

        // Mark the pixel we are testing green in the output image.
        world.camera.Set_Pixel(ivec2(test_x,test_y),0x00ff00ff);
    }

    // Save the rendered image to disk
    Dump_png(world.camera.colors,width,height,"output.png");

    // If a solution is specified, compare against it.
    if(solution_file)
    {
        int width2 = 0, height2 = 0;
        Pixel* data_sol = 0;

        // Read solution from disk
        Read_png(data_sol,width2,height2,solution_file);
        assert(width==width2);
        assert(height==height2);

        // For each pixel, check to see if it matches solution
        double error = 0, total = 0;
        for(int i=0; i<height*width; i++)
        {
            vec3 a=From_Pixel(world.camera.colors[i]);
            vec3 b=From_Pixel(data_sol[i]);
            for(int c=0; c<3; c++)
            {
                double e = fabs(a[c]-b[c]);
                error += e;
                total++;
                b[c] = e;
            }
            data_sol[i]=Pixel_Color(b);
        }

        // Output information on how well it matches. Optionally save to file
        // to avoid getting confused by debugging print statements.
        FILE* stats_file = stdout;
        if(statistics_file) stats_file = fopen(statistics_file, "w");
        fprintf(stats_file,"diff: %.2f\n",error/total*100);
        if(statistics_file) fclose(stats_file);

        // Output images showing the error that was computed to aid debugging
        Dump_png(data_sol,width,height,"diff.png");
        delete [] data_sol;
    }

    return 0;
}

